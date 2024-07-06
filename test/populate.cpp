#include "populate.h"

#include "../conn/conn.h"
#include "../sql/stored_statement.h"
#include "../util/dummy_reader.h"

#include <fmt/format.h>

namespace {
    const std::string getSQL_Value(const SQLResult &result) {
        const std::string &uuid = result.uuid;
        const std::string &title = result.title;
        const std::string &content = result.content;
        const std::time_t time = result.time;

        return fmt::format("('{}', '{}', '{}', {})", uuid, title, content, time);
    }

    const std::string getSQL_Values(const std::vector<SQLResult> &results) {
        std::string sqlResultValues;

        std::vector<SQLResult>::const_iterator start = results.begin();

        if (start != results.end()) {
            sqlResultValues += getSQL_Value(*start);
        }
        for (std::vector<SQLResult>::const_iterator it=start; it!=results.end(); it++) {
            sqlResultValues += fmt::format(", {}", getSQL_Value(*it));
        }

        return sqlResultValues;
    }
}

void Populate::populateResults() {
    const MySQLConnector conn;
    const std::vector<SQLResult> results = DummyReader::getDummyResults();

    const std::string stmtValues = getSQL_Values(results);
    const std::string stmtPopulateResults = fmt::format(StoredStmt::POPULATE_RESULTS_TEMPLATE, stmtValues);

    conn.execute(StoredStmt::FLUSH_RESULTS);
    conn.execute(stmtPopulateResults);
}