#ifndef SECRETS_READER_H 
#define SECRETS_READER_H

#include <jsoncpp/json/json.h>

#include "../model/conn_details.h"

namespace SecretsReader {
    MySQLConnectionDetails getConnectionDetails();
}

#endif