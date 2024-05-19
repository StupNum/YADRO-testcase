#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>


size_t backspaceCount(const std::string string);

inline bool isDigit(const char ch) {
    return (ch >= '0' && ch <= '9');
}

inline bool isNumber(const std::string& string) {
    for (auto ch : string)
        if (!isDigit(ch))
            return false;
    return true;
}

std::vector<std::string> splitString(const std::string& string);

std::string vec2string(const std::vector<std::string>& input);


#endif // COMMON_H
