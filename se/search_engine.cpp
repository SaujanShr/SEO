#include "search_engine.h"

#include <fmt/format.h>

#include "../sql/stored_statement.h"
#include "../util/secrets_reader.h"

const MySQLConnector SearchEngine::getConnector() const {
    MySQLConnectionDetails details = SecretsReader::getConnectionDetails();

    return MySQLConnector(details);
}

const std::unique_ptr<sql::ResultSet> SearchEngine::getSearchResults(const std::string &query) const {
    const std::string sql = fmt::format(StoredStmt::GET_RESULTS_TEMPLATE, query, query);

    return conn.query(sql);
}

std::vector<SearchResult> SearchEngine::processSearchResults(const std::unique_ptr<sql::ResultSet> &queryResults) const {
    std::vector<SearchResult> results;

    queryResults->beforeFirst();
    while (queryResults->next()) {
        const std::string &uuid = queryResults->getString("uuid");
        const std::string &title = queryResults->getString("title");
        const std::string &content = queryResults->getString("content");
        const std::time_t time = queryResults->getInt64("time");
        const int64_t ref = queryResults->getInt64("ref");

        const double relevance = queryResults->getDouble("relevance");

        results.push_back(SearchResult { uuid, title, content, time, relevance });
    }

    return results;
}

const std::string SearchEngine::getSQL_Value(const SearchResult &result) const {
    const std::string &uuid = result.uuid;
    const std::string &title = result.title;
    const std::string &content = result.content;
    const std::time_t time = result.time;

    return fmt::format("('{}', '{}', '{}', {})", uuid, title, content, time);
}

const std::string SearchEngine::getSQL_Values(const std::vector<SearchResult> &results) const {
    std::string sqlResultValues;

    std::vector<SearchResult>::const_iterator it = results.begin();

    if (it != results.end()) {
        sqlResultValues += getSQL_Value(*it);
    }
    while (++it != results.end()) {
        sqlResultValues += fmt::format(", {}", getSQL_Value(*it));
    }

    return sqlResultValues;
}

const std::vector<SearchResult> SearchEngine::getDummyResults() const {
    return std::vector<SearchResult>();
}

void SearchEngine::populateResults() const {
    std::vector<SearchResult> results;

    // TODO

    const std::string SQL_Values = getSQL_Values(results);
    const std::string SQL_PopulateResults = fmt::format(StoredStmt::POPULATE_RESULTS_TEMPLATE, SQL_Values);

    conn.execute(StoredStmt::FLUSH_RESULTS);
    conn.execute(SQL_PopulateResults);
}

void SearchEngine::search(const std::string &query) {
    const std::unique_ptr<sql::ResultSet> queryResults = getSearchResults(query);

    searchResults = processSearchResults(queryResults);
}