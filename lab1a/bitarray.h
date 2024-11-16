#ifndef LAB1A_BITARRAY_H
#define LAB1A_BITARRAY_H
#include <iostream>
#include <vector>

class BitArray {
public:
    /** @brief Default constructor.

    Initializes an empty bit array with zero length and no data.
    */
    BitArray();

    /** @brief Destructor.

    Cleans up resources used by the bit array.
    */
    ~BitArray();

    /** @brief Constructs a bit array with a specified number of bits.

    Optionally initializes the first sizeof(long) bits using the value parameter.
    @param num_bits The number of bits in the array.
    @param value Optional value to initialize the first bits.
    */
    explicit BitArray(int num_bits, unsigned long value = false);

    /** @brief Copy constructor.
     * Creates a new bit array as a copy of an existing one.
     * @param b The BitArray instance to copy from.
     */
    BitArray(const BitArray& b);

    /**
 * @class BitIterator
 * @brief Iterator for traversing bits in a BitArray object.
 *
 * Enables iteration over bits in a `BitArray`, providing access to each bit
 * and the ability to check the bit values.
 */
    class BitIterator {
    public:
        /**
         * @brief Constructs a BitIterator.
         * @param array Reference to the bit array to be iterated over.
         * @param num_pos Initial position of the iterator (bit index).
         *
         * Creates an iterator pointing to the `num_pos` position in the `array`.
         */
        BitIterator(const BitArray& array, unsigned int num_pos);

        /**
         * @brief Dereference operator.
         * @return The value of the current bit (true if the bit is 1; false if the bit is 0).
         */
        bool operator*();

        /**
         * @brief Prefix increment operator.
         * @return Reference to the current iterator after moving to the next bit.
         *
         * Moves the iterator to the next bit in the array.
         */
        BitIterator& operator++();

        /**
         * @brief Inequality operator.
         * @param b Iterator to compare with.
         * @return true if the iterators point to different positions; otherwise, false.
         */
        bool operator!=(const BitIterator& b) const;

        /**
         * @brief Equality operator.
         * @param b Iterator to compare with.
         * @return true if the iterators point to the same position; otherwise, false.
         */
        bool operator==(const BitIterator& b) const;

    private:
        const BitArray& bit_arr;   /**< Reference to the bit array being iterated over. */
        unsigned int bit_pos;      /**< Current iterator position (bit index). */
    };

    /**
     * @brief Returns an iterator pointing to the first bit in the array.
     * @return An iterator pointing to the beginning of the bit array.
     */
    [[nodiscard]] BitIterator begin() const;

    /**
     * @brief Returns an iterator pointing past the last bit in the array.
     * @return An iterator pointing to the end of the bit array.
     */
    [[nodiscard]] BitIterator end() const;

    /** @brief Prints the contents of the bit array (for debugging purposes).
     * @param i The number of an element in data to display.
     */
    void PrintData(int i);

    /** @brief Swaps the contents of this bit array with another.
     * @param b The bit array to swap with.
     */
    void swap(BitArray& b);

    /** @brief Assignment operator.
     * Replaces the contents of this bit array with those of another.
     * @param b The BitArray instance to copy from.
     * @return A reference to this bit array.
     */
    BitArray& operator=(const BitArray& b);

    /** @brief
      * Resizes the bit array to a specified number of bits.
      * If expanded, new bits are initialized to the specified value.
      * @param num_bits The new size in bits.
      * @param value The value for new bits if array is expanded.
      */
    void resize(int num_bits, bool value = false);

    /** @brief Clears all bits in the array, setting length to zero.
     */
    void clear();

    /** @brief Appends a new bit to the end of the array.
     * Resizes the storage if necessary.
     * @param bit The bit to add (true or false).
     */
    void push_back(bool bit);


    /** @brief
     * Performs a bitwise AND with another bit array of the same size.
     * @param b The bit array to AND with.
     * @return A reference to this bit array after the operation.
     */
    BitArray& operator&=(const BitArray& b);

    /** @brief
     * Performs a bitwise OR with another bit array of the same size.
     * @param b The bit array to OR with.
     * @return A reference to this bit array after the operation.
     */
    BitArray& operator|=(const BitArray& b);

