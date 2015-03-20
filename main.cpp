#include <iostream>
#include "Brainfuck.h"

int main(int argc, char* argv[]) {
    Brainfuck bf;

    if (argc > 1)
        bf.SetString(argv[1]);
    else
        bf.SetString("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");

    try {
        bf.Go();
    }
    catch (const char* s) {
        std::cout << s << std::endl;
    }

    return 0;
}
