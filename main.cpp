#include <iostream>
#include <fstream>
#include <cstring>
#include "Brainfuck.h"

void readString(std::fstream& fs, std::string& out)
{
    while (fs)
    {
        std::string temp;
        fs >> temp;
        out += temp;
    }
}

std::string parseArguments(int argc, char* argv[]) {
    if (argc > 1) {
        if (std::strncmp(argv[1], "-f", 2) == 0) {
            if (argc > 2) {
                std::fstream fs(argv[2]);
                std::string str;
                readString(fs, str);
                return str;
            } else {
                std::cout << "Need filename. Using hello world." << std::endl;
            }
        } else {
            return argv[1];
        }
    }

    return "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.++++++\
        +..+++.>>.<-.<.+++.------.--------.>>+.>++.";
}

int main(int argc, char* argv[]) {
    Brainfuck bf;

    std::string str = parseArguments(argc, argv);
    bf.SetString(str);

    try {
        bf.Go();
    } catch (const char* s) {
        std::cout << s << std::endl;
    }

    return 0;
}
