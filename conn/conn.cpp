#include "conn.h"

#include <ctime>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

const std::string SCHEMA = "search";
const std::string GET_RESULTS_QUERY = "SELECT uuid, title, content, time, ref FROM results;";

MySQLConnector::MySQLConnector(const MySQLConnectionDetails details) {
    conn = getConnection(details);
}

std::unique_ptr<sql::Connection> MySQLConnector::getConnection(const MySQLConnectionDetails details) {
    const std::string &server = details.server;
    const std::string &username = details.username;
    const std::string &password = details.password;

    sql::Driver *driver = get_driver_instance();
    
    std::unique_ptr<sql::Connection> conn(driver->connect(server, username, password));
    conn->setSchema(SCHEMA);

    return conn;
}

std::unique_ptr<sql::ResultSet> MySQLConnector::getQueryResults() {
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    
    return std::unique_ptr<sql::ResultSet>(stmt->executeQuery(GET_RESULTS_QUERY));
}

std::vector<SearchResult> MySQLConnector::processQueryResults(std::unique_ptr<sql::ResultSet> queryResults) {
    std::vector<SearchResult> results;

    queryResults->beforeFirst();
    while (queryResults->next()) {
        const std::string UUID = queryResults->getString("UUID");
        const std::string title = queryResults->getString("title");
        const std::string content = queryResults->getString("content");
        const std::time_t time = queryResults->getInt64("time");
        const int64_t ref = queryResults->getInt64("ref");

        SearchResult result { UUID, title, content, time, ref };
        results.push_back(result);
    }

    return results;
}

std::vector<SearchResult> MySQLConnector::getResults() {
    std::unique_ptr<sql::ResultSet> queryResults = getQueryResults();
    std::vector<SearchResult> results = processQueryResults(std::move(queryResults));

    return results;
}