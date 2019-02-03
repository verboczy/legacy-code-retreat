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

TEST (HowManyPlayers, HowMany)
{
  Game testGame;
  ASSERT_EQ(0, testGame.howManyPlayers());
  testGame.add("Alice");
  ASSERT_EQ(1, testGame.howManyPlayers());
  testGame.add("Bob");
  ASSERT_EQ(2, testGame.howManyPlayers());
  testGame.add("Judy");
  ASSERT_EQ(3, testGame.howManyPlayers());
  testGame.add("Mallory");
  ASSERT_EQ(4, testGame.howManyPlayers());
  testGame.add("Oscar");
  ASSERT_EQ(5, testGame.howManyPlayers());
  testGame.add("Trent");
  ASSERT_EQ(6, testGame.howManyPlayers());
  testGame.add("Trudy");
  ASSERT_EQ(7, testGame.howManyPlayers());
}

TEST (Roll, InPenaltyButGetOutGreaterThan11)
{
  Game testGame;
  testGame.add("Alice");
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(13);
  ASSERT_EQ(1, testGame.getPlace(0));
  ASSERT_EQ(true, testGame.getIsGettingOutOfPenaltyBox());
}

TEST (Roll, InPenaltyButGetOutNotGreaterThan11)
{
  Game testGame;
  testGame.add("Alice");
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(11);
  ASSERT_EQ(11, testGame.getPlace(0));
  ASSERT_EQ(true, testGame.getIsGettingOutOfPenaltyBox());  
}

TEST (Roll, InPenaltyNotGetOut)
{
  Game testGame;
  testGame.add("Alice");
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(2);
  ASSERT_EQ(0, testGame.getPlace(0));
  ASSERT_EQ(false, testGame.getIsGettingOutOfPenaltyBox());
}

// Failing because of the bug in the add method
TEST (Roll, NotInPenaltyGreaterThan11)
{
  Game testGame;
  testGame.add("Alice");
  // Initially should not be in penalty
  testGame.roll(16);
  ASSERT_EQ(4, testGame.getPlace(0));
}

// Failing because of the bug in the add method
TEST (Roll, NotInPenaltyNotGreaterThan11)
{
  Game testGame;
  testGame.add("Alice");
  // Initially should not be in penalty
  testGame.roll(8);
  ASSERT_EQ(8, testGame.getPlace(0));
}

TEST (CurrentCategory, Pop)
{
  Game testGame;
  testGame.add("Alice");
  // 0
  ASSERT_EQ("Pop", testGame.currentCategory());
  // 4
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Pop", testGame.currentCategory());
  // 8
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Pop", testGame.currentCategory());
}

TEST (CurrentCategory, Science)
{
  Game testGame;
  testGame.add("Alice");
  // 1
  testGame.roll(1);
  ASSERT_EQ("Science", testGame.currentCategory());
  // 5
  testGame.roll(3);
  testGame.roll(1);  
  ASSERT_EQ("Science", testGame.currentCategory());
  // 9
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Science", testGame.currentCategory());
}

TEST (CurrentCategory, Sports)
{
  Game testGame;
  testGame.add("Alice");
  // 2
  testGame.roll(1);
  testGame.roll(1);
  ASSERT_EQ("Sports", testGame.currentCategory());
  // 6
  testGame.roll(3);
  testGame.roll(1);  
  ASSERT_EQ("Sports", testGame.currentCategory());
  // 10
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Sports", testGame.currentCategory());
}

TEST (CurrentCategory, Rock)
{
  Game testGame;
  testGame.add("Alice");
  // 3
  testGame.roll(3);
  ASSERT_EQ("Rock", testGame.currentCategory());
  // 7
  testGame.roll(3);
  testGame.roll(1);  
  ASSERT_EQ("Rock", testGame.currentCategory());
  // 11
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Rock", testGame.currentCategory());
}

TEST (WasCorrectlyAnswered, InPenaltyGetOut)
{
  Game testGame;
  testGame.add("Alice");
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(11);
  testGame.wasCorrectlyAnswered();
  ASSERT_EQ(1, testGame.getPurse(0));
}

TEST (WasCorrectlyAnswered, InPenaltyNotGetOut)
{
  Game testGame;
  testGame.add("Alice");
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(2);
  testGame.wasCorrectlyAnswered();
  ASSERT_EQ(0, testGame.getPurse(0));
}


TEST (WasCorrectlyAnswered, NotInPenalty)
{
  Game testGame;
  testGame.add("Alice");
  testGame.wasCorrectlyAnswered();
  ASSERT_EQ(1, testGame.getPurse(0));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}