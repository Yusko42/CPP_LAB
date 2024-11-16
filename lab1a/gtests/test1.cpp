#include "bitarray.h"
#include <gtest/gtest.h>

TEST(BitArrayTopic, TestingShiftLeft) {
    BitArray array_1(32, 0xFFFFFFFF);
    array_1 <<= 3;
    ASSERT_EQ(array_1.to_string(),
              "11111111111111111111111111111000");

    BitArray array_2(16, 0b1001011100111011);
    array_2 <<= 3;
    ASSERT_EQ(array_2.to_string(),
              "1011100111011000");

    BitArray array_3(64, 0b1001011100111011);
    array_3 <<= 32;
    ASSERT_EQ(array_3.to_string(),
              "0000000000000000100101110011101100000000000000000000000000000000");
}

TEST(BitArrayTopic, TestingShiftRight) {
    BitArray array_1(32, 0xFFFFFFFF);
    array_1 >>= 8;
    ASSERT_EQ(array_1.to_string(),
              "00000000111111111111111111111111");

    BitArray array_2(16, 0b1001011100111011);
    array_2 >>= 3;
    ASSERT_EQ(array_2.to_string(),
              "0001001011100111");

    BitArray array_3(16, 0b1001011100111011);
    array_3 >>= 17;
    ASSERT_EQ(array_3.to_string(),
              "0000000000000000");

    BitArray array_4(32, 0b1001011100111011);
    array_4.resize(64);
    array_4 >>= 32;
    ASSERT_EQ(array_4.to_string(),
              "0000000000000000000000000000000000000000000000000000000000000000");
}

TEST(BitArrayTopic, TestingLeft) {
    BitArray array_1(32, 0xFFFFFFFF);
    BitArray array_2 = array_1 << 3;
    ASSERT_EQ(array_2.to_string(),
              "11111111111111111111111111111000");
}

TEST(BitArrayTopic, TestingRight) {
    BitArray array_1(32, 0xFFFFFFFF);
    BitArray array_2 = array_1 >> 5;
    ASSERT_EQ(array_2.to_string(),
              "00000111111111111111111111111111");
}

TEST(BitArrayTopic, TestingSet) {
    BitArray bitarray(10, 0b00110010);
    EXPECT_THROW(bitarray.set(12, 1), std::out_of_range);
    bitarray.set(9);
    ASSERT_EQ(bitarray.to_string(), "1000110010");
}

TEST(BitArrayTopic, TestingEmptySet) {
    BitArray bitarray(10);
    bitarray.set();
    ASSERT_EQ(bitarray.to_string(), "1111111111");
}

TEST(BitArrayTopic, TestingReset) {
    BitArray bitarray(10, 0b10110010);
    EXPECT_THROW(bitarray.reset(12), std::out_of_range);
    bitarray.reset(7);
    ASSERT_EQ(bitarray.to_string(), "0000110010");
}

TEST(BitArrayTopic, TestingEmptyReset) {
    BitArray bitarray(10);
    bitarray.reset();
    ASSERT_EQ(bitarray.to_string(), "0000000000");
}

TEST(BitArrayTopic, TestingAny) {
    BitArray bitarray(128);
    EXPECT_FALSE(bitarray.any());

    bitarray.set(62);
    EXPECT_TRUE(bitarray.any());

    bitarray <<= 4;
    EXPECT_TRUE(bitarray.any());
}

TEST(BitArrayTopic, TestingNone) {
    BitArray bitarray(128);
    EXPECT_TRUE(bitarray.none());

    bitarray.set(62);
    EXPECT_FALSE(bitarray.none());

    bitarray <<= 4;
    EXPECT_FALSE(bitarray.none());
}

TEST(BitArrayTopic, TestingCount) {
    BitArray bitarray(64, 0b101101);
    ASSERT_EQ(bitarray.count(), 4);

    bitarray <<= 29;
    ASSERT_EQ(bitarray.count(), 4);
}

TEST(BitArrayTopic, EmptyArray1) {
    BitArray bitarray;
    ASSERT_EQ(bitarray.size(), 0);
    ASSERT_TRUE(bitarray.empty());
}

TEST(BitArrayTopic, PushBack) {
    BitArray bitarray(64);
    bitarray.push_back(1);
    ASSERT_EQ(bitarray.size(), 65);
}

TEST(BitArrayTopic, ExpectChangedSize) {
    BitArray bitarray(64);
    bitarray.resize(42);
    ASSERT_EQ(bitarray.size(), 42);

    bitarray.resize(70);
    ASSERT_EQ(bitarray.size(), 70);
}

TEST(BitArrayTopic, TestingToString) {
    BitArray bitarray(10, 20);
    ASSERT_EQ(bitarray.to_string(), "0000010100");
}

TEST(BitArrayTopic, ReverseToString) {
    BitArray bitarray(10, 20);
    bitarray = ~bitarray;
    ASSERT_EQ(bitarray.to_string(), "1111101011");
}

TEST(BitArrayTopic, TestingSwap) {
    BitArray array_1(10, 7);
    BitArray array_2(12, 25);
    array_1.swap(array_2);
    ASSERT_EQ(array_1.to_string(), "000000011001");
    ASSERT_EQ(array_2.to_string(), "0000000111");
}

TEST(BitArrayTopic, TestingAssign) {
    BitArray array;
    BitArray source_array(10, 42);
    array = source_array;
    ASSERT_EQ(array.to_string(), "0000101010");
}

TEST(BitArrayTopic, testingClear) {
    BitArray bitarray(10, 20);
    bitarray.clear();
    ASSERT_EQ(bitarray.size(), 0);
}

TEST(BitArrayTopic, TestingAND) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b1110111010);

    array_1 &= array_2;
    ASSERT_EQ(array_1.to_string(), "1010101000");
}

TEST(BitArrayTopic, TestingOR) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b1110111010);

    array_1 |= array_2;
    ASSERT_EQ(array_1.to_string(), "1111111011");
}

TEST(BitArrayTopic, TestingXOR) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b1110111010);

    array_1 ^= array_2;
    ASSERT_EQ(array_1.to_string(), "0101010011");
}