    /** @brief
     * Performs a bitwise XOR with another bit array of the same size.
     * @param b The bit array to XOR with.
     * @return A reference to this bit array after the operation.
     */
    BitArray& operator^=(const BitArray& b);

    /** @brief
     * Shifts the bits in the array left by a specified number of positions.
     * New bits are filled with zeros.
     * @param n Number of positions to shift.
     * @return A reference to this bit array after the shift.
     */
    BitArray& operator<<=(int n);

    /** @brief
     * Shifts the bits in the array right by a specified number of positions.
     * New bits are filled with zeros.
     * @param n Number of positions to shift.
     * @return A reference to this bit array after the shift.
     */
    BitArray& operator>>=(int n);

    /** @brief
     * Creates a new bit array with bits shifted left by a specified number.
     * New bits are filled with zeros.
     * @param n Number of positions to shift.
     * @return A new bit array with shifted bits.
     */
    BitArray operator<<(int n) const;

    /** @brief
     * Creates a new bit array with bits shifted right by a specified number.
     * New bits are filled with zeros.
     * @param n Number of positions to shift.
     * @return A new bit array with shifted bits.
     */
    BitArray operator>>(int n) const;

    /** @brief
     * Sets the bit at a specified index to a given value.
     * @param n The index of the bit to set.
     * @param val The value to set (true or false).
     * @return A reference to this bit array after modification.
     */
    BitArray& set(int n, bool val = true);

    /** @brief
     * Sets all bits in the array to true.
     * @return A reference to this bit array after modification.
     */
    BitArray& set();

    /** @brief
     * Resets the bit at a specified index to false.
     * @param n The index of the bit to reset.
     * @return A reference to this bit array after modification.
     */
    BitArray& reset(int n);

    /** @brief
     * Sets all bits in the array to false.
     * @return A reference to this bit array after modification.
     */
    BitArray& reset();


    /** @brief
     * Checks if any bit in the array is true.
     * @return True if at least one bit is true, false otherwise.
     */
    bool any() const;

    /** @brief
     * Checks if all bits in the array are false.
     * @return True if all bits are false, false otherwise.
     */
    bool none() const;

    /** @brief
     * Creates a new bit array with all bits inverted.
     * @return A new bit array with inverted bits.
     */
    BitArray operator~() const;

    /** @brief
      * Counts the number of bits set to true in the array.
      * @return The count of bits set to true.
      */
    int count() const;

    /** @brief
     * Accesses the value of a bit at a specified index.
     * @param i The index of the bit.
     * @return The value of the bit (true or false).
     */
    bool operator[](int i) const;

    /** @brief
     * Returns the number of bits in the array.
     * @return The bit array size.
     */
    unsigned int size() const;

    /** @brief
     * Checks if the bit array is empty (size is zero).
     * @return True if empty, false otherwise.
     */
    bool empty() const;

    std::string to_string() const;

private:
    unsigned int len;
    std::vector<unsigned long> data;
};

/** @brief
 * Equality operator.
 * Compares two bit arrays for equality.
 * @param a The first bit array.
 * @param b The second bit array.
 * @return True if both arrays are equal, false otherwise.
 */
bool operator==(const BitArray & a, const BitArray & b);

/** @brief
 * Inequality operator.
 * Compares two bit arrays for inequality.
 * @param a The first bit array.
 * @param b The second bit array.
 * @return True if arrays are not equal, false otherwise.
 */
bool operator!=(const BitArray & a, const BitArray & b);

/** @brief
 * Bitwise AND operator for bit arrays.
 * Creates a new bit array by performing AND on each bit.
 * @param b1 The first bit array.
 * @param b2 The second bit array.
 * @return A new bit array with result of AND operation.
 */
BitArray operator&(const BitArray& b1, const BitArray& b2);

/** @brief
 * Bitwise OR operator for bit arrays.
 * Creates a new bit array by performing OR on each bit.
 * @param b1 The first bit array.
 * @param b2 The second bit array.
 * @return A new bit array with result of OR operation.
 */
BitArray operator|(const BitArray& b1, const BitArray& b2);

/** @brief
 * Bitwise XOR operator for bit arrays.
 * Creates a new bit array by performing XOR on each bit.
 * @param b1 The first bit array.
 * @param b2 The second bit array.
 * @return A new bit array with result of XOR operation.
 */
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif //LAB1A_BITARRAY_H
