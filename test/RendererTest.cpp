#include <renderer.hpp>
#include <gtest/gtest.h>

namespace {

	TEST(RendererTest, Packaging) {
		int count;
		Plane plane(80,60);
		Renderer* r = package_renderers(&plane, &count);
		ASSERT_NE(nullptr, r);
		EXPECT_NE(0, count);

		int color_count;
		c_keys* colors = package_colors(&color_count);
		ASSERT_NE(nullptr, colors);
		EXPECT_NE(0, color_count);


		for(int k = 0; k < color_count; ++k) {
			plane.color = colors[k].function;
			for(int j = 0; j < count; ++j) {
				char nonZero = 0;
				r[j].render();
				for(int i = 0; i < plane.width * plane.height * 3; ++i) {
					if(plane.data[i] != 0) {
						nonZero = 1;
						break;
					}
				}
				EXPECT_EQ(1, nonZero) << r[j].get_id() << " " <<  colors[k].id;
			}
		}
	}

}
