#include <gtest/gtest.h>
#include <renderer.hpp>

TEST(ColorTest, greyscale) {
    unsigned char instance[3];

    //double x has min value (x = 0)
    double x1 = 0;
    color_grayscale(x1, instance);
    unsigned char result1[] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(instance[i], result1[i]);
    }

    //double x has max value (x = 1)
    double x2 = 1;
    color_grayscale(x2, instance);
    unsigned char result2[] = {255, 255, 255};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(instance[i], result2[i]);
    }   

    //double x is between [0;1]
    double x3 = 0.1;
    color_grayscale(x3, instance);
    unsigned char result3[] = {25, 25, 25};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(instance[i], result3[i]);
    }   
}

TEST(ColorTest, blue) {
    unsigned char instance[3];

    //double x has min value (x = 0)
    double x1 = 0;
    color_blue(x1, instance);
    unsigned char result1[] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(instance[i], result1[i]);
    }

    //double x has max value (x = 1)
    double x2 = 1;
    color_blue(x2, instance);
    unsigned char result2[] = {57, 229, 235};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(instance[i], result2[i]);
    }

    //double x is between [0;1]
    double x3 = 0.1;
    color_blue(x3, instance);
    unsigned char result3[] = {4, 8, 44};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(instance[i], result3[i]);
   }
}

