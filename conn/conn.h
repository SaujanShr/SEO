#ifndef CONN_H
#define CONN_H

#include <string>
#include <cppconn/resultset.h>

#include "../model/conn_details.h"
#include "../model/search_result.h"
#include "mysql_connection.h"

class MySQLConnector {
private:
    const std::unique_ptr<sql::Connection> conn;

public:
    MySQLConnector();

    const std::unique_ptr<sql::ResultSet> query(const std::string &sql) const;

    void execute(const std::string &sql) const;
};

#endif