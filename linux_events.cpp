#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <linux/input.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/preprocessor.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/program_options.hpp>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#include "event_monitor.h"

#include "linux_event_to_string.h"
#include "aux.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

namespace{


enum tag{
        tag_created,
        tag_deleted,
        tag_existing,
};



struct directory_monitor : std::enable_shared_from_this<directory_monitor>{
        using sig_t = void(tag, const std::string&);
        using signal_t = boost::signals2::signal<sig_t>;

        explicit directory_monitor(boost::asio::io_service& io_, const std::string& dir)
                :io_(io_)
                ,work_(io_) // keep alive
                ,timer_(io_)
        {
                fd = inotify_init();

                wd = inotify_add_watch( fd, dir_.c_str(), 
                                        IN_MODIFY | IN_CREATE | IN_DELETE );

                time_to_wait.tv_sec = 0;
                time_to_wait.tv_usec = 0;

        }
        void start(){
                start_read();
        }
        void stop(){
                running_ = false;
        }
        boost::signals2::connection connect(const signal_t::slot_type& sub){
                return sig_.connect(sub);
        }
private:
        void start_read(){
                timer_.expires_from_now(boost::posix_time::milliseconds(50));
                timer_.async_wait( [this](boost::system::error_code ec){
                        FD_ZERO ( &descriptors );
                        FD_SET ( fd, &descriptors );
                         
                                 
                        int return_value = select ( fd + 1, &descriptors, NULL, NULL, &time_to_wait);
                         
                        if ( return_value < 0 ) {
                                perror("select");
                        }
                        else if ( ! return_value ) {
                        }
                        else if ( FD_ISSET ( fd, &descriptors ) ) {
                                char buffer[BUF_LEN];
                                int length = read( fd, buffer, BUF_LEN );  

                                if ( length < 0 ) {
                                        perror( "read" );
                                }  

                                for(int i=0;  i < length ; ) {
                                        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
                                        if ( event->len ) {
                                                if ( event->mask & IN_CREATE ) {
                                                        if ( ! (event->mask & IN_ISDIR ) ) {
                                                                sig_(tag_created, dir_ + "/" + event->name); 
                                                        }
                                                }
                                                else if ( event->mask & IN_DELETE ) {
                                                        if ( ! ( event->mask & IN_ISDIR ) ) {
                                                                sig_(tag_deleted, dir_+ "/" + event->name); 
                                                        }
                                                }
                                        }
                                        i += EVENT_SIZE + event->len;
                                }
                        }

                        if( running_ ){
                                start_read();
                        }
                });
        }
private:
        std::string dir_{"/dev/input"};
        boost::asio::io_service& io_;
        boost::asio::io_service::work work_;
        boost::asio::deadline_timer timer_;
        boost::array<char,sizeof(struct inotify_event) * 1024> ev_buffer_;

        bool running_{true};

        int fd;
        int wd;
        int return_value;
        fd_set descriptors;
        struct timeval time_to_wait{0};
        signal_t sig_;
};


struct driver{
        driver():signals_(io_){}
        int run(int argc, char** argv){
                try{
                        bool do_create_existing = true;

                        for(int arg_iter=1; arg_iter < argc;){
                                int d = argc - arg_iter;
                                std::string arg = argv[arg_iter];
                                switch(d){
                                default:
                                case 1:
                                        if( arg == "--dont-create-existing"){
                                                do_create_existing = false;
                                                ++arg_iter;
                                                continue;
                                        }
                                        if( arg == "--help" ){
                                                std::cout 
                                                        << argv[0] << " <options>\n"
                                                        << "             --dont-create-existing\n";
                                                ++arg_iter;
                                                return EXIT_SUCCESS;
                                        }
                                }
                                std::cerr << "unknown arg \"" << arg << "\"\n";
                                return EXIT_FAILURE;
                        }


                        start_monitor_();
                        if( do_create_existing ){
                                create_existing_();
                        }
                        start_signal_monitor_();

                        io_.run();


                } catch( const std::exception& e){
                        std::cerr 
                                << "Caught exception: "
                                << boost::diagnostic_information(e)
                                ;
                        return EXIT_FAILURE;
                }
        }
private:
        void start_signal_monitor_(){
                signals_.add( SIGINT );
                signals_.add( SIGTERM );
                signals_.async_wait( [this](const boost::system::error_code& ec, int sig){
                        switch(sig){
                                case SIGINT:
                                case SIGTERM:
                                        mon_->stop();
                                        mon_.reset();
                                        for( auto& p : monitors_ ){
                                                p.second->stop();
                                        }
                                        monitors_.clear();
                                        break;
                                default:
                                        assert( 0 && "unexpcted signal");
                        }
                });
        }
        void start_monitor_(){
                mon_ = std::make_shared<directory_monitor>(io_, "/dev/input");
                mon_->connect([this](tag t, std::string const& dir){
                        process_event_(t, dir);
                });
                mon_->start();
        }
        void create_existing_(){
                namespace bf = boost::filesystem;
                for(bf::directory_iterator iter("/dev/input/"),end;iter!=end;++iter){
                        auto p = iter->path();
                        auto dev = p.filename().string();
                       
                      
                        if( ! bf::is_directory( iter->path() ) )
                        {
                                process_event_(tag_existing, iter->path().string());
                        }
                }
        }
        void pretty_print_(const std::string& dev, const struct input_event& ev){
                std::stringstream sstr;
                sstr << dev << " - ";
                sstr << input_event_to_string(ev,aux::colour_formatter());
                std::cout << sstr.str() << std::endl;
        }
        void process_event_(tag t, std::string const& dir){
                switch(t){
                        case tag_existing:
                        case tag_created:{
                                std::cerr << dir << " created\n";
                                auto sptr = std::make_shared<event_monitor>(io_, dir);
                                sptr->start();
                                sptr->connect( [this](std::string const& dev, const struct input_event& ev){
                                       pretty_print_(dev, ev);
                                });
                                monitors_.emplace(dir, sptr);
                                break;
                        }
                        case tag_deleted:{
                                std::cerr << dir << " deleted\n";
                                auto iter = monitors_.find(dir);
                                if( iter == monitors_.end()){
                                        std::cerr << "can't find it\n";
                                        break;
                                }
                                iter->second->stop();
                                monitors_.erase(iter);
                                break;
                        }
                }
        }
        boost::asio::io_service io_;
        boost::asio::signal_set signals_;
        std::shared_ptr<directory_monitor> mon_;
        std::map<std::string, std::shared_ptr<event_monitor> > monitors_;
};

} // anon

int main(int argc, char** argv){
        driver d;
        return d.run(argc, argv);
}
