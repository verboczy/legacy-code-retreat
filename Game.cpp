#include "Game.h"

#include <iostream>

Game::Game() : m_currentPlayerId{0}, m_isGettingOutOfPenaltyBox{false}
{
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
  
  for (int i = 0; i < 50; ++i)
  {
    std::string iToString = std::to_string(i);
    m_popQuestions.push_back("Pop Question " + iToString);
    m_scienceQuestions.push_back("Science Question " + iToString);
    m_sportsQuestions.push_back("Sports Question " + iToString);    
    m_rockQuestions.push_back("Rock Question " + iToString);
  }
}

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
}

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
}

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
}

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
}

int Game::getCurrentPlayerId()
{
  return m_currentPlayerId;
}

Player Game::getPlayer(int t_index)
{
  return m_players[t_index];
}

int Game::getPlace(int t_index)
{
  return m_players[t_index].m_place;
}

int Game::getPurse(int t_index)
{
  return m_players[t_index].m_purse;
}

bool Game::isInPenaltyBox(int t_index)
{
  return m_players[t_index].m_isInPenaltyBox;
}

bool Game::getIsGettingOutOfPenaltyBox()
{
  return m_isGettingOutOfPenaltyBox;
}

std::string Game::getCurrentCategory()
{
  int place = m_players[m_currentPlayerId].m_place;
  if (place > PLACE_SIZE - 1)
  {
    return "Rock";
  }
  return m_currentCategory[place];
}

bool Game::isPlayable()
{
  return (howManyPlayers() >= 2);
}

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

bool Game::isPlayingAlready(Player t_player)
{
  for (auto it = m_players.begin(); it != m_players.end(); ++it)
  {
    if (t_player == *it)
    {
      return true;
    }
  }
  
  return false;
}

int Game::howManyPlayers()
{
  return m_players.size();
}

void Game::roll(int t_roll)
{
  std::cout << m_players[m_currentPlayerId] << " is the current player" << std::endl;
  std::cout << "(s)he has rolled a " << t_roll << std::endl;

  if (m_players[m_currentPlayerId].m_isInPenaltyBox)
  {
    if (t_roll % 2 != 0)
    {
      m_isGettingOutOfPenaltyBox = true;

      std::cout << m_players[m_currentPlayerId] << " is getting out of the penalty box" 
           << std::endl;
      m_players[m_currentPlayerId].m_place = m_players[m_currentPlayerId].m_place + t_roll;
      if (m_players[m_currentPlayerId].m_place > PLACE_SIZE - 1)
      {
        m_players[m_currentPlayerId].m_place = m_players[m_currentPlayerId].m_place - PLACE_SIZE;
      }

      std::cout << m_players[m_currentPlayerId] << "'s new location is " 
                << m_players[m_currentPlayerId].m_place << std::endl;
      std::cout << "The category is " << getCurrentCategory() << std::endl;
      askQuestion();
    }
    else
    {
      std::cout << m_players[m_currentPlayerId] << " is not getting out of the penalty box" 
                << std::endl;
      m_isGettingOutOfPenaltyBox = false;
    }
  }
  else
  {
    m_players[m_currentPlayerId].m_place = m_players[m_currentPlayerId].m_place + t_roll;
    if (m_players[m_currentPlayerId].m_place > PLACE_SIZE - 1)
    {
      m_players[m_currentPlayerId].m_place = m_players[m_currentPlayerId].m_place - PLACE_SIZE;
    }

    std::cout << m_players[m_currentPlayerId] << "'s new location is " 
              << m_players[m_currentPlayerId].m_place << std::endl;
    std::cout << "The category is " << getCurrentCategory() << std::endl;
    askQuestion();
  }
}

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

bool Game::wasCorrectlyAnswered()
{
  if (m_players[m_currentPlayerId].m_isInPenaltyBox)
  {
    if (m_isGettingOutOfPenaltyBox)
    {
      std::cout << "Answer was correct!!!!" << std::endl;
      ++m_players[m_currentPlayerId].m_purse;
      std::cout << m_players[m_currentPlayerId] << " now has " 
                << m_players[m_currentPlayerId].m_purse <<  " Gold Coins." << std::endl;

      bool winner = didPlayerWin();
      changeCurrentPlayerToNextPlayer();

      return winner;
    }
    else
    {
      changeCurrentPlayerToNextPlayer();
      
      return true;
    }
  }
  else
  {

    std::cout << "Answer was correct!!!!" << std::endl;
    ++m_players[m_currentPlayerId].m_purse;
    std::cout << m_players[m_currentPlayerId] << " now has " << m_players[m_currentPlayerId].m_purse
              << " Gold Coins." << std::endl;

    bool winner = didPlayerWin();
    changeCurrentPlayerToNextPlayer();

    return winner;
  }
}

void Game::wrongAnswer()
{
  std::cout << "Question was incorrectly answered" << std::endl;
  std::cout << m_players[m_currentPlayerId] << " was sent to the penalty box" << std::endl;
  m_players[m_currentPlayerId].m_isInPenaltyBox = true;
  changeCurrentPlayerToNextPlayer();
}

bool Game::didPlayerWin()
{
  return !(m_players[m_currentPlayerId].m_purse == 6);
}


void Game::changeCurrentPlayerToNextPlayer()
{
  ++m_currentPlayerId;
  if (m_currentPlayerId >= m_players.size())
  {
    m_currentPlayerId = 0;
  }
}

/********************** Player methods **********************/

Player::Player(std::string t_name) : m_name{t_name}, m_place{0}, m_purse{0}, m_isInPenaltyBox{false} 
{
  // Initialised everything
}

std::string Player::getName()
{
  return m_name;
}

int Player::getPurse()
{
  return m_purse;
}

int Player::getPlace()
{
  return m_place;
}

bool Player::getIsInPenaltyBox()
{
  return m_isInPenaltyBox;
}

bool Player::operator==(Player const & t_rhs)
{
  return (this->m_name == t_rhs.m_name);
}

bool Player::operator!=(Player const & t_rhs)
{
  return !(*this == t_rhs);
}

std::ostream& operator<<(std::ostream& t_os, Player const & t_player)
{
  t_os << t_player.m_name;
  return t_os;
}