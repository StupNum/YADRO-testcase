#include <iostream>
#include "FileHandler.h"
#include "GameClub.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Error: File name not entered!\n" << std::endl;
        return 0;
    }
    
    FileHandler FH_instance(argv[1]);
    GameClub GC_instance{};

    try {
        GameClub::ProccessFileInfo(GC_instance, FH_instance);
    }
    catch (const std::runtime_error& exception) {
        std::cout << "Error: " << exception.what() << '\n';
    }
    return 0;
}
