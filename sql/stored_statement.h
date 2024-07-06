#ifndef STORED_STATEMENT_H
#define STORED_STATEMENT_H

#include <string>

namespace StoredStmt {
    const std::string FLUSH_RESULTS = "DELETE * FROM results;";

    const std::string GET_RESULTS_TEMPLATE = 
        "SELECT uuid, title, content, time, ref, levenshtein_similarity({}, title) AS relevance"
        "FROM results"
        "WHERE relevance > 10;";

    const std::string POPULATE_RESULTS_TEMPLATE = "INSERT INTO search (uuid, title, content, time) VALUES {};";
}

#endif