#ifndef SEARCH_RESULT_H 
#define SEARCH_RESULT_H

#include <string>
#include <ctime>

struct SearchResult {
    std::string UUID;
    std::string title;
    std::string content;
    std::time_t time;
    int64_t ref;
};

#endif