#include "bitarray.h"
#include <gtest/gtest.h>

TEST(BitIteratorTopic, Equal){
    BitArray bitarray(11, 0b10100000101);
    auto iterator1 = bitarray.begin();
    auto iterator2 = bitarray.end();
    EXPECT_TRUE(*iterator1 == *iterator2);

    ++iterator1;
    EXPECT_FALSE(*iterator1 == *iterator2);
}

TEST(BitIteratorTopic, NotEqual){
    BitArray bitarray(11, 0b10100000101);
    auto iterator1 = bitarray.begin();
    auto iterator2 = bitarray.end();
    EXPECT_FALSE(*iterator1 != *iterator2);

    ++iterator1;
    EXPECT_TRUE(*iterator1 != *iterator2);
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