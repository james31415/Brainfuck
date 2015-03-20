#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
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

#endif /* STORAGE_H */

