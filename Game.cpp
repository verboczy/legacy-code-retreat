#include "Game.h"

#include <iostream>

// Parameterless constructor for Game. 
// It initialises current playr to 0, and is getting out of penalty box to false.
Game::Game() : m_currentPlayerId{0}, m_isGettingOutOfPenaltyBox{false}
{
  // Create categories on the place
  m_currentCategory.reserve(PLACE_SIZE);
  m_currentCategory.push_back("Pop");
  m_currentCategory.push_back("Science");
  m_currentCategory.push_back("Sports");
  m_currentCategory.push_back("Rock");
  m_currentCategory.push_back("Pop");
  m_currentCategory.push_back("Science");
  m_currentCategory.push_back("Sports");
  m_currentCategory.push_back("Rock");
  m_currentCategory.push_back("Pop");
  m_currentCategory.push_back("Science");
  m_currentCategory.push_back("Sports");
  m_currentCategory.push_back("Rock");
  // Add questions to categories
  for (int i = 0; i < 50; ++i)
  {
    std::string iToString = std::to_string(i);
    m_popQuestions.push_back("Pop Question " + iToString);
    m_scienceQuestions.push_back("Science Question " + iToString);
    m_sportsQuestions.push_back("Sports Question " + iToString);    
    m_rockQuestions.push_back("Rock Question " + iToString);
  }
}

// Returns the index-th pop question.
std::string Game::getPopQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_popQuestions.begin(); it != m_popQuestions.end(); ++it)
  {
    if (count == t_index)
    {
      return *it;
    }
    ++count;
  }  
  return "";
}

// Returns the index-th science question.
std::string Game::getScienceQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_scienceQuestions.begin(); it != m_scienceQuestions.end(); ++it)
  {
    if (count == t_index)
    {
      return *it;
    }
    ++count;
  }  
  return "";
}

// Returns the index-th sports question.
std::string Game::getSportsQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_sportsQuestions.begin(); it != m_sportsQuestions.end(); ++it)
  {
    if (count == t_index)
    {
      return *it;
    }
    ++count;
  }  
  return "";
}

// Returns the index-th rock question.
std::string Game::getRockQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_rockQuestions.begin(); it != m_rockQuestions.end(); ++it)
  {
    if (count == t_index)
    {
      return *it;
    }
    ++count;
  }  
  return "";
}

// Returns the id of the current player.
int Game::getCurrentPlayerId()
{
  return m_currentPlayerId;
}

// Returns the index-th player.
Player Game::getPlayer(int t_index)
{
  return m_players[t_index];
}

// Returns is getting out of penalty box.
bool Game::getIsGettingOutOfPenaltyBox()
{
  return m_isGettingOutOfPenaltyBox;
}

// Returns the current category, based on the current player's place.
std::string Game::getCurrentCategory()
{
  int place = m_players[m_currentPlayerId].m_place;
  if (place > PLACE_SIZE - 1)
  {
    return "Rock";
  }
  return m_currentCategory[place];
}

// Returns whether the game is playable. 
// True if there are more than 2 players.
bool Game::isPlayable()
{
  return (howManyPlayers() >= 2);
}

// Adds player the players, if the player has not been added already.
void Game::add(Player t_player){
  if (!(isPlayingAlready(t_player)))
  {
    m_players.push_back(t_player);   
    std::clog << t_player << " was added" << std::endl;
    std::clog << "Number of player(s): " << m_players.size() << std::endl;
  }
  else
  {
    std::clog << t_player << " is already playing" << std::endl;
  }
}

// Returns if the given player is in the players.
bool Game::isPlayingAlready(Player const & t_player)
{
  for (auto it = m_players.begin(); it != m_players.end(); ++it)
  {
    if (*it == t_player)
    {
      return true;
    }
  }  
  return false;
}

// Returns the number of players.
int Game::howManyPlayers()
{
  return m_players.size();
}

// Puts the player in the next place or lets out the player 
// from the penalty box, or not. Returns true if a question should be asked from 
// the current player, false otherwise
bool Game::roll(int t_roll)
{
  std::cout << m_players[m_currentPlayerId] << " is the current player" << std::endl;
  std::cout << "(s)he has rolled a " << t_roll << std::endl;

  // Current player is in penalty box
  if (m_players[m_currentPlayerId].m_isInPenaltyBox)
  {
    // Gets out of penalty box
    if (t_roll % 2 != 0)
    {
      m_isGettingOutOfPenaltyBox = true;
      std::cout << m_players[m_currentPlayerId] << " is getting out of the penalty box" 
           << std::endl;
      incrementPlace(t_roll);
      return true;
    }
    // Remains in penalty box
    else
    {
      std::cout << m_players[m_currentPlayerId] 
                << " is not getting out of the penalty box" << std::endl;
      m_isGettingOutOfPenaltyBox = false;
      return false;
    }
  }
  // Not in penalty box
  else
  {
    incrementPlace(t_roll);
    return true;
  }
}

