namespace{
namespace aux{
        #define AUX(r,suffix,elem)                                     \
                std::string                                     \
                BOOST_PP_CAT(colour_,BOOST_PP_SEQ_ELEM(0,elem))        \
                (const std::string& s){                                \
                        return BOOST_PP_SEQ_ELEM(1,elem) + s + suffix ;\
                }
        struct colour_formatter{
                #define COL_SUFFIX "\033[0;m"
                #define COL_SEQ\
                        ((red)("\033[0;36m"))   \
                        ((blue)("\033[0;35m"))  \
                        ((green)("\033[0;34m")) \
                        ((yellow)("\033[0;33m"))\
                        ((pruple)("\033[0;32m"))

                BOOST_PP_SEQ_FOR_EACH(AUX,COL_SUFFIX,COL_SEQ)
                #undef COL_SEQ
                #undef COLSUFFIX
        };
                
        struct nul_formatter{                        
                #define NUL_SUFFIX ""
                #define NUL_SEQ\
                        ((red)(""))   \
                        ((blue)(""))  \
                        ((green)("")) \
                        ((yellow)(""))\
                        ((pruple)(""))
                BOOST_PP_SEQ_FOR_EACH(AUX,NUL_SUFFIX,NUL_SEQ)
                #undef NUL_SEQ
                #undef NULSUFFIX
        };
        #undef AUX
}
}
