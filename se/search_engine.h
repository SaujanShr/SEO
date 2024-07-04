#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <functional>

#include "../conn/conn.h"
#include "../model/search_result.h"
#include "cmp.h"

class SearchEngine {
private:
    const MySQLConnector conn;

    std::vector<SearchResult> searchResults;

    const MySQLConnector getConnector() const;

    const std::unique_ptr<sql::ResultSet> getQueryResults() const;

    float computeSimilarity(const std::string &query, const std::string &title, const std::string &content) const;

    std::vector<SearchResult> processQueryResults(const std::string &query, const std::unique_ptr<sql::ResultSet> &queryResults) const;

    const std::string getSQL_Value(const SearchResult &result) const;

    const std::string getSQL_Values(const std::vector<SearchResult> &results) const;

    template<typename T>
    void sortSearchResults(const T &cmp) { std::sort(searchResults.begin(), searchResults.end(), cmp); }

public:
    SearchEngine(): conn(getConnector()) {};

    void populateResults() const;

    void search(std::string query);

    void sortByRelevance();

    void sortByTitle(bool rev = false);

    void sortByTime(bool rev = false);

    const std::vector<SearchResult> &getSearchResults() const { return searchResults; }
};

#endif