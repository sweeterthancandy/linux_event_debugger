#pragma once

#include "aux.h"

//struct input_event {
	//struct timeval time;
	//__u16 type;
	//__u16 code;
	//__s32 value;
//};

struct event_monitor : std::enable_shared_from_this<event_monitor>{
        explicit event_monitor(boost::asio::io_service& io, const std::string& dev)
                :io_(io)
                ,work_(io) // keep alive
                ,desc_(io)
                ,dev_(dev)
        {
                int fd = open(dev_.c_str(), O_RDONLY);
                if( fd < 0 ) 
                        BOOST_THROW_EXCEPTION(std::domain_error("unable to open file"));
                desc_.assign( fd );
        }
        void start(){
                start_read();
        }
        void stop(){
                desc_.cancel();
        }
private:
        void start_read(){
                auto self = shared_from_this();
                boost::asio::async_read( desc_, boost::asio::buffer(ev_buffer_),
                        [this,self](const boost::system::error_code& ec, size_t n){
                                if( ec ){
                                        // must of been cancelled
                                 
                                } else {
                                        assert( n == sizeof(struct input_event) && "unexpected read size");
                                        on_read( *reinterpret_cast<struct input_event*>(ev_buffer_.data()));
                                        start_read();
                                }
                });
        }
        void on_read(struct input_event& ev){
                std::stringstream sstr;
                sstr << dev_ << " - ";
                sstr << input_event_to_string(ev,aux::colour_formatter());
                std::cout << sstr.str() << std::endl;
        }
private:
        boost::asio::io_service& io_;
        boost::asio::io_service::work work_;
        boost::asio::posix::stream_descriptor desc_;
        std::string dev_;
        boost::array<char,sizeof(struct input_event)> ev_buffer_;
};
