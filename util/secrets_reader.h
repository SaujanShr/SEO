#ifndef SECRETS_READER_H 
#define SECRETS_READER_H

#include "../model/conn_details.h"

#include <jsoncpp/json/json.h>

namespace SecretsReader {
    MySQLConnectionDetails getConnectionDetails();
}

#endif