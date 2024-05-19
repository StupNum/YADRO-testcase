#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <string>
#include <vector>

class FileHandler {
public:
    FileHandler(std::string string);

    bool ReadFile();

    long long ValidateInput();

    std::vector<std::vector<std::string>>& GetFileContent();

private:
    std::string file_path{};
    std::vector<std::vector<std::string>> file_content{};

};
#endif // FILEHANDLER_H