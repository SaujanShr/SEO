#include "search_engine.h"

#include <fmt/format.h>

#include "../sql/stored_statement.h"
#include "../util/secrets_reader.h"


const std::unique_ptr<sql::ResultSet> SearchEngine::getQueryResultSet(const std::string &query) const {
    const std::string sql = fmt::format(StoredStmt::GET_RESULTS_TEMPLATE, query);

    return conn.query(sql);
}

std::vector<SearchResult> SearchEngine::processQueryResultSet(const std::unique_ptr<sql::ResultSet> &queryResultSet) const {
    std::vector<SearchResult> results;

    queryResultSet->beforeFirst();
    while (queryResultSet->next()) {
        const std::string &uuid = queryResultSet->getString("uuid");
        const std::string &title = queryResultSet->getString("title");
        const std::string &content = queryResultSet->getString("content");

        const std::time_t time = queryResultSet->getInt64("time");
        const int64_t ref = queryResultSet->getInt64("ref");
        const double relevance = queryResultSet->getDouble("relevance");

        results.push_back(SearchResult { uuid, title, content, time, relevance });
    }

    return results;
}

void SearchEngine::search(const std::string &query) {
    const std::unique_ptr<sql::ResultSet> res = getQueryResultSet(query);

    searchResults = processQueryResultSet(res);
}