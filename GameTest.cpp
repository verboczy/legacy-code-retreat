#include "Game.h"
#include <gtest/gtest.h>
#include <string>

TEST (GameConstructorTest, CreateQuestions)
{
  Game testGame;
  for (int i = 0; i < 50; ++i)
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
  Player alice{"Alice"};
  testGame.add(alice);
  ASSERT_EQ("Alice", testGame.getPlayer(testGame.getCurrentPlayerId()).getName());
}

TEST (IsPlayable, NotPlayable)
{
  Game testGame;
  Player alice{"Alice"};
  ASSERT_EQ(false, testGame.isPlayable());
  testGame.add(alice);
  ASSERT_EQ(false, testGame.isPlayable());
}

TEST (IsPlayable, Playable)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  Player bob{"Bob"};
  testGame.add(bob);
  ASSERT_EQ(true, testGame.isPlayable());
  Player judy{"Judy"};
  testGame.add(judy);
  ASSERT_EQ(true, testGame.isPlayable());
  Player mallory{"Mallory"};
  testGame.add(mallory);
  ASSERT_EQ(true, testGame.isPlayable());
  Player oscar{"Oscar"};
  testGame.add(oscar);
  ASSERT_EQ(true, testGame.isPlayable());
  Player trent{"Trent"};
  testGame.add(trent);
  ASSERT_EQ(true, testGame.isPlayable());
  Player trudy{"Trudy"};
  testGame.add(trudy);
  ASSERT_EQ(true, testGame.isPlayable());
}

TEST (Add, InitializePlayer)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  ASSERT_EQ("Alice", testGame.getPlayer(0).getName());
  ASSERT_EQ(0, testGame.getPlayer(0).getPlace());
  ASSERT_EQ(0, testGame.getPlayer(0).getPurse());
  ASSERT_EQ(false, testGame.getPlayer(0).getIsInPenaltyBox());
}

TEST (Add, NoSameNames)
{
  Game testGame;
  ASSERT_EQ(0, testGame.howManyPlayers());
  Player alice{"Alice"};
  testGame.add(alice);
  ASSERT_EQ(1, testGame.howManyPlayers());
  Player alice2{"Alice"};
  testGame.add(alice2);
  ASSERT_EQ(1, testGame.howManyPlayers());
}

TEST (HowManyPlayers, HowMany)
{
  Game testGame;
  ASSERT_EQ(0, testGame.howManyPlayers());
  Player alice{"Alice"};
  testGame.add(alice);
  ASSERT_EQ(1, testGame.howManyPlayers());  
  Player bob{"Bob"};
  testGame.add(bob);
  ASSERT_EQ(2, testGame.howManyPlayers());  
  Player judy{"Judy"};
  testGame.add(judy);
  ASSERT_EQ(3, testGame.howManyPlayers());  
  Player mallory{"Mallory"};
  testGame.add(mallory);
  ASSERT_EQ(4, testGame.howManyPlayers());  
  Player oscar{"Oscar"};
  testGame.add(oscar);
  ASSERT_EQ(5, testGame.howManyPlayers());
  Player trent{"Trent"};
  testGame.add(trent);
  ASSERT_EQ(6, testGame.howManyPlayers());  
  Player trudy{"Trudy"};
  testGame.add(trudy);
  ASSERT_EQ(7, testGame.howManyPlayers());
}

TEST (Roll, InPenaltyButGetOutGreaterThan11)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(13);
  ASSERT_EQ(1, testGame.getPlayer(0).getPlace());
  ASSERT_EQ(true, testGame.getIsGettingOutOfPenaltyBox());
}

TEST (Roll, InPenaltyButGetOutNotGreaterThan11)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(11);
  ASSERT_EQ(11, testGame.getPlayer(0).getPlace());
  ASSERT_EQ(true, testGame.getIsGettingOutOfPenaltyBox());  
}

TEST (Roll, InPenaltyNotGetOut)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(2);
  ASSERT_EQ(0, testGame.getPlayer(0).getPlace());
  ASSERT_EQ(false, testGame.getIsGettingOutOfPenaltyBox());
}

// Failing because of the bug in the add method
TEST (Roll, NotInPenaltyGreaterThan11)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // Initially should not be in penalty
  testGame.roll(16);
  ASSERT_EQ(4, testGame.getPlayer(0).getPlace());
}

// Failing because of the bug in the add method
TEST (Roll, NotInPenaltyNotGreaterThan11)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // Initially should not be in penalty
  testGame.roll(8);
  ASSERT_EQ(8, testGame.getPlayer(0).getPlace());
}

TEST (CurrentCategory, Pop)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // 0
  ASSERT_EQ("Pop", testGame.getCurrentCategory());
  // 4
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Pop", testGame.getCurrentCategory());
  // 8
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Pop", testGame.getCurrentCategory());
}

TEST (CurrentCategory, Science)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // 1
  testGame.roll(1);
  ASSERT_EQ("Science", testGame.getCurrentCategory());
  // 5
  testGame.roll(3);
  testGame.roll(1);  
  ASSERT_EQ("Science", testGame.getCurrentCategory());
  // 9
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Science", testGame.getCurrentCategory());
}

TEST (CurrentCategory, Sports)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // 2
  testGame.roll(1);
  testGame.roll(1);
  ASSERT_EQ("Sports", testGame.getCurrentCategory());
  // 6
  testGame.roll(3);
  testGame.roll(1);  
  ASSERT_EQ("Sports", testGame.getCurrentCategory());
  // 10
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Sports", testGame.getCurrentCategory());
}

