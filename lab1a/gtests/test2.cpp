#include "bitarray.h"
#include <gtest/gtest.h>

TEST(BoolOperatorTopic, TestingEqual) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b0011101001);
    EXPECT_FALSE(array_1 == array_2);
    array_2.set(9);
    EXPECT_TRUE(array_1 == array_2);
}

TEST(BoolOperatorTopic, TestingNotEqual) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b0011101001);
    EXPECT_TRUE(array_1 != array_2);
    array_2.set(9);
    EXPECT_FALSE(array_1 != array_2);
}

TEST(BoolOperatorTopic, TestingFindingElementValue) {
    BitArray array(32, 0xFFFFFFFE);
    array.push_back(1);
    EXPECT_TRUE(array[32] == 1);
    EXPECT_TRUE(array[31] == 1);
    EXPECT_TRUE(array[0] == 0);
}