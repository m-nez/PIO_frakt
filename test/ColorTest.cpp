#include <gtest/gtest.h>
#include <renderer.hpp>

TEST(ColorTest, greyscale) {
	unsigned char* instance = new char[3];
	double x = 0.1;
	color_greyscale(x, instance);
	unsigned char[3] result = {{25.5}, {25.5}, {25.5}};
	EXPECT_EQ(result, instance);	
}

TEST(ColorTest, blue) {
	unsigned char* instance = new char[3];
	double x = 0.1;
	color_blue(x, instance);
	unsigned char[3] result = {{4.98}, {8.05}, {44.02}};
	EXPECT_EQ(result, instance);
}
