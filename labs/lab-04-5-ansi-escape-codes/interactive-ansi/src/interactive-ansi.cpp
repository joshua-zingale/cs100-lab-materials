#include<iostream>
#include<stdlib.h>

#include<ansi.hpp>

int main(int argc, char *argv[]) {
    int height, width;
    if (argc != 3 || (height = atoi(argv[1])) <= 0 || (width = atoi(argv[2]) ) <= 0) {
        std::cerr << "Usage:  " << argv[0] << " <HEIGHT> <WIDTH>" << std::endl;
        return 1;
    }

    std::cout
    << ansi::clearScreen
    << ansi::moveCursor(0,0)
    << ansi::save
    << std::flush;


    std::string input = "";
    std::cout << ansi::moveCursor(height-1, 1) << "> " << std::flush;
    bool first = true;
    while (first || std::getline(std::cin, input)) {
        first = false;
        std::string unescapedInput = ansi::unescape(input);

        std::cout << ansi::load << unescapedInput << ansi::save;

        std::cout << ansi::moveCursor(height-2, 1);
        for (int i = 0; i < width; ++i) std::cout << '~';

        std::cout
        << ansi::moveCursor(height-1, 1)
        << ansi::clearScreenFromCursor
        << "> " << std::flush;
    }

    
    return 1;
}

