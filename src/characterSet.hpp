#ifndef WORDINDEX_CHARACTERSET_HPP
#define WORDINDEX_CHARACTERSET_HPP

#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;

class CharacterSet {
public:
    CharacterSet();
    CharacterSet(std::vector<std::string> iOrder, bool iCaseSensitive, bool iReverseAppend, int iMinLen, bool iStrict);

    bool isLoaded() const;
    std::vector<std::string> getOrder() const;
    bool isCaseSensitive() const;
    bool isReverseAppend() const;
    int getMinLen() const;
    bool isStrict() const;

private:
    bool loaded {};
    std::vector<std::string> order {};
    bool caseSensitive {true};
    bool reverseAppend {};
    int minLen {};
    bool strict {};
};

#endif