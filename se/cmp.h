#ifndef CMP_H
#define CMP_H

#include "../model/search_result.h"

namespace Comparator {
    bool compareRelevance(const SearchResult &lhs, const SearchResult &rhs) { return lhs.relevance < rhs.relevance; }

    bool compareTitle(const SearchResult &lhs, const SearchResult &rhs) { return lhs.title < rhs.title; }

    bool compareTitleRev(const SearchResult &lhs, const SearchResult &rhs) { return lhs.title > rhs.title; }

    bool compareTime(const SearchResult &lhs, const SearchResult &rhs) { return lhs.time < rhs.time; }

    bool compareTimeRev(const SearchResult &lhs, const SearchResult &rhs) { return lhs.time > rhs.time; }
}

#endif