namespace linux_event_to_string_detail{


        #define EVENT_TYPES\
                ((EV_SYN)("EV_SYN"))\
                ((EV_KEY)("EV_KEY"))\
                ((EV_REL)("EV_REL"))\
                ((EV_ABS)("EV_ABS"))\
                ((EV_MSC)("EV_MSC"))\
                ((EV_SW)("EV_SW"))\
                ((EV_LED)("EV_LED"))\
                ((EV_SND)("EV_SND"))\
                ((EV_REP)("EV_REP"))\
                ((EV_FF)("EV_FF"))\
                ((EV_PWR)("EV_PWR"))\
                ((EV_FF_STATUS)("EV_FF_STATUS"))\
                ((EV_MAX)("EV_MAX"))\
        
        #define SYN_EVENTS\
                ((SYN_REPORT)("SYN_REPORT"))\
                ((SYN_CONFIG)("SYN_CONFIG"))\
                ((SYN_MT_REPORT)("SYN_MT_REPORT"))\
                ((SYN_DROPPED)("SYN_DROPPED"))\
                ((SYN_MAX)("SYN_MAX"))\



        #define KEYS_AND_BUTTONS\
                ((KEY_RESERVED)("KEY_RESERVED"))\
                ((KEY_ESC)("KEY_ESC"))\
                ((KEY_1)("KEY_1"))\
                ((KEY_2)("KEY_2"))\
                ((KEY_3)("KEY_3"))\
                ((KEY_4)("KEY_4"))\
                ((KEY_5)("KEY_5"))\
                ((KEY_6)("KEY_6"))\
                ((KEY_7)("KEY_7"))\
                ((KEY_8)("KEY_8"))\
                ((KEY_9)("KEY_9"))\
                ((KEY_0)("KEY_0"))\
                ((KEY_MINUS)("KEY_MINUS"))\
                ((KEY_EQUAL)("KEY_EQUAL"))\
                ((KEY_BACKSPACE)("KEY_BACKSPACE"))\
                ((KEY_TAB)("KEY_TAB"))\
                ((KEY_Q)("KEY_Q"))\
                ((KEY_W)("KEY_W"))\
                ((KEY_E)("KEY_E"))\
                ((KEY_R)("KEY_R"))\
                ((KEY_T)("KEY_T"))\
                ((KEY_Y)("KEY_Y"))\
                ((KEY_U)("KEY_U"))\
                ((KEY_I)("KEY_I"))\
                ((KEY_O)("KEY_O"))\
                ((KEY_P)("KEY_P"))\
                ((KEY_LEFTBRACE)("KEY_LEFTBRACE"))\
                ((KEY_RIGHTBRACE)("KEY_RIGHTBRACE"))\
                ((KEY_ENTER)("KEY_ENTER"))\
                ((KEY_LEFTCTRL)("KEY_LEFTCTRL"))\
                ((KEY_A)("KEY_A"))\
                ((KEY_S)("KEY_S"))\
                ((KEY_D)("KEY_D"))\
                ((KEY_F)("KEY_F"))\
                ((KEY_G)("KEY_G"))\
                ((KEY_H)("KEY_H"))\
                ((KEY_J)("KEY_J"))\
                ((KEY_K)("KEY_K"))\
                ((KEY_L)("KEY_L"))\
                ((KEY_SEMICOLON)("KEY_SEMICOLON"))\
                ((KEY_APOSTROPHE)("KEY_APOSTROPHE"))\
                ((KEY_GRAVE)("KEY_GRAVE"))\
                ((KEY_LEFTSHIFT)("KEY_LEFTSHIFT"))\
                ((KEY_BACKSLASH)("KEY_BACKSLASH"))\
                ((KEY_Z)("KEY_Z"))\
                ((KEY_X)("KEY_X"))\
                ((KEY_C)("KEY_C"))\
                ((KEY_V)("KEY_V"))\
                ((KEY_B)("KEY_B"))\
                ((KEY_N)("KEY_N"))\
                ((KEY_M)("KEY_M"))\
                ((KEY_COMMA)("KEY_COMMA"))\
                ((KEY_DOT)("KEY_DOT"))\
                ((KEY_SLASH)("KEY_SLASH"))\
                ((KEY_RIGHTSHIFT)("KEY_RIGHTSHIFT"))\
                ((KEY_KPASTERISK)("KEY_KPASTERISK"))\
                ((KEY_LEFTALT)("KEY_LEFTALT"))\
                ((KEY_SPACE)("KEY_SPACE"))\
                ((KEY_CAPSLOCK)("KEY_CAPSLOCK"))\
                ((KEY_F1)("KEY_F1"))\
                ((KEY_F2)("KEY_F2"))\
                ((KEY_F3)("KEY_F3"))\
                ((KEY_F4)("KEY_F4"))\
                ((KEY_F5)("KEY_F5"))\
                ((KEY_F6)("KEY_F6"))\
                ((KEY_F7)("KEY_F7"))\
                ((KEY_F8)("KEY_F8"))\
                ((KEY_F9)("KEY_F9"))\
                ((KEY_F10)("KEY_F10"))\

