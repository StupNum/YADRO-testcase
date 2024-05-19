#include <fstream>
#include "FileHandler.h"
#include "common.h"
#include "Time.h"

namespace
{
    bool isValidName(const std::string& string) {
        for (auto ch : string)
            if (!((ch >= '0' && ch <= '9') ||
                (ch >= 'a' && ch <= 'z') ||
                (ch >= 'A' && ch <= 'Z') ||
                ch == '-' || ch == '_')) {
                return false;
            }
        return true;
    }
}


FileHandler::FileHandler(std::string string) : file_path(string) {};

bool FileHandler::ReadFile() {
    std::ifstream input_file(file_path);
    std::string line;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            file_content.push_back(splitString(line));
        }
    }
    else {
        return false;
    }
    return true;
}

// проверка правильности форматирования входного файла
// возврат -1 если ошибок нет,
// или -2 в случае, когда данных для работы программы недостаточно, 
// в остальных случаях неправильного форматирования
// возврат индекса строки с ошибкой

long long FileHandler::ValidateInput() {
    if (file_content.size() < 3)
        return -2;

    std::vector<std::string> line;

    //строка номер 1
    line = file_content[0];
    if (line.size() != 1 || !isNumber(line[0]))
        return 1;

    //строка номер 2
    line = file_content[1];
    if (line.size() != 2 || !Time(line[0]).isValid() || !Time(line[1]).isValid() ||
        Time(line[0]) > Time(line[1]))
        return 2;

    //строка номер 3
    line = file_content[2];
    if (line.size() != 1 || !isNumber(line[0]))
        return 3;

    //остальные строки
    Time time_prev{};
    for (size_t i = 3; i < file_content.size(); i++) {
        line = file_content[i];
        if ((line.size() < 3 || line.size() > 4) ||
            !Time(line[0]).isValid() ||
            time_prev > Time(line[0]) ||
            !isNumber(line[1]) ||
            !isValidName(line[2]) ||
            (std::stoi(line[1]) == 2 && line.size() != 4) ||
            (line.size() == 4 && !isNumber(line[3])) ||
            (line.size() == 4 && (std::stoi(line[3]) < 1 || std::stoi(line[3]) > std::stoi(file_content[0][0]))) ||
            (std::stoi(line[1]) < 1 || std::stoi(line[1]) > 4)) {
            return i;
        }
        time_prev = Time(line[0]);
    }
    return -1;
}

std::vector<std::vector<std::string>>& FileHandler::GetFileContent() {
    return file_content;
}

