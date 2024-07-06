#include "secrets_reader.h"

#include <fstream>

const std::string SECRETS_FILE_LOCATION = "secrets.json";

static Json::Value getSecretsValue() {
    Json::Value secretsValue;

    std::ifstream secretsFile(SECRETS_FILE_LOCATION);
    secretsFile >> secretsValue;

    return secretsValue;
}

MySQLConnectionDetails SecretsReader::getConnectionDetails() {
    const Json::Value secretsValue = getSecretsValue();
    const Json::Value &connectionDetailsValue = secretsValue["connectionDetails"];

    const std::string &server = connectionDetailsValue["server"].asString();
    const std::string &username = connectionDetailsValue["username"].asString();
    const std::string &password = connectionDetailsValue["password"].asString();

    return MySQLConnectionDetails { server, username, password };
}