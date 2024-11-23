#include <iostream>
#include "bitarray.h"

static const int ELEMENT_SIZE = (sizeof(unsigned long) * 8);

BitArray::BitArray() : len(0) {};
BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value) : len(num_bits) {
    if (num_bits <= 0)
        throw std::invalid_argument("ERROR: length is not positive!");

    unsigned long size_init = (num_bits + ELEMENT_SIZE - 1) / (ELEMENT_SIZE);

    data.resize(size_init, 0);

    data[0] = value;
};

BitArray::BitArray(const BitArray& b) : len(b.len), data(b.data) {};

BitArray::BitIterator::BitIterator(BitArray& array, unsigned int num_pos) :
    bit_arr(array), bit_pos(num_pos) {};

//Value ONLY
bool BitArray::BitIterator::operator*() const{
    return (bit_arr.data[bit_pos / ELEMENT_SIZE] & (1UL << (bit_pos % ELEMENT_SIZE)));
}

BitArray::BitReference BitArray::BitIterator::operator*() {
    unsigned int data_index = bit_pos / ELEMENT_SIZE;
    unsigned int bit_index = bit_pos % ELEMENT_SIZE;
    return BitReference(bit_arr.data[data_index], bit_index);
}

BitArray::BitIterator& BitArray::BitIterator::operator++() {
    ++bit_pos;
    return *this;
}

bool BitArray::BitIterator::operator!=(const BitArray::BitIterator& b) const{
    return bit_pos != b.bit_pos;
}

bool BitArray::BitIterator::operator==(const BitArray::BitIterator& b) const{
    return bit_pos == b.bit_pos;
}

BitArray::BitIterator BitArray::begin() {
    return BitIterator(*this, 0);
}
BitArray::BitIterator BitArray::end() {
    return BitIterator(*this, len);
}

BitArray::BitReference::BitReference(unsigned long& string, unsigned int index) :
        string_of_array(string), bit_pos(index) {};

BitArray::BitReference& BitArray::BitReference::operator=(bool value) {
    if (value)
        string_of_array |= (1UL << bit_pos);
    else
        string_of_array &= ~(1UL << bit_pos);
    return *this;
}

BitArray::BitReference::operator bool() const {
    return (string_of_array >> bit_pos) & 1;
}


void BitArray::PrintData(int i) {
    data[i] = data[i];
    std::cout << data[i];
};

void BitArray::swap(BitArray& b){
    std::swap(b.len, len);
    std::swap(b.data, data);
};

BitArray& BitArray::operator=(const BitArray& b){
    if (this != &b) {
        len = b.len;
        data = b.data;
    }

    return *this;
};


void BitArray::resize(int num_bits, bool value) {

    if (num_bits < 0) {
        throw std::invalid_argument("ERROR: size cannot be negative!");
    }

    if (num_bits == len) { return; }

    int new_position_number = (num_bits + ELEMENT_SIZE - 1) / (ELEMENT_SIZE);

    if (len < num_bits) {
        data.resize(new_position_number, 0);

        if (value == 1) {
            for (unsigned i = (len + ELEMENT_SIZE - 1) / (ELEMENT_SIZE);
                 i < new_position_number; i++) {
                data[i] = ~0UL;
            }

            unsigned int start = len % ELEMENT_SIZE;
            if (start != 0 && (len / ELEMENT_SIZE) < new_position_number) {
                unsigned long bitmask = (~0UL << start);
                data[new_position_number - 1] |= bitmask;
            }
        }

    } else if (len > num_bits) {
        data.resize(new_position_number);
        int bits_remain = num_bits % ELEMENT_SIZE;
        if (bits_remain) {
            unsigned long bitmask = ~(~0UL << bits_remain);
            data[new_position_number - 1] &= bitmask;
        }
    }
    len = num_bits;
}

void BitArray::clear() {
    data.clear();
    len = 0;
}

