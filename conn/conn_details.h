#ifndef CONN_DETAILS_H 
#define CONN_DETAILS_H

#include <string>

struct MySQLConnectionDetails {
    std::string server;
    std::string username;
    std::string password;
    std::string schema;
};

#endif