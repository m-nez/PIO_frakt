#include <plane.hpp>
#include <gtest/gtest.h>

TEST(PlaneTest, resize) {
	float u, d, l, r;
	// Resizing in constructor
	Plane plane(80,60);
	u = plane.up;
	d = plane.down;
	l = plane.left;
	r = plane.right;
	EXPECT_EQ(80, plane.width);
	EXPECT_EQ(60, plane.height);
	EXPECT_NE(nullptr, plane.data);

	// Resizing, make sure that only the capacity changes
	plane.resize(151, 59);
	EXPECT_EQ(151, plane.width);
	EXPECT_EQ(59, plane.height);
	EXPECT_NE(nullptr, plane.data);
	EXPECT_EQ(plane.up, u);
	EXPECT_EQ(plane.down, d);
	EXPECT_EQ(plane.left, l);
	EXPECT_EQ(plane.right, r);

	// Negative dimensions should be clamped to 0
	plane.resize(-151, -59);
	EXPECT_EQ(0, plane.width);
	EXPECT_EQ(0, plane.height);
	EXPECT_EQ(plane.up, u);
	EXPECT_EQ(plane.down, d);
	EXPECT_EQ(plane.left, l);
	EXPECT_EQ(plane.right, r);
}
