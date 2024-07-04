#ifndef CONN_H
#define CONN_H

#include <string>
#include <cppconn/resultset.h>

#include "mysql_connection.h"
#include "conn_details.h"

class MySQLConnector {
private:
    std::unique_ptr<sql::Connection> conn;

    std::unique_ptr<sql::Connection> getConnection(const MySQLConnectionDetails details);

public:
    MySQLConnector(const MySQLConnectionDetails details);

    std::unique_ptr<sql::ResultSet> query(std::string sql);
};

#endif