TEST (CurrentCategory, Rock)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // 3
  testGame.roll(3);
  ASSERT_EQ("Rock", testGame.getCurrentCategory());
  // 7
  testGame.roll(3);
  testGame.roll(1);  
  ASSERT_EQ("Rock", testGame.getCurrentCategory());
  // 11
  testGame.roll(3);
  testGame.roll(1);
  ASSERT_EQ("Rock", testGame.getCurrentCategory());
}

TEST (WasCorrectlyAnswered, InPenaltyGetOut)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(11);
  testGame.wasCorrectlyAnswered();
  ASSERT_EQ(1, testGame.getPlayer(0).getPurse());
}

TEST (WasCorrectlyAnswered, InPenaltyNotGetOut)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  // Put her into penalty box
  testGame.wrongAnswer();
  testGame.roll(2);
  testGame.wasCorrectlyAnswered();
  ASSERT_EQ(0, testGame.getPlayer(0).getPurse());
}

TEST (WasCorrectlyAnswered, NotInPenalty)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  testGame.wasCorrectlyAnswered();
  ASSERT_EQ(1, testGame.getPlayer(0).getPurse());
}

TEST (WrongAnswer, GetPenalty)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  testGame.wrongAnswer();
  ASSERT_EQ(true, testGame.getPlayer(0).getIsInPenaltyBox());
}

TEST (Player, PlayerConstructor)
{
  Player alice{"Alice"};
  ASSERT_EQ("Alice", alice.getName());
  ASSERT_EQ(0, alice.getPlace());
  ASSERT_EQ(0, alice.getPurse());
  ASSERT_EQ(false, alice.getIsInPenaltyBox());
}

TEST (Add, AddPlayer)
{
  Game testGame;
  ASSERT_EQ(0, testGame.howManyPlayers());
  Player alice{"Alice"};
  testGame.add(alice);
  ASSERT_EQ(1, testGame.howManyPlayers());
  Player bob{"Bob"};
  testGame.add(bob);
  ASSERT_EQ(2, testGame.howManyPlayers());
  ASSERT_EQ("Alice", testGame.getPlayer(0).getName());
  ASSERT_EQ("Bob", testGame.getPlayer(1).getName());
  ASSERT_EQ(0, testGame.getPlayer(0).getPlace());
  ASSERT_EQ(0, testGame.getPlayer(1).getPlace());
  ASSERT_EQ(0, testGame.getPlayer(0).getPurse());
  ASSERT_EQ(0, testGame.getPlayer(1).getPurse());
  ASSERT_EQ(false, testGame.getPlayer(0).getIsInPenaltyBox());
  ASSERT_EQ(false, testGame.getPlayer(1).getIsInPenaltyBox());
}

TEST (NextPlayer, OnePlayer)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  ASSERT_EQ(0, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(0, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(0, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(0, testGame.getCurrentPlayerId());
}

TEST (NextPlayer, MorePlayers)
{
  Game testGame;
  Player alice{"Alice"};  
  testGame.add(alice);
  Player bob{"Bob"};  
  testGame.add(bob);
  Player mallory{"Mallory"};  
  testGame.add(mallory);
  Player trudy{"Trudy"};  
  testGame.add(trudy);
  
  ASSERT_EQ(0, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(1, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(2, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(3, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(0, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(1, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(2, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(3, testGame.getCurrentPlayerId());
  testGame.changeCurrentPlayerToNextPlayer();
  ASSERT_EQ(0, testGame.getCurrentPlayerId());
}

TEST (AskQuestion, PopQuestions)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  ASSERT_EQ("Pop Question 0", testGame.getPopQuestion(0));
  for (int i = 1; i < 50; ++i)
  {
    testGame.askQuestion();
    std::string expected = "Pop Question " + std::to_string(i);
    ASSERT_EQ(expected, testGame.getPopQuestion(0));
  }
  ASSERT_EQ("Pop Question 49", testGame.getPopQuestion(0));
}

TEST (AskQuestion, ScienceQuestions)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  testGame.roll(1);
  ASSERT_EQ("Science Question 0", testGame.getScienceQuestion(0));
  for (int i = 1; i < 50; ++i)
  {
    testGame.askQuestion();
    std::string expected = "Science Question " + std::to_string(i);
    ASSERT_EQ(expected, testGame.getScienceQuestion(0));
  }
  ASSERT_EQ("Science Question 49", testGame.getScienceQuestion(0));
}

TEST (AskQuestion, SportsQuestions)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  testGame.roll(1);
  testGame.roll(1);
  ASSERT_EQ("Sports Question 0", testGame.getSportsQuestion(0));
  for (int i = 1; i < 50; ++i)
  {
    testGame.askQuestion();
    std::string expected = "Sports Question " + std::to_string(i);
    ASSERT_EQ(expected, testGame.getSportsQuestion(0));
  }
  ASSERT_EQ("Sports Question 49", testGame.getSportsQuestion(0));
}

TEST (AskQuestion, RockQuestions)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  testGame.roll(3);
  ASSERT_EQ("Rock Question 0", testGame.getRockQuestion(0));
  for (int i = 1; i < 50; ++i)
  {
    testGame.askQuestion();
    std::string expected = "Rock Question " + std::to_string(i);
    ASSERT_EQ(expected, testGame.getRockQuestion(0));
  }
  ASSERT_EQ("Rock Question 49", testGame.getRockQuestion(0));
}

TEST (DidPlayerWin, WinIfGreaterOrEqualToSix)
{
  Game testGame;
  Player alice{"Alice"};
  testGame.add(alice);
  for (int i = 0; i < 5; ++i)
  {    
    testGame.roll(1);
    testGame.wasCorrectlyAnswered();
    ASSERT_EQ(false, testGame.didPlayerWin());
  }
  testGame.roll(1);
  testGame.wasCorrectlyAnswered();
  ASSERT_EQ(true, testGame.didPlayerWin());
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}