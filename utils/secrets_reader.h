#ifndef SECRETS_READER_H 
#define SECRETS_READER_H

#include <jsoncpp/json/json.h>

#include "../conn/conn_details.h"

class SecretsReader {
private:
    static Json::Value getSecretsValue();

public:
    static MySQLConnectionDetails getConnectionDetails();
};

#endif