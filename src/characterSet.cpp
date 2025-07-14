#include "characterSet.hpp"
#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;


// Default constructor
CharacterSet::CharacterSet() {}

// Construct using the parameters
CharacterSet::CharacterSet(std::vector<std::string> iOrder, bool iCaseSensitive, bool iReverseAppend, int iMinLen, bool iStrict)
    : loaded {true}
    , order {iOrder}
    , caseSensitive {iCaseSensitive}
    , reverseAppend {iReverseAppend}
    , minLen {iMinLen}
    , strict {iStrict}
{}

// Return CharacterSet.loaded
bool CharacterSet::isLoaded() const {
    return loaded;
}

// Return CharacterSet.order
std::vector<std::string> CharacterSet::getOrder() const {
    return order;
}

// Return CharacterSet.caseSensitive
bool CharacterSet::isCaseSensitive() const {
    return caseSensitive;
}

// Return CharacterSet.reverseAppend
bool CharacterSet::isReverseAppend() const {
    return reverseAppend;
}

// Return CharacterSet.minLen
int CharacterSet::getMinLen() const {
    return minLen;
}

// Return CharacterSet.strict
bool CharacterSet::isStrict() const {
    return strict;
}