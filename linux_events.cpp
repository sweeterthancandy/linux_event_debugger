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
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/preprocessor.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/program_options.hpp>


#include "event_monitor.h"

#include "linux_event_to_string.h"
#include "aux.h"



int main(int argc, char** argv){
        try{
                namespace bf = boost::filesystem;

                std::vector<std::thread> tg;

                boost::asio::io_service io;

                std::vector<std::shared_ptr<event_monitor> > monitors;

                auto printer = [](const std::string& dev, const struct input_event& ev){
                        std::stringstream sstr;
                        sstr << dev << " - ";
                        sstr << input_event_to_string(ev,aux::colour_formatter());
                        std::cout << sstr.str() << std::endl;
                };

                for(bf::directory_iterator iter("/dev/input/"),end;iter!=end;++iter){
                        auto p = iter->path();
                        auto dev = p.filename().string();
                       
                      
                        if( ! bf::is_directory( iter->path() ) )
                        {
                                auto sptr = std::make_shared<event_monitor>(io, iter->path().string());
                                sptr->start();
                                sptr->connect( printer );
                                monitors.emplace_back(sptr);
                        }
                }

                boost::asio::signal_set signals( io);
                signals.add( SIGINT );
                signals.add( SIGTERM );

                signals.async_wait( [&monitors](const boost::system::error_code& ec, int sig){
                        switch(sig){
                                case SIGINT:
                                case SIGTERM:
                                        boost::for_each( monitors, std::mem_fn(&event_monitor::stop) );
                                        monitors.clear();
                                        break;
                                default:
                                        assert( 0 && "unexpcted signal");
                        }
                });

                io.run();

        } catch( const std::exception& e){
                std::cerr 
                        << "Caught exception: "
                        << boost::diagnostic_information(e)
                        ;
                return EXIT_FAILURE;
        }
}
