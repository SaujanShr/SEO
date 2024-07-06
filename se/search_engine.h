#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "../conn/conn.h"
#include "../model/search_result.h"
#include "search_result_cmp.h"

class SearchEngine {
private:
    const MySQLConnector conn;

    std::vector<SearchResult> searchResults;

    const std::unique_ptr<sql::ResultSet> getQueryResultSet(const std::string &query) const;

    std::vector<SearchResult> processQueryResultSet(const std::unique_ptr<sql::ResultSet> &queryResultSet) const;

    template<typename T>
    inline void sortSearchResults(const T &cmp) { std::sort(searchResults.begin(), searchResults.end(), cmp); }

public:
    void search(const std::string &query);

    void sortByRelevance() { sortSearchResults(SearchResultCmp::compareRelevance); }

    void sortByTitle() { sortSearchResults(SearchResultCmp::compareTitle); }

    void sortByTitleRev() { sortSearchResults(SearchResultCmp::compareTitleRev); }

    void sortByTime() { sortSearchResults(SearchResultCmp::compareTime); }

    void sortByTimeRev() { sortSearchResults(SearchResultCmp::compareTimeRev); }

    const std::vector<SearchResult> &getSearchResults() const { return searchResults; }
};

#endif