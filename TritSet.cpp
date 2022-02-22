#include "TritSet.h"

bool operator==(unsigned int value_uint,Trit value) {
    if (value == TRUE && value_uint == 3)
        return true;

    else if (value == FALSE && value_uint == 1)
        return true;

    else if (value == UNKNOWN && value_uint == 0)
        return true;

    else
        return false;
}

TritSet::TritSet(unsigned int capacity) {
    this->capacity = capacity;
    unsigned int qt_uint = capacity * 2 / (8 * sizeof(unsigned int));

    if (((capacity * 2) % (8 * sizeof(unsigned int))) != 0)
        qt_uint += 1;

    vector_uint.resize(qt_uint, 0);
}

TritSet::TritSet() {
    this->capacity = 0;
    vector_uint.resize(0, 0);
}

size_t TritSet::get_capacity() const{
    return  capacity;
}

void TritSet::shrink() {
    int new_qt_trit = capacity - 1;
    for (new_qt_trit; new_qt_trit >= 0 && (*this)[new_qt_trit] == UNKNOWN; new_qt_trit -= 1);

    unsigned int qt_uint = new_qt_trit * 2 / (8 * sizeof(unsigned int));

    if (((new_qt_trit * 2) % (8 * sizeof(unsigned int))) != 0)
        qt_uint += 1;

    capacity = new_qt_trit + 1;
    vector_uint.resize(qt_uint);
}

void TritSet::trim(unsigned int LastIndex) {
    unsigned int num_uint = LastIndex / (4 * sizeof(unsigned int));

    capacity = LastIndex + 1;
    vector_uint.resize(num_uint);

    unsigned int LastIndex_uint = (num_uint + 1) * (4 * sizeof(unsigned int));

    for (LastIndex; LastIndex < LastIndex_uint - 1; LastIndex += 1)
        (*this)[LastIndex + 1] = UNKNOWN;
}

size_t TritSet::get_ln_vecor() const{
    return vector_uint.size();
}
size_t TritSet::cardinality(Trit value) const{
    int count = 0;

    for (int i = 0; i < capacity; i += 1)
        if ((*this)[i] == value)
            count += 1;

    return count;
}

size_t TritSet::lenght() const{
    int new_qt_trit = capacity - 1;

    for (new_qt_trit; new_qt_trit >= 0 && (*this)[new_qt_trit] == UNKNOWN; new_qt_trit -= 1);

    return new_qt_trit + 1;
}

std::unordered_map<Trit, int, std::hash<int>> TritSet::cardinality() {
    std::unordered_map<Trit, int, std::hash<int>> map;

    for (int i = 0; i < capacity; i += 1) {
        if ((*this)[i] == TRUE)
            map[TRUE]++;

        else if ((*this)[i] == FALSE)
            map[FALSE]++;

        else
            map[UNKNOWN]++;

    }

    return map;
}

Trit TritSet::operator[](unsigned int index) const {
    if (index >= capacity)
        return UNKNOWN;

    else {
        unsigned int qt_uint = index / (4 * sizeof(unsigned int));
        unsigned int trit_index = index - (qt_uint * sizeof(unsigned int) * 4);

        unsigned int trit_value;
        trit_value = (this->vector_uint[qt_uint] << trit_index * 2) >> (sizeof(unsigned int) * 8 - 2);

        if (trit_value == TRUE)
            return TRUE;

        else if (trit_value == FALSE)
            return FALSE;

        else return UNKNOWN;
    }
}
cellTritSet TritSet::operator[](unsigned int index) {
    cellTritSet cpl_tr(this, index);

    return cpl_tr;
}

TritSet TritSet::operator=(const TritSet& set) {
    this->capacity = set.capacity;
    this->vector_uint = set.vector_uint;

    return *this;
}

TritSet TritSet::operator&(const TritSet& set) {
    unsigned int new_capacity;

    if (this->capacity > set.capacity)
        new_capacity = this->capacity;

    else
        new_capacity = set.capacity;

    TritSet new_set(new_capacity);

    for (unsigned int i = 0; i < new_set.capacity; i++)
        new_set[i] = (*this)[i] & set[i];

    return new_set;
}

TritSet TritSet::operator|(const TritSet& set) {
    unsigned int new_capacity;

    if (this->capacity > set.capacity)
        new_capacity = this->capacity;

    else
        new_capacity = set.capacity;

    TritSet new_set(new_capacity);

    for (unsigned int i = 0; i < new_set.capacity; i += 1)
        new_set[i] = (*this)[i] | set[i];

    return new_set;
}

TritSet TritSet::operator~() {
    unsigned int new_capacity = this->capacity;

    TritSet new_set(new_capacity);

    for (unsigned int i = 0; i < new_set.capacity; i++)
        new_set[i] = ~(*this)[i];

    return new_set;
}

TritSet::iterator::iterator(TritSet* trit_set, unsigned int index) {
    this->trit_set = trit_set;
    this->index = index;
}

TritSet::iterator TritSet::iterator::operator*() const{
    return *this;
}

cellTritSet TritSet::iterator::operator*(){
    return (*trit_set)[index];
}

TritSet::iterator TritSet::iterator::operator=(const iterator& set){
    this->index = set.index;
    this->trit_set = set.trit_set;
    return *this;
}

void TritSet::iterator::operator++(int) {
    index += 1;
}

void TritSet::iterator::operator++(){
    index += 1;
}

bool  TritSet::iterator::operator!=(const iterator& it) const{
    if(this->trit_set == it.trit_set && this->index == it.index)
        return false;
    else
        return true;
}

bool  TritSet::iterator::operator==(const iterator& it) const{
    if(this->trit_set == it.trit_set && this->index == it.index)
        return true;
    else
        return false;
}

