#ifndef SQL_RESULT_H 
#define SQL_RESULT_H

#include <string>
#include <ctime>

struct SQLResult {
    std::string uuid;
    std::string title;
    std::string content;
    std::time_t time;
};

#endif