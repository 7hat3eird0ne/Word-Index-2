#include "characterSet.hpp"
#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;


CharacterSet::CharacterSet() {}

CharacterSet::CharacterSet(std::vector<std::string> iOrder, bool iCaseSensitive, bool iReverseAppend, int iMinLen)
    : loaded {true}
    , order {iOrder}
    , caseSensitive {iCaseSensitive}
    , reverseAppend {iReverseAppend}
    , minLen {iMinLen}
{}

bool CharacterSet::isLoaded() const {
    return loaded;
}

std::vector<std::string> CharacterSet::getOrder() const {
    return order;
}

bool CharacterSet::isCaseSensitive() const {
    return caseSensitive;
}

bool CharacterSet::isReverseAppend() const {
    return reverseAppend;
}

int CharacterSet::getMinLen() const {
    return minLen;
}