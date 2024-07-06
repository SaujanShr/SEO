#include "conn.h"

#include "../util/secrets_reader.h"

#include <ctime>
#include <cppconn/driver.h>
#include <cppconn/statement.h>

const std::string SCHEMA = "search";

static const std::unique_ptr<sql::Connection> getConnection() {
    const MySQLConnectionDetails details = SecretsReader::getConnectionDetails();

    const std::string &server = details.server;
    const std::string &username = details.username;
    const std::string &password = details.password;

    sql::Driver *driver = get_driver_instance();
    sql::Connection *conn = driver->connect(server, username, password);
    conn->setSchema(SCHEMA);

    return std::unique_ptr<sql::Connection>(conn);
}

MySQLConnector::MySQLConnector(): conn(getConnection()) {}

const std::unique_ptr<sql::ResultSet> MySQLConnector::query(const std::string &sql) const {
    sql::ResultSet *queryResults = conn
        ->createStatement()
        ->executeQuery(sql);

    return std::unique_ptr<sql::ResultSet>(queryResults);
}

void MySQLConnector::execute(const std::string &sql) const {
    conn->createStatement()->execute(sql);
}
