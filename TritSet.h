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
        cellTritSet* cell_set;

    public:
        iterator(const cellTritSet& set);
        void operator++();
        bool operator!=(TritSet::iterator it);
        bool operator==(Trit set);
        iterator operator=(Trit set);
        iterator operator=(TritSet::iterator set);
    };

    iterator begin();
    iterator end();
};


class cellTritSet {
private:
    TritSet* trit_set;
    unsigned int index;
friend class TritSet::iterator;
public:
    cellTritSet(TritSet* set, unsigned int index);

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
