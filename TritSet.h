//
// Created by Alena on 11.02.2022.
//

#ifndef UNTITLED_TRITSET_H
#define UNTITLED_TRITSET_H

#include <iostream>
#include <vector>
#include <unordered_map>

enum Trit {
    UNKNOWN,
    FALSE,
    TRUE = 3
};

bool operator==(unsigned int value_uint, Trit value);

class cellTritSet;
class TritSet;

class TritSet {
private:
    friend class cellTritSet;
    std::vector <unsigned int> vector_uint;
    size_t capacity;

public:
    TritSet(unsigned int capacity);
    TritSet();

    size_t get_capacity() const;
    void shrink();
    void trim(unsigned int LastIndex);
    size_t get_ln_vecor() const;
    size_t cardinality(Trit value) const;
    size_t lenght() const;
    std::unordered_map< Trit, int, std::hash<int> > cardinality();

    Trit operator[](unsigned int index) const;
    cellTritSet operator[](unsigned int index);
    TritSet operator=(const TritSet& set);
    TritSet operator&(const TritSet& set);
    TritSet operator|(const TritSet& set);
    TritSet operator~();
    class iterator{
    private:
        TritSet* trit_set;
        unsigned int index;

    public:
        iterator(TritSet* trit_set, unsigned int index);
        void operator++(int);
        void operator++();

        iterator operator*()  const;
        cellTritSet operator*();

        bool operator!=(const iterator& it) const;
        bool operator==(const iterator& it) const;
        bool operator==(const Trit& set) const;
        iterator operator=(const Trit& set);
        iterator operator=(const iterator& set);
    };

    iterator begin();
    iterator end();
};

class cellTritSet {
private:
    TritSet* trit_set;
    unsigned int index;
public:
    cellTritSet(TritSet* set, unsigned int index);
    cellTritSet();

    const TritSet* getTritSet()  {return trit_set;};

    cellTritSet operator=(Trit value);
    cellTritSet operator=(const cellTritSet& set);
    bool operator==(Trit set) const;
    bool operator==(const cellTritSet& set) const;
    Trit operator&(const  cellTritSet& set) const;
    Trit operator&(Trit set) const;
    Trit operator|(const cellTritSet& set) const;
    Trit operator|(Trit set) const;
    Trit operator~() const;
};

#endif //UNTITLED_TRITSET_H
