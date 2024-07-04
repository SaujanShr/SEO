#include "search_engine.h"

#include <fmt/format.h>

#include "../util/secrets_reader.h"
#include "../util/jaro_winkler.h"

const std::string GET_RESULTS_QUERY = "SELECT uuid, title, content, time, ref FROM results;";
const std::string POPULATE_RESULTS_TEMPLATE = "INSERT INTO search (uuid, title, content, time, ref) VALUES {};";

const MySQLConnector SearchEngine::getConnector() const {
    MySQLConnectionDetails details = SecretsReader::getConnectionDetails();

    return MySQLConnector(details);
}

const std::unique_ptr<sql::ResultSet> SearchEngine::getQueryResults() const {
    return conn.query(GET_RESULTS_QUERY);
}

float SearchEngine::computeSimilarity(const std::string &query, const std::string &title, const std::string &content) const {
    float title_sim = JW::getJaroSimilarity(query, title);
    float content_sim = JW::getJaroSimilarity(query, content);

    return title_sim + content_sim/3;
}

std::vector<SearchResult> SearchEngine::processQueryResults(const std::string &query, const std::unique_ptr<sql::ResultSet> &queryResults) const {
    std::vector<SearchResult> results;

    queryResults->beforeFirst();
    while (queryResults->next()) {
        const std::string &uuid = queryResults->getString("uuid");
        const std::string &title = queryResults->getString("title");
        const std::string &content = queryResults->getString("content");
        const std::time_t time = queryResults->getInt64("time");
        const int64_t ref = queryResults->getInt64("ref");

        const float sim = computeSimilarity(query, title, content);

        results.push_back(SearchResult { uuid, title, content, time, ref, sim });
    }

    return results;
}

const std::string SearchEngine::getSQL_Value(const SearchResult &result) const {
    const std::string &uuid = result.uuid;
    const std::string &title = result.title;
    const std::string &content = result.content;
    const std::time_t time = result.time;
    const int64_t ref = result.ref;

    return fmt::format("('{}', '{}', '{}', {}, {})", uuid, title, content, time, ref);
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