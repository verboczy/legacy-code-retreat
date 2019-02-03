#include "Game.h"
#include <gtest/gtest.h>
#include <string>

TEST (GameConstructorTest, CreateQuestions)
{
  Game testGame;
  for (int i = 0; i < 50; i++)
  {
    ASSERT_EQ("Pop Question " + std::to_string(i), testGame.getPopQuestion(i));
    ASSERT_EQ("Science Question " + std::to_string(i), testGame.getScienceQuestion(i));
    ASSERT_EQ("Sports Question " + std::to_string(i), testGame.getSportsQuestion(i));
    ASSERT_EQ("Rock Question " + std::to_string(i), testGame.getRockQuestion(i));
  }
}

TEST (GameConstructorTest, CurrentPlayer)
{
  Game testGame;
  ASSERT_EQ(0, testGame.getCurrentPlayer());
}

TEST (IsPlayable, NotPlayable)
{
  Game testGame;
  ASSERT_EQ(false, testGame.isPlayable());
  testGame.add("Alice");
  ASSERT_EQ(false, testGame.isPlayable());
}

TEST (IsPlayable, Playable)
{
  Game testGame;
  testGame.add("Alice");
  testGame.add("Bob");
  ASSERT_EQ(true, testGame.isPlayable());
  testGame.add("Judy");
  ASSERT_EQ(true, testGame.isPlayable());
  testGame.add("Mallory");
  ASSERT_EQ(true, testGame.isPlayable());
  testGame.add("Oscar");
  ASSERT_EQ(true, testGame.isPlayable());
  testGame.add("Trent");
  ASSERT_EQ(true, testGame.isPlayable());
  testGame.add("Trudy");
  ASSERT_EQ(true, testGame.isPlayable());
}

TEST (Add, InitializePlayer)
{
  Game testGame;
  testGame.add("Alice");
  ASSERT_EQ("Alice", testGame.getPlayer(0));
  ASSERT_EQ(0, testGame.getPlace(0));
  ASSERT_EQ(0, testGame.getPurse(0));
  // This found a bug! This is wrong:
  // inPenaltyBox[howManyPlayers()] = false;
  // howManyPlayers() - 1 would be better
  // Also the place and purse initialization is wrong.
  ASSERT_EQ(false, testGame.isInPenaltyBox(0));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}