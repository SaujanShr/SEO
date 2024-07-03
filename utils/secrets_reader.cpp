#include "secrets_reader.h"

#include <fstream>
#include <string>

const std::string secretsFileLocation = "secrets.json";

Json::Value SecretsReader::getSecretsValue() {
    Json::Value secretsValue;

    std::ifstream secretsFile(secretsFileLocation);
    secretsFile >> secretsValue;

    return secretsValue;
}

MySQLConnectionDetails SecretsReader::getConnectionDetails() {
    const Json::Value secretsValue = getSecretsValue();
    const Json::Value &connectionDetailsValue = secretsValue["connectionDetails"];

    std::string server = connectionDetailsValue["server"].asString();
    std::string username = connectionDetailsValue["username"].asString();
    std::string password = connectionDetailsValue["password"].asString();
    std::string schema = connectionDetailsValue["schema"].asString();

    return MySQLConnectionDetails { server, username, password, schema };
}