bool TritSet::iterator::operator==(const Trit& set) const{
    if((*trit_set)[index] == set)
       return true;
    else
       return false;
}

TritSet::iterator TritSet::iterator::operator=(const Trit& set) {
    (*trit_set)[index] = set;
    return *this;
}

TritSet::iterator TritSet::begin() {
    TritSet::iterator it(this, 0);
    return it;
}

TritSet::iterator TritSet::end() {
    TritSet::iterator it(this, this->capacity);
    return it ;
}

cellTritSet::cellTritSet(TritSet* set, unsigned int index) {
    trit_set = set;
    this->index = index;
}

cellTritSet::cellTritSet() {
    trit_set = NULL;
    this->index = 0;
}

cellTritSet cellTritSet::operator=(Trit value) {
    unsigned int qt_uint = index / (4 * sizeof(unsigned int));
    unsigned int trit_index = index - (qt_uint * sizeof(unsigned int) * 4);
    unsigned int trit_value = value;
    unsigned int trit_plase = trit_value << (sizeof(unsigned int) * 8 - 2 - trit_index * 2);
    unsigned int max_nmb = 0;

    max_nmb = ~max_nmb;

    if (index >= trit_set->capacity && !(value == UNKNOWN)) {
        trit_set->capacity = index + 1;
        trit_set->vector_uint.resize(qt_uint, 0);
    }

    if (value == TRUE)
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] | trit_plase;

    if (value == FALSE) {
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] | trit_plase;
        trit_plase = ~(trit_plase << 1);
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] & trit_plase;
    }

    if (value == UNKNOWN) {
        trit_plase = ~((max_nmb << (sizeof(unsigned int) * 8 - 2)) >> (trit_index * 2));
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] & trit_plase;
    }

    return *this;
}

cellTritSet cellTritSet::operator=(const cellTritSet& set) {
    unsigned int qt_uint = index / (4 * sizeof(unsigned int));
    unsigned int trit_index = index - (qt_uint * sizeof(unsigned int) * 4);


    unsigned int uint_number_set = set.index / (4 * sizeof(unsigned int));
    unsigned int trit_index_set = set.index - (qt_uint * sizeof(unsigned int) * 4);
    unsigned int trit_value = (set.trit_set->vector_uint[uint_number_set] << trit_index_set * 2) >> (sizeof(unsigned int) * 8 - 2);

    unsigned int trit_plase = trit_value << (sizeof(unsigned int) * 8 - 2 - trit_index * 2);
    unsigned int max_nmb = 0;
    max_nmb = ~max_nmb;

    if (index >= trit_set->capacity) {
        trit_set->capacity = index + 1;
        trit_set->vector_uint.resize(qt_uint, 0);
    }

    if (set == TRUE)
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] | trit_plase;

    if (set == FALSE) {
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] | trit_plase;
        trit_plase = ~(trit_plase << 1);
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] & trit_plase;
    }

    if (set == UNKNOWN) {
        trit_plase = ~((max_nmb << (sizeof(unsigned int) * 8 - 2)) >> (trit_index * 2));
        trit_set->vector_uint[qt_uint] = trit_set->vector_uint[qt_uint] & trit_plase;
    }

    return *this;
}

bool cellTritSet::operator==(Trit set) const {
    unsigned int qt_uint = index / (4 * sizeof(unsigned int));
    unsigned int trit_index = index - (qt_uint * sizeof(unsigned int) * 4);

    unsigned int trit_value;
    if (index >= trit_set->capacity)
        trit_value = UNKNOWN;
    else
        trit_value = (trit_set->vector_uint[qt_uint] << trit_index * 2) >> (sizeof(unsigned int) * 8 - 2);


    if (trit_value == set)
        return true;
    else
        return false;
}

bool cellTritSet::operator==(const cellTritSet& set) const {
    unsigned int qt_uint = this->index / (4 * sizeof(unsigned int));
    unsigned int trit_index = this->index - (qt_uint * sizeof(unsigned int) * 4);
    unsigned int qt_uint_set = set.index / (4 * sizeof(unsigned int));
    unsigned int trit_index_set = set.index - (qt_uint_set * sizeof(unsigned int) * 4);
    unsigned int trit_value, trit_value_set;

    trit_value_set = (set.trit_set->vector_uint[qt_uint_set] << trit_index_set * 2) >> (sizeof(unsigned int) * 8 - 2);
    trit_value = (this->trit_set->vector_uint[qt_uint] << trit_index * 2) >> (sizeof(unsigned int) * 8 - 2);

    if (trit_value == trit_value_set)
        return true;

    else
        return false;
}

Trit cellTritSet::operator&(const cellTritSet& set) const{
    if (*this == FALSE || set == FALSE)
        return FALSE;

    else if (*this == UNKNOWN || set == UNKNOWN)
        return UNKNOWN;

    else
        return TRUE;
}

Trit cellTritSet::operator&(Trit set) const{
    if (*this == FALSE || set == FALSE)
        return FALSE;
    else if (*this == UNKNOWN || set == UNKNOWN)
        return UNKNOWN;
    else
        return TRUE;
}

Trit cellTritSet::operator|(const cellTritSet& set) const{
    if (*this == TRUE || set == TRUE)
        return TRUE;
    else if (*this == UNKNOWN || set == UNKNOWN)
        return UNKNOWN;
    else
        return FALSE;
}

Trit cellTritSet::operator|(Trit set) const{
    if (*this == TRUE || set == TRUE)
        return TRUE;

    else if (*this == UNKNOWN || set == UNKNOWN)
        return UNKNOWN;

    else
        return FALSE;
}

Trit cellTritSet::operator~() const{
    if (*this == TRUE)
        return FALSE;

    else if (*this == FALSE)
        return TRUE;

    else
        return UNKNOWN;
}