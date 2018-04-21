#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned char BYTE;

typedef std::vector<BYTE> Internal;

class Storage
{
    public:
        Storage();
        Storage& operator++();
        Storage& operator--();
        BYTE& operator*();
        const BYTE& operator*() const;
        friend std::ostream& operator<<(std::ostream& os, const Storage& sto);

    private:
        unsigned int ptr;
        Internal m_vStore;
};

Storage::Storage() {
    ptr = 0;
    m_vStore.push_back(0);
}

Storage& Storage::operator++() {
    if (ptr + 1 == m_vStore.size())
        m_vStore.push_back(0);
    ++ptr;

    return *this;
}

Storage& Storage::operator--() {
    if (ptr == 0)
        throw "Sorry";
    --ptr;

    return *this;
}

BYTE& Storage::operator*() {
    return m_vStore[ptr];
}

const BYTE& Storage::operator*() const {
    return m_vStore[ptr];
}

std::ostream& operator<<(std::ostream& os, const Storage& sto) {
    os << "(" << sto.ptr << ") " << static_cast<unsigned int>(sto.m_vStore[sto.ptr]);

    return os;
}

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

Brainfuck::Brainfuck() : ip(0) { std::cin >> std::noskipws; }

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
            default: break;
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
