#include "Game.h"

#include <iostream>

Game::Game() : m_currentPlayer(0), m_places({}), m_purses({})
{
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

std::string Game::getPlayer(int t_index)
{
  return m_players[t_index];
}

int Game::getPlace(int t_index)
{
  return m_places[t_index];
}

int Game::getPurse(int t_index)
{
  return m_purses[t_index];
}

bool Game::isInPenaltyBox(int t_index)
{
  return m_inPenaltyBox[t_index];
}

bool Game::getIsGettingOutOfPenaltyBox()
{
  return m_isGettingOutOfPenaltyBox;
}

bool Game::isPlayable()
{
  return (howManyPlayers() >= 2);
}

bool Game::add(std::string t_playerName){
  m_players.push_back(t_playerName);
  m_places[howManyPlayers()] = 0;
  m_purses[howManyPlayers()] = 0;
  m_inPenaltyBox[howManyPlayers()] = false;

  std::clog << t_playerName << " was added" << std::endl;
  std::clog << "Number of player(s): " << m_players.size() << std::endl;
  
  return true;
}

int Game::howManyPlayers()
{
  return m_players.size();
}

void Game::roll(int t_roll)
{
  std::cout << m_players[m_currentPlayer] << " is the current player" << std::endl;
  std::cout << "(s)he has rolled a " << t_roll << std::endl;

  if (m_inPenaltyBox[m_currentPlayer])
  {
    if (t_roll % 2 != 0)
    {
      m_isGettingOutOfPenaltyBox = true;

      std::cout << m_players[m_currentPlayer] << " is getting out of the penalty box" 
           << std::endl;
      m_places[m_currentPlayer] = m_places[m_currentPlayer] + t_roll;
      if (m_places[m_currentPlayer] > 11)
      {
        m_places[m_currentPlayer] = m_places[m_currentPlayer] - 12;
      }

      std::cout << m_players[m_currentPlayer] << "'s new location is " 
                << m_places[m_currentPlayer] << std::endl;
      std::cout << "The category is " << currentCategory() << std::endl;
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
    m_places[m_currentPlayer] = m_places[m_currentPlayer] + t_roll;
    if (m_places[m_currentPlayer] > 11)
    {
      m_places[m_currentPlayer] = m_places[m_currentPlayer] - 12;
    }

    std::cout << m_players[m_currentPlayer] << "'s new location is " 
              << m_places[m_currentPlayer] << std::endl;
    std::cout << "The category is " << currentCategory() << std::endl;
    askQuestion();
  }
}

void Game::askQuestion()
{
  if (currentCategory() == "Pop")
  {
    std::cout << m_popQuestions.front() << std::endl;
    m_popQuestions.pop_front();
  }
  if (currentCategory() == "Science")
  {
    std::cout << m_scienceQuestions.front() << std::endl;
    m_scienceQuestions.pop_front();
  }
  if (currentCategory() == "Sports")
  {
    std::cout << m_sportsQuestions.front() << std::endl;
    m_sportsQuestions.pop_front();
  }
  if (currentCategory() == "Rock")
  {
    std::cout << m_rockQuestions.front() << std::endl;
    m_rockQuestions.pop_front();
  }
}

std::string Game::currentCategory()
{
  if (m_places[m_currentPlayer] == 0) return "Pop";
  if (m_places[m_currentPlayer] == 4) return "Pop";
  if (m_places[m_currentPlayer] == 8) return "Pop";
  if (m_places[m_currentPlayer] == 1) return "Science";
  if (m_places[m_currentPlayer] == 5) return "Science";
  if (m_places[m_currentPlayer] == 9) return "Science";
  if (m_places[m_currentPlayer] == 2) return "Sports";
  if (m_places[m_currentPlayer] == 6) return "Sports";
  if (m_places[m_currentPlayer] == 10) return "Sports";
  
  return "Rock";
}

bool Game::wasCorrectlyAnswered()
{
  if (m_inPenaltyBox[m_currentPlayer])
  {
    if (m_isGettingOutOfPenaltyBox)
    {
      std::cout << "Answer was correct!!!!" << std::endl;
      ++m_purses[m_currentPlayer];
      std::cout << m_players[m_currentPlayer] << " now has " 
                << m_purses[m_currentPlayer] <<  " Gold Coins." << std::endl;

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
    ++m_purses[m_currentPlayer];
    std::cout << m_players[m_currentPlayer]
        << " now has "
        << m_purses[m_currentPlayer]
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

bool Game::wrongAnswer()
{
  std::cout << "Question was incorrectly answered" << std::endl;
  std::cout << m_players[m_currentPlayer] << " was sent to the penalty box" << std::endl;
  m_inPenaltyBox[m_currentPlayer] = true;

  ++m_currentPlayer;
  if (m_currentPlayer == m_players.size())
  {    
    m_currentPlayer = 0;
  }
  
  return true;
}

bool Game::didPlayerWin()
{
  return !(m_purses[m_currentPlayer] == 6);
}
