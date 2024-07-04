#include <iostream>

#include "utils/secrets_reader.h"
#include "conn/conn.h"

int main() {
    const MySQLConnectionDetails mySQL_Details = SecretsReader::getConnectionDetails();

    MySQLConnector conn(mySQL_Details);

    std::unique_ptr<sql::ResultSet> res = conn.query("SHOW SCHEMAS;");

    while (res->next()) {
        std::cout << res->getString(1) << std::endl;
    }

    return -1;
}