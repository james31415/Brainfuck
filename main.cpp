#include <cstring>
#include <fstream>
#include <string>

#include <cstdio>

typedef unsigned char BYTE;

struct Storage
{
    unsigned int ptr;

    BYTE* m_vStore;
    unsigned int size;
};

void
StorageConstruct(Storage* pThis) {
    pThis->ptr = 0;
    pThis->size = 30000;
    pThis->m_vStore = (BYTE*)malloc(pThis->size * sizeof(pThis->m_vStore));
    memset(pThis->m_vStore, 0, pThis->size);
}

Storage& StorageIncrement(Storage* pThis)
{
    if (pThis->ptr + 1 == pThis->size)
    {
        pThis->size = 3 * pThis->size / 2;
        BYTE* temp = (BYTE*)realloc(pThis->m_vStore, pThis->size);
        if (temp)
        {
            pThis->m_vStore = temp;
        }
        else
        {
            throw "Very sorry";
        }
    }
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
}

void
Go(Brainfuck* pThis) {
    while (pThis->ip != pThis->m_str.length()) {
        const char c = pThis->m_str[pThis->ip];
        switch (c) {
            case '>': StorageIncrement(&pThis->sto); break;
            case '<': StorageDecrement(&pThis->sto); break;
            case '+': ++StorageFetch(&pThis->sto); break;
            case '-': --StorageFetch(&pThis->sto); break;
            case '.': putchar(StorageFetch(&pThis->sto)); break;
            case ',': StorageFetch(&pThis->sto) = getchar(); break;
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
                printf("Need filename. Using hello world.\n");
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

    bf.m_str = parseArguments(argc, argv);

    try {
        Go(&bf);
    } catch (const char* s) {
        printf("%s\n", s);
    }

    return 0;
}
