#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "stdio.h"
#include "stdint.h"

namespace dlogger{

typedef enum bsm_log_type
{
    log_type_stdout = 1,
    log_type_file = 2
}bsm_log_type_e;

class dlogger
{
public:
    static bsm_log_type m_log_type;
    static dlogger* m_instance;
    static dlogger* get_instance()
    {
        if (NULL != m_instance)
        {
            return m_instance;
        }
        else
        {
            m_instance = new dlogger();
            return m_instance;
        }
    }
    static bsm_log_type_e get_log_type();
    static void set_log_type(bsm_log_type_e log_type);

    bool init_logger(char* file_name);
    void uninit_logger();

    ~dlogger() {}
public:
    FILE* m_fp_logfile;
private:
    dlogger();

private:  
};

#define LOG(fmt, ...) do{\
    if(log_type_stdout == dlogger::get_log_type() )\
    {\
        fprintf(stdout, "[DEBUG] %s\n%s:%d:" fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
    }\
    else if(log_type_file == dlogger::get_log_type() )\
    {\
        if(NULL != dlogger::get_instance()->m_fp_logfile)\
        {\
            fprintf(dlogger::get_instance()->m_fp_logfile, "%s\n%s:%d:" fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        }\
        else\
        {\
            printf("log_file not init.\n");\
        }\
    }}while(0);
	
}

#endif // !__LOGGER_H__

