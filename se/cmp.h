#ifndef CMP_H
#define CMP_H

#include "../model/search_result.h"

namespace Comparator {
    bool compareRelevance(const SearchResult &lhs, const SearchResult &rhs) { return lhs.sim < rhs.sim; }

    bool compareTitle(SearchResult lhs, SearchResult rhs) { return lhs.title < rhs.title; }

    bool compareTitleRev(SearchResult lhs, SearchResult rhs) { return lhs.title > rhs.title; }

    bool compareTime(SearchResult lhs, SearchResult rhs) { return lhs.time < rhs.time; }

    bool compareTimeRev(SearchResult lhs, SearchResult rhs) { return lhs.time > rhs.time; }
}

#endif