// Adds the roll value to the current player's place.
// It is greater, than the maximal place, then the player starts a new lap.
void Game::incrementPlace(int t_roll)
{
    m_players[m_currentPlayerId].m_place = 
      m_players[m_currentPlayerId].m_place + t_roll;
    if (m_players[m_currentPlayerId].m_place > PLACE_SIZE - 1)
    {
      m_players[m_currentPlayerId].m_place = 
        m_players[m_currentPlayerId].m_place - PLACE_SIZE;
    }

    std::cout << m_players[m_currentPlayerId] << "'s new location is " 
              << m_players[m_currentPlayerId].m_place << std::endl;
    std::cout << "The category is " << getCurrentCategory() << std::endl;
}

// Ask question
void Game::askQuestion()
{
  if (getCurrentCategory() == "Pop")
  {
    std::cout << m_popQuestions.front() << std::endl;
    m_popQuestions.pop_front();
  }
  else if (getCurrentCategory() == "Science")
  {
    std::cout << m_scienceQuestions.front() << std::endl;
    m_scienceQuestions.pop_front();
  }
  else if (getCurrentCategory() == "Sports")
  {
    std::cout << m_sportsQuestions.front() << std::endl;
    m_sportsQuestions.pop_front();
  }
  else if (getCurrentCategory() == "Rock")
  {
    std::cout << m_rockQuestions.front() << std::endl;
    m_rockQuestions.pop_front();
  }
}

// The player answered correctly. If (s)he has enough money, 
// then (s)he is the winner, and the game is over.
bool Game::wasCorrectlyAnswered()
{
  // Current player is in penalty box
  if (m_players[m_currentPlayerId].m_isInPenaltyBox)
  {
    // Gets out
    if (m_isGettingOutOfPenaltyBox)
    {
      bool winner = correctAnswerNotRemainInPenalty();      
      return winner;
    }
    // Remains in penalty box
    else
    {
      return false;
    }
  }
  // Not in penalty box
  else
  {
    bool winner = correctAnswerNotRemainInPenalty();    
    return winner;
  }
}

// Answer was correct, increase purse. Returns if the player has enough money.
bool Game::correctAnswerNotRemainInPenalty()
{
  std::cout << "Answer was correct!!!!" << std::endl;
  ++m_players[m_currentPlayerId].m_purse;
  std::cout << m_players[m_currentPlayerId] << " now has " 
            << m_players[m_currentPlayerId].m_purse << " Gold Coins." << std::endl;
  return didPlayerWin();
}

// The answer was wrong. Put the current player into the penalty box.
void Game::wrongAnswer()
{
  std::cout << "Question was incorrectly answered" << std::endl;
  std::cout << m_players[m_currentPlayerId] 
            << " was sent to the penalty box" << std::endl;
  m_players[m_currentPlayerId].m_isInPenaltyBox = true;
}

// Returns if the player has enough money.
bool Game::didPlayerWin()
{
  return m_players[m_currentPlayerId].m_purse >= PURSE_LIMIT;
}

// Set current player to the next player.
void Game::changeCurrentPlayerToNextPlayer()
{
  ++m_currentPlayerId;
  if (m_currentPlayerId >= m_players.size())
  {
    m_currentPlayerId = 0;
  }
}

/********************** Player methods **********************/
// Player's constructor with name parameter. 
// It initialises purse to 0,
// place to 0,
// and is in penalty box to false.
Player::Player(std::string t_name) : 
  m_name{t_name}, m_purse{0}, m_place{0}, m_isInPenaltyBox{false} 
{
  // Initialised everything
}

// Returns player's name.
std::string Player::getName()
{
  return m_name;
}

// Returns player's purse.
int Player::getPurse()
{
  return m_purse;
}

// Returns player's place.
int Player::getPlace()
{
  return m_place;
}

// Returns if the player is in penalty box.
bool Player::getIsInPenaltyBox()
{
  return m_isInPenaltyBox;
}

// Two players are equal if, their names are equal.
bool Player::operator==(Player const & t_rhs)
{
  return (this->m_name == t_rhs.m_name);
}

// Two players are not equal, if they are not equal.
bool Player::operator!=(Player const & t_rhs)
{
  return !(*this == t_rhs);
}

// Using << on a player, accesses the name.
std::ostream& operator<<(std::ostream& t_os, Player const & t_player)
{
  t_os << t_player.m_name;
  return t_os;
}