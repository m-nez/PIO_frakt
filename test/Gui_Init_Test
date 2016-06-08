#include <gtest/gtest.h>
#include <gui.hpp>

TEST(GuiInitTest, init) {
	GUI gui; // initialising in constructor
	EXPECT_EQ(800 , gui.get_width()        );
	EXPECT_EQ(600 , gui.get_height()       );
	EXPECT_FALSE (0 == gui.get_rs_count()       );
	EXPECT_FALSE(0 == gui.get_color_count()    );
	EXPECT_FALSE(NULL == gui.get_plane()     );
	EXPECT_FALSE(NULL == gui.get_rs()       );
	EXPECT_EQ(0 , gui.get_rs_current()     );
	EXPECT_EQ(0 , gui.get_color_current()  );
}
	
