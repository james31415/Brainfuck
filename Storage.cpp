#include "Storage.h"

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
