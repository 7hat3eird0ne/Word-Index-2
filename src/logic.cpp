#include "logic.hpp"
#include "characterSet.hpp"
#include "BigInt.hpp"
#include <string_view>
#include <string>
#include <utility>


// helper functions
namespace {
    // if the character is an uppercase letter, turn it lowercase
    char toLower(char letter) {
        if ('A' <= letter && 'Z' >= letter) {
            return letter + 'a' - 'A';
        }
        return letter;
    }

    std::string toLower(std::string string) {
        for (auto& letter: string) {
            letter = toLower(letter);
        }

        return string;
    }

    int toSign(size_t index) {
        return static_cast<ptrdiff_t>(index);
    }

    size_t toUnsign(int index) {
        return static_cast<size_t>(index);
    }

    void reverseStr(std::string& str) {
        for (int index1 {0}, index2 {toSign(str.size())-1}; index2 > index1; ++index1, --index2) {
            std::swap(str[index1], str[index2]);
        }
    }
}


// Return the index of string, else return "-1";
BigInt toIndex(std::string str, const CharacterSet& characterSet) {
    if (characterSet.getMinLen() > toSign(str.size())) {
        return WordIndexErrors::toIndexError;
    }

    BigInt result {};
    BigInt power {1};
    const int charsetLength {toSign(characterSet.getOrder().size())};

    if (characterSet.isReverseAppend()) {
        reverseStr(str);
    }
    if (!characterSet.isCaseSensitive()) {
        str = toLower(str);
    }
    int index {};
    for (int curIndex {0}; curIndex < toSign(str.size());) {
        bool found {};
        int letterIndex {};
        ++index;
        for (auto tested: characterSet.getOrder()) {
            if (!characterSet.isCaseSensitive()) {
                tested = toLower(tested);
            }
            if (str.substr(toUnsign(curIndex), tested.size()) == tested) {
                curIndex += toSign(tested.size());
                found = true;
                result += letterIndex * power;
                power *= charsetLength;
                break;
            }
            ++letterIndex;
        }
        if (!found) {
            return WordIndexErrors::toIndexError;
        }
        if (index == characterSet.getMinLen()) {
            result -= (power-1)/(charsetLength-1);
        }

    }
    
    result += (power-1)/(charsetLength-1);

    return result;
}

// Return a string, to which corresponds the index, else return an empty string
std::string fromIndex(BigInt index, const CharacterSet& characterSet) {
    if (index < 0) {
        return std::string {WordIndexErrors::fromIndexError};
    }

    const int charsetLength {toSign(characterSet.getOrder().size())};
    int length {1};
    BigInt prevPower {1};
    BigInt power {charsetLength};
    BigInt correct {1};
    while (length <= characterSet.getMinLen() || correct < index) {
        if (length == characterSet.getMinLen()) {
            index += correct;
        }
        ++length;
        prevPower = power;
        power *= charsetLength;
        correct = (power-1)/(charsetLength-1);
    }

    if (correct != index) {
        --length;
        power = prevPower;
        correct = (power-1)/(charsetLength-1);
    }

    BigInt repres {index - correct};
    std::string result {""};
    while (length) {
        std::string pushedChar {characterSet.getOrder().data()[(repres%charsetLength).to_int()]};
        if (!characterSet.isCaseSensitive()) {
            pushedChar = toLower(pushedChar);
        }
        result.append(pushedChar);
        repres /= charsetLength;
        --length;
    }
    if (characterSet.isReverseAppend()) {
        reverseStr(result);
    }

    return result;
}

// Return false if the character set is inaccurate, true otherwise
bool testCharacterSet(const CharacterSet& characterSet) {
    if (!characterSet.isCaseSensitive()) {
        std::vector<std::string> testedStrings {};
        for (const auto& character: characterSet.getOrder()) {
            std::string loweredCharacter = toLower(character);
            for (const auto& testedCharacter: testedStrings) {
                if (loweredCharacter == testedCharacter) {
                    return false;
                }
            }
            testedStrings.push_back(character);
        }
    }

    CharacterSet newCharacterSet {characterSet.getOrder(), characterSet.isCaseSensitive(), characterSet.isReverseAppend(), 0};
    for (int testedIndex {0}; testedIndex < toSign(1 + characterSet.getOrder().size() + characterSet.getOrder().size()*characterSet.getOrder().size()); ++testedIndex) {
        if (testedIndex != toIndex(fromIndex(testedIndex, newCharacterSet), newCharacterSet)) {
            return false;
        }        
    }

    return true;
}