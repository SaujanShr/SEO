#include "jaro_winkler.h"

float JW::getJaroDistance(const std::string &lhs, const std::string &rhs) {
    // Number of matching chars
    float m = 0;

    const int lhsLength = lhs.length();
    const int rhsLength = rhs.length();
    const int maxDistance = (std::max(lhsLength, rhsLength) / 2) - 1;

    bool lhsTable[lhsLength] = { false };
    bool rhsTable[rhsLength] = { false };

    for (int i=0; i<lhsLength; i++) {
        for (int j=std::max(0, i-maxDistance); j<std::min(rhsLength, i+maxDistance+1); j++) {
            if (lhs[i] == rhs[j] && rhsTable[j]) {
                lhsTable[i] = true;
                rhsTable[j] = true;
                m++;

                break;
            }
        }
    }

    if (m == 0) {
        return 0;
    }

    // Number of transpositions
    float t = 0;

    int j = 0;
    for (int i=0; i<lhsLength; i++) {
        if (lhsTable[i]) {
            while (!rhsTable[j]) {
                j++;
            }
            if (lhs[i] != rhs[j++]) {
                t++;
            }
        }
    }
    t /= 2;

    float w = ((m / lhs.length()) + (m / rhs.length()) + ((m - t) / m)) / 3;

    return w;
}