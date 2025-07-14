#ifndef WORDINDEX_LOGIC_HPP
#define WORDINDEX_LOGIC_HPP

#include "characterSet.hpp"
#include "BigInt.hpp"
#include <string>
#include <string_view>

namespace WordIndexErrors {
    constexpr int toIndexError {-1};
    constexpr std::string_view fromIndexError {""};
}

BigInt toIndex(std::string string, const CharacterSet& characterSet);

std::string fromIndex(BigInt index, const CharacterSet& characterSet);

bool testCharacterSet(const CharacterSet& characterSet);

#endif