#include <iostream>
#include "Brainfuck.h"

Brainfuck::Brainfuck() : ip(0) {}

Brainfuck::Brainfuck(const std::string& str) : ip(0), m_str(str) {
}

void Brainfuck::SetString(const std::string& str) { m_str = str; }

void Brainfuck::Go() {
#if _DEBUG
    int i = 0;
#endif
    while (ip != m_str.length()) {
        const char c = m_str[ip];
#if _DEBUG
        std::cout << ++i << ": " << c << ": " << sto << std::endl;
#endif
        switch (c) {
            case '>': GT(); break;
            case '<': LT(); break;
            case '+': PL(); break;
            case '-': MI(); break;
            case '.': DT(); break;
            case ',': CM(); break;
            case '[': OB(); break;
            case ']': CB(); break;
            default: throw "Invalid input"; break;
        };
        ++ip;
    }
}

void Brainfuck::GT() {
    ++sto;
}

void Brainfuck::LT() {
    --sto;
}

void Brainfuck::PL() {
    ++*sto;
}

void Brainfuck::MI() {
    --*sto;
}

void Brainfuck::DT() {
    std::cout << *sto;
}

void Brainfuck::CM() {
    std::cin >> *sto;
}

void Brainfuck::OB() {
   if (*sto == 0)
   {
       int iDepth = 1;
       while (iDepth > 0) {
           ++ip;
           switch (m_str[ip]) {
               case '[': ++iDepth; break;
               case ']': --iDepth; break;
               default: break;
           };
       }
   }
}

void Brainfuck::CB() {
    if (*sto != 0)
    {
        int iDepth = 1;
        while (iDepth > 0) {
            --ip;
            switch (m_str[ip]) {
                case '[': --iDepth; break;
                case ']': ++iDepth; break;
                default: break;
            };
        }
    }
}


