#ifndef JARO_WINKLER_H
#define JARO_WINKLER_H

#include <string>

namespace JW {
    float getJaroDistance(const std::string &lhs, const std::string &rhs);

    float getJaroSimilarity(const std::string &lhs, const std::string &rhs) { return 1 - getJaroDistance(lhs, rhs); }
}

#endif