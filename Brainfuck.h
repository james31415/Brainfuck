#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <string>
#include "Storage.h"

class Brainfuck
{
    public:
        Brainfuck();
        Brainfuck(const std::string& str);
        void SetString(const std::string& str);
        void Go();

    private:
        void GT();
        void LT();
        void PL();
        void MI();
        void DT();
        void CM();
        void OB();
        void CB();
        unsigned int ip;
        std::string m_str;
        Storage sto;
};

#endif /* BRAINFUCK_H */

