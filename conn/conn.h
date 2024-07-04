#ifndef CONN_H
#define CONN_H

#include <string>
#include <cppconn/resultset.h>

#include "../model/conn_details.h"
#include "../model/search_result.h"
#include "mysql_connection.h"

class MySQLConnector {
private:
    std::unique_ptr<sql::Connection> conn;

    std::unique_ptr<sql::Connection> getConnection(const MySQLConnectionDetails details);

    std::unique_ptr<sql::ResultSet> getQueryResults();

    std::vector<SearchResult> processQueryResults(std::unique_ptr<sql::ResultSet> queryResults);

public:
    MySQLConnector(const MySQLConnectionDetails details);

    std::vector<SearchResult> getResults();
};

#endif