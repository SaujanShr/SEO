#ifndef DUMMY_READER_H
#define DUMMY_READER_H

#include "../model/sql_result.h"

#include <vector>

namespace DummyReader {
    std::vector<SQLResult> getDummyResults();
}

#endif