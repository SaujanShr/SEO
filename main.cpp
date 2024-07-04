#include <iostream>

#include "util/secrets_reader.h"
#include "conn/conn.h"

int main() {
    const MySQLConnectionDetails mySQL_Details = SecretsReader::getConnectionDetails();

    MySQLConnector conn(mySQL_Details);

    std::vector<SearchResult> results = conn.getResults();

    return -1;
}