        #define REL_AXIS\
                ((REL_X)("REL_X"))\
                ((REL_Y)("REL_Y"))\
                ((REL_Z)("REL_Z"))\
                ((REL_RX)("REL_RX"))\
                ((REL_RY)("REL_RY"))\
                ((REL_RZ)("REL_RZ"))\
                ((REL_HWHEEL)("REL_HWHEEL"))\
                ((REL_DIAL)("REL_DIAL"))\
                ((REL_WHEEL)("REL_WHEEL"))\
                ((REL_MISC)("REL_MISC"))\


        #define ABS_AXIS\
                ((ABS_X)("ABS_X"))\
                ((ABS_Y)("ABS_Y"))\
                ((ABS_Z)("ABS_Z"))\
                ((ABS_RX)("ABS_RX"))\
                ((ABS_RY)("ABS_RY"))\
                ((ABS_RZ)("ABS_RZ"))\
                ((ABS_THROTTLE)("ABS_THROTTLE"))\
                ((ABS_RUDDER)("ABS_RUDDER"))\
                ((ABS_WHEEL)("ABS_WHEEL"))\
                ((ABS_GAS)("ABS_GAS"))\
                ((ABS_BRAKE)("ABS_BRAKE"))\
                ((ABS_HAT0X)("ABS_HAT0X"))\
                ((ABS_HAT0Y)("ABS_HAT0Y"))\
                ((ABS_HAT1X)("ABS_HAT1X"))\
                ((ABS_HAT1Y)("ABS_HAT1Y"))\
                ((ABS_HAT2X)("ABS_HAT2X"))\
                ((ABS_HAT2Y)("ABS_HAT2Y"))\
                ((ABS_HAT3X)("ABS_HAT3X"))\
                ((ABS_HAT3Y)("ABS_HAT3Y"))\
                ((ABS_PRESSURE)("ABS_PRESSURE"))\
                ((ABS_DISTANCE)("ABS_DISTANCE"))\
                ((ABS_TILT_X)("ABS_TILT_X"))\
                ((ABS_TILT_Y)("ABS_TILT_Y"))\
                ((ABS_TOOL_WIDTH)("ABS_TOOL_WIDTH"))\
                ((ABS_VOLUME)("ABS_VOLUME"))\
                ((ABS_MISC)("ABS_MISC"))\
                ((ABS_MT_SLOT)("ABS_MT_SLOT"))\
                ((ABS_MT_TOUCH_MAJOR)("ABS_MT_TOUCH_MAJOR"))\
                ((ABS_MT_TOUCH_MINOR)("ABS_MT_TOUCH_MINOR"))\
                ((ABS_MT_WIDTH_MAJOR)("ABS_MT_WIDTH_MAJOR"))\
                ((ABS_MT_WIDTH_MINOR)("ABS_MT_WIDTH_MINOR"))\
                ((ABS_MT_ORIENTATION)("ABS_MT_ORIENTATION"))\
                ((ABS_MT_POSITION_X)("ABS_MT_POSITION_X"))\
                ((ABS_MT_POSITION_Y)("ABS_MT_POSITION_Y"))\
                ((ABS_MT_TOOL_TYPE)("ABS_MT_TOOL_TYPE"))\
                ((ABS_MT_BLOB_ID)("ABS_MT_BLOB_ID"))\
                ((ABS_MT_TRACKING_ID)("ABS_MT_TRACKING_ID"))\
                ((ABS_MT_PRESSURE)("ABS_MT_PRESSURE"))\
                ((ABS_MT_DISTANCE)("ABS_MT_DISTANCE"))\
                ((ABS_MT_TOOL_X)("ABS_MT_TOOL_X"))\
                ((ABS_MT_TOOL_Y)("ABS_MT_TOOL_Y"))\


