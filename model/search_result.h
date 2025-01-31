#ifndef SEARCH_RESULT_H 
#define SEARCH_RESULT_H

#include <string>
#include <ctime>

struct SearchResult {
    std::string uuid;
    std::string title;
    std::string content;
    std::time_t time;
    double relevance;
};

#endif