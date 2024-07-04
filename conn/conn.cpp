#include "conn.h"

#include <ctime>
#include <fmt/format.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

const std::string SCHEMA = "search";

const std::unique_ptr<sql::Connection> MySQLConnector::getConnection(const MySQLConnectionDetails &details) const {
    const std::string &server = details.server;
    const std::string &username = details.username;
    const std::string &password = details.password;

    sql::Driver *driver = get_driver_instance();
    sql::Connection *conn = driver->connect(server, username, password);
    conn->setSchema(SCHEMA);

    return std::unique_ptr<sql::Connection>(conn);
}

const std::unique_ptr<sql::ResultSet> MySQLConnector::query(const std::string &sql) const {
    sql::ResultSet *queryResults = conn
        ->createStatement()
        ->executeQuery(sql);

    return std::unique_ptr<sql::ResultSet>(queryResults);
}

void MySQLConnector::execute(const std::string &sql) const {
    conn->createStatement()->execute(sql);
}
