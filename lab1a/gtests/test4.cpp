#include "bitarray.h"
#include <gtest/gtest.h>

TEST(BitIteratorTopic, Equal){
    BitArray bitArray1(11, 0b10100000101);
    BitArray bitArray2(11, 0b10100000101);

    EXPECT_TRUE(bitArray1 == bitArray2);
    EXPECT_FALSE(bitArray1 != bitArray2);
}

TEST(BitIteratorTopic, NotEqual){
    BitArray bitArray1(11, 0b10100000101);
    BitArray bitArray2(11, 0b10101000101);

    EXPECT_FALSE(bitArray1 == bitArray2);
    EXPECT_TRUE(bitArray1 != bitArray2);
}

TEST(BitIteratorTopic, BoundCase){
    BitArray bitarray1(32, 0x80000003);
    BitArray bitarray2(11, 0x80000002);
    auto iterator1 = bitarray1.begin();
    auto iterator2 = bitarray2.begin();
    EXPECT_TRUE(*iterator1 != *iterator2);

    for (int i = 0; i < 31; ++i) {
        ++iterator1;
        ++iterator2;
    }
    EXPECT_TRUE(*iterator1 == *iterator2);
}

TEST(BitIteratorTopic, RangeFor) {
    BitArray ba(10);
    for (auto v: ba){
        v = true;
    }
    EXPECT_TRUE(ba.count() == 10);
}
