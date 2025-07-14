#include "characterSet.hpp"
#include "logic.hpp"
#include "BigInt.hpp"
#include "json.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using json = nlohmann::json;


// Ask user for a command and return it
char getCommand() {
    while (true) {
        std::cout << "-";
        char oper {};
        std::cin >> oper;
        bool success {std::cin};

        if (std::cin.eof()) {
            std::exit(0);
        }
        if (std::cin.peek() != '\n') {
            success = false;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (oper) {
            case 'h':
            case 'q':
            case 'r':
            case 'f':
            case 'b':
                break;
            default:
                success = false;
        }

        if (success) {
            return oper;
        }
        std::cout << "Enter \'h\' for help.\n";
    }
}

// Ask user for a string and return it
std::string getString() {
    while (true) {
        std::cout << "Enter a string: \n";
        std::string str {};
        std::getline(std::cin >> std::ws, str);
        bool success {std::cin};

        if (std::cin.eof()) {
            std::exit(0);
        }
        std::cin.clear();

        if (success) {
            return str;
        }
        std::cout << "Failed somehow.\n";
    }
}

// Ask user for an index and return it
BigInt getIndex() {
    while (true) {
        std::cout << "Enter an index: ";
        BigInt index {};
        try {
            std::cin >> index;
            bool success {std::cin};
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (std::cin.eof()) {
                std::exit(0);
            }
            if (!success) {
                throw std::invalid_argument("Extraction failed.");
            }

        } catch (const std::invalid_argument& exception) {
            std::cout << "Try again.\n";
            continue;
        }
        return index;
    }
}

enum class ReloadFileReturn {
    file_not_found,
    accurate,
    inaccurate
};

ReloadFileReturn reloadFile(CharacterSet& characterSet, const std::string& filepath) {
    std::ifstream fp {filepath};
    if (!fp) {
        return ReloadFileReturn::file_not_found;
    }

    json jsonCharacterSet {};
    jsonCharacterSet = json::parse(fp);

    CharacterSet characterSetTemp {
        jsonCharacterSet.at("order").get<std::vector<std::string>>(),
        jsonCharacterSet.at("caseSensitive").get<bool>(),
        jsonCharacterSet.at("reverseAppend").get<bool>(),
        jsonCharacterSet.at("minLen").get<int>(),
        jsonCharacterSet.at("strict").get<bool>()
    };
    characterSet = characterSetTemp;

    if (!testCharacterSet(characterSet)) {
        return ReloadFileReturn::inaccurate;
    }

    return ReloadFileReturn::accurate;
}


// Print help
void printHelp() {
    std::cout << "Current available commands:\n";
    std::cout << "  -h\n";
    std::cout << "    - Prints help\n";
    std::cout << "  -q\n";
    std::cout << "    - Quits the program\n";
    std::cout << "  -r\n";
    std::cout << "    - Changes the character set\n";
    std::cout << "  -f\n";
    std::cout << "    - Translates a string into an index\n";
    std::cout << "  -b\n";
    std::cout << "    - Finds a string using an index\n";
}

// Ask user for a path to a json file with new character set
void refile(CharacterSet& characterSet) {
    while (true) {
        std::cout << "Enter a filename (or q to quit reload): ";
        std::string filepath {};
        std::cin >> filepath;

        bool success {std::cin};
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.eof()) {
            std::exit(0);
        }
        if (!success) {
            std::cout << "Failed somehow.\n";
            continue;
        }

        if (filepath == "q") {
            break;
        }


        try {
            ReloadFileReturn refileReturn {reloadFile(characterSet, filepath)};

            if (refileReturn == ReloadFileReturn::file_not_found) {
                std::cout << "File \"" << filepath << "\" not found.\n";
                continue;
            } else if (refileReturn == ReloadFileReturn::inaccurate) {
                std::cout << "The new character set may be inaccurate.\n";
            }
            
        } catch (const json::parse_error& exception) {
            std::cout << "File does not have valid JSON.\n";
            continue;
        } catch (const json::out_of_range& exception) {
            std::cout << "The JSON\'s structure is invalid.\n";
            std::cout << exception.what() << "\n";
            continue;
        } catch (const json::type_error& exception) {
            std::cout << "The JSON\'s structure is invalid.\n";
            std::cout << exception.what() << "\n";
            continue;
        }

        return;
    }
}

// Ask user for a string and print its index
void forward(const CharacterSet& characterSet) {
    std::string str {getString()};
    BigInt index {toIndex(str, characterSet)};

    if (index == WordIndexErrors::toIndexError) {
        std::cout << "Invalid string entered.\n";
        return;
    }
    std::cout << "The string's index: " << index << ".\n";
}

// Ask user for an index and print the corresponding string
void backward(const CharacterSet& characterSet) {
    BigInt index {getIndex()};
    std::string str {fromIndex(index, characterSet)};

    if (index != 0 && str == WordIndexErrors::fromIndexError) {
        std::cout << "Invalid index entered.\n";
        return;
    }
    std::cout << "The index corresponds to a string: \"" << str << "\".\n";
}


int main() {
    CharacterSet characterSet {};
    while (true) {
        char command {getCommand()};
        bool quit {};

        switch (command) {
        case 'h':
            printHelp();
            break;
        case 'q':
            quit = true;
            break;
        case 'r':
            refile(characterSet);
            break;
        case 'f':
            if (!characterSet.isLoaded()) {
                std::cout << "A character set wasn\'t loaded yet.\n";
                break;
            }
            forward(characterSet);
            break;
        case 'b':
            if (!characterSet.isLoaded()) {
                std::cout << "A character set wasn\'t loaded yet.\n";
                break;
            }
            backward(characterSet);
            break;
        default:
            std::cout << "This line of code should be unreachable\?\?\?\n";
        }

        if (quit) {
            break;
        }

        std::cout << "\n";
    }
    return 0;
}