void BitArray::push_back(bool bit) {
    if (len % ELEMENT_SIZE != 0) {
        data[len/ELEMENT_SIZE] |= bit << (len % ELEMENT_SIZE);
    } else {
        data.resize(len+1);
        data[len/ELEMENT_SIZE] = bit;
    }
    ++len;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (len != b.len)
        throw std::invalid_argument("ERROR: sizes are not equal!");
    if (data.size() != b.data.size())
        throw std::invalid_argument("ERROR: internal vector sizes are not equal!");
    for (int i = 0; i < data.size(); ++i) {
        data[i] = data[i] & b.data[i];
    }
    return *this;
}
BitArray& BitArray::operator|=(const BitArray& b) {
    if (len != b.len)
        throw std::invalid_argument("ERROR: sizes are not equal!");
    if (data.size() != b.data.size())
        throw std::invalid_argument("ERROR: internal vector sizes are not equal!");
    for (int i = 0; i < data.size(); ++i) {
        data[i] = data[i] | b.data[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (len != b.len)
        throw std::invalid_argument("ERROR: sizes are not equal!");
    if (data.size() != b.data.size())
        throw std::invalid_argument("ERROR: internal vector sizes are not equal!");
    for (int i = 0; i < data.size(); ++i) {
        data[i] = data[i] ^ b.data[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n <= 0)
        throw std::invalid_argument("ERROR: number should be positive!");

    if (n >= len) {
        (*this).reset();
        return *this;
    }

    unsigned int element_shift = n / ELEMENT_SIZE;
    unsigned int shift = n % ELEMENT_SIZE;

    if (shift == 0) {
        for (unsigned int i = data.size() - 1; i >= element_shift; i--) {
            data[i] = (data[i - element_shift]); //test this for work pls
        }
    } else {
        for (unsigned int i = data.size() - 1; i > element_shift; i--) {
            data[i] = (data[i - element_shift] << shift)
                    | (data[i - element_shift - 1] >> (ELEMENT_SIZE - shift));
        }
        data[element_shift] = (data[0] << shift);
    }

    //or just use std::fill with 0s
    for (unsigned int i = element_shift - 1; i <= 0; i--) {
        data[i] = 0UL;
    }

    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n <= 0)
        throw std::invalid_argument("ERROR: number should be positive!");

    if (n >= len) {
        (*this).reset();
        return *this;
    }

    unsigned int element_shift = n / ELEMENT_SIZE;
    unsigned int shift = n % ELEMENT_SIZE;

    if (shift == 0) {
        for (unsigned int i = element_shift; i < data.size(); i++) {
            data[i - element_shift] = data[i]; //and test this
        }
    } else {
        for (unsigned long i = 0; i < data.size() - element_shift - 1; i++) {
            data[i] = (data[i + element_shift] >> shift)
                    | (data[i + shift + 1] << (ELEMENT_SIZE - shift));
        }
        data[data.size() - element_shift - 1] = data[data.size() - 1] >> shift;
    }
    for (unsigned int i = data.size() - element_shift; i < data.size(); i++) {
        data[i] = 0UL;
    }

    return *this;
}
BitArray BitArray::operator<<(int n) const {
    BitArray shift_left(*this);
    return shift_left <<= n;
}
BitArray BitArray::operator>>(int n) const {
    BitArray shift_right(*this);
    return shift_right >>= n;
}

BitArray& BitArray::set(int n, bool val) {
    if (n >= len || n < 0)
        throw std::out_of_range("ERROR: number - out of range!");

    unsigned int element_shift = n / ELEMENT_SIZE;
    unsigned int shift = n % ELEMENT_SIZE;

    if (val)
        data[element_shift] |= val << shift;
    else
        data[element_shift] &= ~(1UL << shift);
    return *this;
}

BitArray& BitArray::reset(int n) {
    (*this).set(n , false);
    return *this;
}

BitArray& BitArray::set() {
    for (unsigned i = 0; i < (len + ELEMENT_SIZE - 1) / (ELEMENT_SIZE); i++)
        data[i] = ~0UL;
    return *this;
}

/* for (unsigned i = 0; i < ((len + ELEMENT_SIZE - 1) - 1 / (ELEMENT_SIZE)) - 1; i++)
        data[i] = ~0UL;
    data[(len + ELEMENT_SIZE - 1) - 1 / (ELEMENT_SIZE)] = ~0UL >> (ELEMENT_SIZE - len % ELEMENT_SIZE)
    return *this;
 */

BitArray& BitArray::reset() {
    for (unsigned i = 0; i < (len + ELEMENT_SIZE - 1) / (ELEMENT_SIZE); i++)
        data[i] = 0UL;
    return *this;
}

bool BitArray::any() const {
    for (const auto& i : data)
        if (i != 0)
            return true;
    return false;
};

bool BitArray::none() const {
    for (const auto& i : data)
        if (i != 0)
            return false;
    return true;
};

BitArray BitArray::operator~() const {
    BitArray copy(*this);
    for (auto& i : copy.data)
        i = ~i;

    return copy;
};

int BitArray::count() const {
    int true_count = 0;
    for (auto& i : data) {
        for (unsigned shift = 0; shift < ELEMENT_SIZE; shift++){
            true_count += ((i >> shift) & 1);
        }
    }
    return true_count;
};

bool BitArray::operator[](int i) const {
    if (i >= len || i < 0)
        throw std::out_of_range("ERROR: i - out of range!");

    return (data[i / ELEMENT_SIZE] & (1UL << (i % ELEMENT_SIZE)));
};

unsigned int BitArray::size() const { return len; }

bool BitArray::empty() const {
    if (len)
        return false;
    return true;
};

std::string BitArray::to_string() const {
    std::string result_string;
    for (int i = len - 1; i >= 0; i--) {
        result_string += (*this)[i] ? '1' : '0';
    }
    return result_string;
};

bool operator==(const BitArray & a, const BitArray & b) {
    if (a.size() != b.size())
        return false;

    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;

    return true;
};
bool operator!=(const BitArray & a, const BitArray & b) {
    if (a.size() != b.size())
        return true;

    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return true;

    return false;
};

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size())
        throw std::invalid_argument("ERROR: sizes are not equal!");

    BitArray result(b1);
    result &= b2;

    return result;
};
BitArray operator|(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size())
        throw std::invalid_argument("ERROR: sizes are not equal!");

    BitArray result(b1);
    result |= b2;

    return result;
};
BitArray operator^(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size())
        throw std::invalid_argument("ERROR: sizes are not equal!");

    BitArray result(b1);
    result ^= b2;

    return result;
};
