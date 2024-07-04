#include "conn.h"

#include <cppconn/driver.h>
#include <cppconn/statement.h>

MySQLConnector::MySQLConnector(const MySQLConnectionDetails details) {
    conn = getConnection(details);
}

std::unique_ptr<sql::Connection> MySQLConnector::getConnection(const MySQLConnectionDetails details) {
    const std::string &server = details.server;
    const std::string &username = details.username;
    const std::string &password = details.password;
    const std::string &schema = details.schema;

    sql::Driver *driver = get_driver_instance();
    
    std::unique_ptr<sql::Connection> conn(driver->connect(server, username, password));
    conn->setSchema(schema);

    return conn;
}

std::unique_ptr<sql::ResultSet> MySQLConnector::query(std::string sql) {
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    
    return std::unique_ptr<sql::ResultSet>(stmt->executeQuery(sql));
}