        #define MSC_EVENTS\
                ((MSC_SERIAL)("MSC_SERIAL"))\
                ((MSC_PULSELED)("MSC_PULSELED"))\
                ((MSC_GESTURE)("MSC_GESTURE"))\
                ((MSC_RAW)("MSC_RAW"))\
                ((MSC_SCAN)("MSC_SCAN"))\
                ((MSC_TIMESTAMP)("MSC_TIMESTAMP"))\
                ((MSC_MAX)("MSC_MAX"))\

        #define AUX(r,impl,elem) \
                case BOOST_PP_SEQ_ELEM(0,elem): \
                        return BOOST_PP_SEQ_ELEM(1,elem);
        

        #define MAKE_TO_STRING(int_type,name,impl,SEQ) \
                std::string name(int_type value){\
                        switch(value){\
                                BOOST_PP_SEQ_FOR_EACH(AUX,impl,SEQ)\
                                default:\
                                        return "unknown(" + boost::lexical_cast<std::string>(value) + ")";\
                        }\
                        assert(0);\
                }

        MAKE_TO_STRING(int,type_to_string,~,EVENT_TYPES)
        MAKE_TO_STRING(int,syn_to_string,~,SYN_EVENTS)
        MAKE_TO_STRING(int,key_to_string,~,KEYS_AND_BUTTONS)
        MAKE_TO_STRING(int,rel_to_string,~,REL_AXIS)
        MAKE_TO_STRING(int,abs_to_string,~,ABS_AXIS)
        MAKE_TO_STRING(int,msc_to_string,~,MSC_EVENTS)

        #undef MAKE_TO_STRING
        #undef AUX

        #undef MSC_EVENTS
        #undef ABS_AXIS
        #undef REL_AXIS
        #undef KEYS_AND_BUTTONS
        #undef SYN_EVENTS
        #undef EVENT_TYPES

}

template<class colour_formatter>
std::string input_event_to_string(struct input_event const& ev, colour_formatter&& formatter){

        namespace detail = linux_event_to_string_detail;
        std::string type_s( detail::type_to_string(ev.type));
        std::string code_s;
        std::string value_s = boost::lexical_cast<std::string>(ev.value);

        auto make_it = [](const std::string& type_s, const std::string& code_s, const std::string& value_s){
                return str( boost::format("%-10s %-10s %s")
                                % type_s
                                % code_s
                                % value_s
                       );
        };
        
        switch(ev.type){
                #define AUX_SEQ\
                        ((EV_SYN)(syn_to_string)(formatter.colour_pruple))      \
                        ((EV_KEY)(key_to_string)(formatter.colour_red))         \
                        ((EV_ABS)(abs_to_string)(formatter.colour_blue))        \
                        ((EV_REL)(rel_to_string)(formatter.colour_green))       \
                        ((EV_MSC)(msc_to_string)(formatter.colour_yellow))      \

                #define AUX(r,data,elem)                                        \
                        case BOOST_PP_SEQ_ELEM(0,elem):                         \
                               return BOOST_PP_SEQ_ELEM(2,elem) ( make_it(      \
                                        type_s,                                 \
                                        detail:: BOOST_PP_SEQ_ELEM(1,elem)( ev.code ),   \
                                        value_s                                 \
                                ) ) ;
                BOOST_PP_SEQ_FOR_EACH(AUX,~,AUX_SEQ)
                #undef AUX
                #undef AUX_SEQ
                default:
                        code_s = boost::lexical_cast<std::string>(ev.code);
                        break;
        }
}
