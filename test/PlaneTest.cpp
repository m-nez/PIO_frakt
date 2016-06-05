#include <plane.hpp>
#include <gtest/gtest.h>

TEST(PlaneTest, resize) {
	Plane plane(80,60);
	EXPECT_EQ(80, plane.width);
	EXPECT_EQ(60, plane.height);
	EXPECT_NE(nullptr, plane.data);

	plane.resize(151, 59);
	EXPECT_EQ(151, plane.width);
	EXPECT_EQ(59, plane.height);
	EXPECT_NE(nullptr, plane.data);

	plane.resize(-151, -59);
	EXPECT_EQ(0, plane.width);
	EXPECT_EQ(0, plane.height);
}
