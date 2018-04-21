#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned char BYTE;

typedef std::vector<BYTE> Internal;

struct Storage
{
    friend std::ostream& operator<<(std::ostream& os, const Storage& sto);

    unsigned int ptr;
    Internal m_vStore;
};

void
StorageConstruct(Storage* pThis) {
    pThis->ptr = 0;
    pThis->m_vStore.push_back(0);
}

Storage& StorageIncrement(Storage* pThis)
{
    if (pThis->ptr + 1 == pThis->m_vStore.size())
        pThis->m_vStore.push_back(0);
    ++pThis->ptr;

    return *pThis;
}

Storage& StorageDecrement(Storage* pThis)
{
    if (pThis->ptr == 0)
        throw "Sorry";
    --pThis->ptr;

    return *pThis;
}

BYTE&
StorageFetch(Storage* pThis)
{
    return pThis->m_vStore[pThis->ptr];
}

std::ostream& operator<<(std::ostream& os, const Storage& sto) {
    os << "(" << sto.ptr << ") " << static_cast<unsigned int>(sto.m_vStore[sto.ptr]);

    return os;
}

struct Brainfuck
{
    unsigned int ip;
    std::string m_str;
    Storage sto;
};

void
BrainfuckConstruct(Brainfuck* pThis)
{
    pThis->ip = 0;
    StorageConstruct(&pThis->sto);
    std::cin >> std::noskipws;
}

void
Go(Brainfuck* pThis) {
#if _DEBUG
    int i = 0;
#endif
    while (pThis->ip != pThis->m_str.length()) {
        const char c = pThis->m_str[pThis->ip];
#if _DEBUG
        std::cout << ++i << ": " << c << ": " << pThis->sto << std::endl;
#endif
        switch (c) {
            case '>': StorageIncrement(&pThis->sto); break;
            case '<': StorageDecrement(&pThis->sto); break;
            case '+': ++StorageFetch(&pThis->sto); break;
            case '-': --StorageFetch(&pThis->sto); break;
            case '.': std::cout << StorageFetch(&pThis->sto); break;
            case ',': std::cin >> StorageFetch(&pThis->sto); break;
            case '[': 
            {
                if (StorageFetch(&pThis->sto) == 0)
                {
                    int iDepth = 1;
                    while (iDepth > 0)
                    {
                        ++pThis->ip;
                        switch (pThis->m_str[pThis->ip]) {
                            case '[': ++iDepth; break;
                            case ']': --iDepth; break;
                            default: break;
                        };
                    }
                }
            } break;
            case ']':
            {
                if (StorageFetch(&pThis->sto) != 0)
                {
                    int iDepth = 1;
                    while (iDepth > 0) {
                        --pThis->ip;
                        switch (pThis->m_str[pThis->ip])
                        {
                            case '[': --iDepth; break;
                            case ']': ++iDepth; break;
                            default: break;
                        };
                    }
                }
            } break;
            default: break;
        };
        ++pThis->ip;
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
    BrainfuckConstruct(&bf);

    std::string str = parseArguments(argc, argv);
    bf.m_str = str;

    try {
        Go(&bf);
    } catch (const char* s) {
        std::cout << s << std::endl;
    }

    return 0;
}
