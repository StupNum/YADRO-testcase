#include "common.h"


size_t backspaceCount(const std::string string) {
    size_t result = 0;
    for (const auto var : string)
        if (var == ' ')
            result++;
    return result;

}

std::string vec2string(const std::vector<std::string>& input) {
    std::string output;
    if (input.size() > 0)
        output += input[0];
    for (size_t i = 1; i < input.size(); ++i) {
        output += ' ' + input[i];
    }
    return output;
}

std::vector<std::string> splitString(const std::string& string) {
    std::vector<std::string> result;
    std::string temp;

    for (const auto ch : string) {
        if (ch != ' ') {
            temp += ch;
        }
        else if (ch == ' ') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    return result;
}
