#ifndef WORDINDEX_CHARACTERSET_HPP
#define WORDINDEX_CHARACTERSET_HPP

#include "characterSet.hpp"
#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;

class CharacterSet {
public:
    CharacterSet();
    CharacterSet(std::vector<std::string> order, bool caseSensitive, bool reverseAppend, int minLen);

    bool isLoaded() const;
    std::vector<std::string> getOrder() const;
    bool isCaseSensitive() const;
    bool isReverseAppend() const;
    int getMinLen() const;

private:
    bool loaded {};
    std::vector<std::string> order {};
    bool caseSensitive {true};
    bool reverseAppend {};
    int minLen {};
};

#endif