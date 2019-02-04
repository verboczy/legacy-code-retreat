#include "Game.h"

#include <iostream>

Game::Game() : m_currentPlayer{0}
{
  m_currentCategory.reserve(12);
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

int Game::getCurrentPlayer()
{
  return m_currentPlayer;
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
  int place = m_players[m_currentPlayer].m_place;
  if (place > 11)
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
  m_players.push_back(t_player);
  //m_places[howManyPlayers()] = 0;
  //m_purses[howManyPlayers()] = 0;
  //m_inPenaltyBox[howManyPlayers()] = false;

  std::clog << t_player << " was added" << std::endl;
  std::clog << "Number of player(s): " << m_players.size() << std::endl;
}

int Game::howManyPlayers()
{
  return m_players.size();
}

void Game::roll(int t_roll)
{
  std::cout << m_players[m_currentPlayer] << " is the current player" << std::endl;
  std::cout << "(s)he has rolled a " << t_roll << std::endl;

  if (m_players[m_currentPlayer].m_isInPenaltyBox)
  {
    if (t_roll % 2 != 0)
    {
      m_isGettingOutOfPenaltyBox = true;

      std::cout << m_players[m_currentPlayer] << " is getting out of the penalty box" 
           << std::endl;
      m_players[m_currentPlayer].m_place = m_players[m_currentPlayer].m_place + t_roll;
      if (m_players[m_currentPlayer].m_place > 11)
      {
        m_players[m_currentPlayer].m_place = m_players[m_currentPlayer].m_place - 12;
      }

      std::cout << m_players[m_currentPlayer] << "'s new location is " 
                << m_players[m_currentPlayer].m_place << std::endl;
      std::cout << "The category is " << getCurrentCategory() << std::endl;
      askQuestion();
    }
    else
    {
      std::cout << m_players[m_currentPlayer] << " is not getting out of the penalty box" 
                << std::endl;
      m_isGettingOutOfPenaltyBox = false;
    }
  }
  else
  {
    m_players[m_currentPlayer].m_place = m_players[m_currentPlayer].m_place + t_roll;
    if (m_players[m_currentPlayer].m_place > 11)
    {
     m_players[m_currentPlayer].m_place = m_players[m_currentPlayer].m_place - 12;
    }

    std::cout << m_players[m_currentPlayer] << "'s new location is " 
              << m_players[m_currentPlayer].m_place << std::endl;
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
  if (getCurrentCategory() == "Science")
  {
    std::cout << m_scienceQuestions.front() << std::endl;
    m_scienceQuestions.pop_front();
  }
  if (getCurrentCategory() == "Sports")
  {
    std::cout << m_sportsQuestions.front() << std::endl;
    m_sportsQuestions.pop_front();
  }
  if (getCurrentCategory() == "Rock")
  {
    std::cout << m_rockQuestions.front() << std::endl;
    m_rockQuestions.pop_front();
  }
}

bool Game::wasCorrectlyAnswered()
{
  if (m_players[m_currentPlayer].m_isInPenaltyBox)
  {
    if (m_isGettingOutOfPenaltyBox)
    {
      std::cout << "Answer was correct!!!!" << std::endl;
      ++m_players[m_currentPlayer].m_purse;
      std::cout << m_players[m_currentPlayer] << " now has " 
                << m_players[m_currentPlayer].m_purse <<  " Gold Coins." << std::endl;

      bool winner = didPlayerWin();
      ++m_currentPlayer;
      if (m_currentPlayer == m_players.size())
      {
        m_currentPlayer = 0;
      }

      return winner;
    }
    else
    {
      ++m_currentPlayer;
      if (m_currentPlayer == m_players.size())
      {
        m_currentPlayer = 0;
      }
      
      return true;
    }
  }
  else
  {

    std::cout << "Answer was correct!!!!" << std::endl;
    ++m_players[m_currentPlayer].m_purse;
    std::cout << m_players[m_currentPlayer]
        << " now has "
        << m_players[m_currentPlayer].m_purse
      << " Gold Coins." << std::endl;

    bool winner = didPlayerWin();
    ++m_currentPlayer;
    if (m_currentPlayer == m_players.size())
    {
      m_currentPlayer = 0;
    }

    return winner;
  }
}

void Game::wrongAnswer()
{
  std::cout << "Question was incorrectly answered" << std::endl;
  std::cout << m_players[m_currentPlayer] << " was sent to the penalty box" << std::endl;
  m_players[m_currentPlayer].m_isInPenaltyBox = true;

  ++m_currentPlayer;
  if (m_currentPlayer == m_players.size())
  {    
    m_currentPlayer = 0;
  }
}

bool Game::didPlayerWin()
{
  return !(m_players[m_currentPlayer].m_purse == 6);
}

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

std::ostream& operator<<(std::ostream& t_os, Player const & t_player)
{
  t_os << t_player.m_name;
  return t_os;
}