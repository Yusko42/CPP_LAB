#include "bitarray.h"
#include <gtest/gtest.h>

TEST(UnarOperatorTopic, TestingAND) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b1011001100);
    BitArray array_3 = array_1 & array_2;
    ASSERT_EQ(array_3.to_string(), "1011001000");
}

TEST(UnarOperatorTopic, TestingOR) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b1011001100);
    BitArray array_3 = array_1 | array_2;
    ASSERT_EQ(array_3.to_string(), "1011101101");
}

TEST(UnarOperatorTopic, TestingXOR) {
    BitArray array_1(10, 0b1011101001);
    BitArray array_2(10, 0b1011001100);
    BitArray array_3 = array_1 ^ array_2;
    ASSERT_EQ(array_3.to_string(), "0000100101");
}