#include <iostream>

#include "utils/secrets_reader.h"
#include "conn/conn.h"

int main() {
    MySQLConnectionDetails details = SecretsReader::getConnectionDetails();

    MySQLConnector conn = MySQLConnector(details);

    return -1;
}