#include "Game.h"
#include <gtest/gtest.h>


TEST(IsPlayableTest, NotPlayable)
{
	Game testGame;
	testGame.add("Chet");
	ASSERT_EQ(false, testGame.isPlayable());
	testGame.add("Chat");
	ASSERT_EQ(true, testGame.isPlayable());
	//ASSERT_EQ(false, false);
}


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}