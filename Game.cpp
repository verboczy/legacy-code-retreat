#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game() : m_currentPlayer(0), m_places({}), m_purses({})
{
  for (int i = 0; i < 50; i++)
  {
    ostringstream oss (ostringstream::out);
    oss << "Pop Question " << i;
    
    m_popQuestions.push_back(oss.str());

    char str[255];
    sprintf(str, "Science Question %d", i);
    m_scienceQuestions.push_back(str);

    char str1[255];
    sprintf(str1, "Sports Question %d", i);
    m_sportsQuestions.push_back(str1);

    m_rockQuestions.push_back(createRockQuestion(i));
  }
}

string Game::getPopQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_popQuestions.begin(); it != m_popQuestions.end(); it++)
  {
    if (count == t_index)
    {
      return *it;
    }
    count++;
  }
}

string Game::getScienceQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_scienceQuestions.begin(); it != m_scienceQuestions.end(); it++)
  {
    if (count == t_index)
    {
      return *it;
    }
    count++;
  }
}

string Game::getSportsQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_sportsQuestions.begin(); it != m_sportsQuestions.end(); it++)
  {
    if (count == t_index)
    {
      return *it;
    }
    count++;
  }
}

string Game::getRockQuestion(int t_index)
{
  int count = 0;
  for (auto it = m_rockQuestions.begin(); it != m_rockQuestions.end(); it++)
  {
    if (count == t_index)
    {
      return *it;
    }
    count++;
  }
}

string Game::createRockQuestion(int t_index)
{
  char indexStr[127];
  sprintf(indexStr, "Rock Question %d", t_index);
  return indexStr;
}

int Game::getCurrentPlayer()
{
  return m_currentPlayer;
}

string Game::getPlayer(int t_index)
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

bool Game::add(string t_playerName){
  m_players.push_back(t_playerName);
  m_places[howManyPlayers()] = 0;
  m_purses[howManyPlayers()] = 0;
  m_inPenaltyBox[howManyPlayers()] = false;

  cout << t_playerName << " was added" << endl;
  cout << "They are player number " << m_players.size() << endl;
  
  return true;
}

int Game::howManyPlayers()
{
  return m_players.size();
}

void Game::roll(int t_roll)
{
  cout << m_players[m_currentPlayer] << " is the current player" << endl;
  cout << "They have rolled a " << t_roll << endl;

  if (m_inPenaltyBox[m_currentPlayer])
  {
    if (t_roll % 2 != 0)
    {
      m_isGettingOutOfPenaltyBox = true;

      cout << m_players[m_currentPlayer] << " is getting out of the penalty box" << endl;
      m_places[m_currentPlayer] = m_places[m_currentPlayer] + t_roll;
      if (m_places[m_currentPlayer] > 11)
      {
        m_places[m_currentPlayer] = m_places[m_currentPlayer] - 12;
      }

      cout << m_players[m_currentPlayer] << "'s new location is " << m_places[m_currentPlayer] << endl;
      cout << "The category is " << currentCategory() << endl;
      askQuestion();
    }
    else
    {
      cout << m_players[m_currentPlayer] << " is not getting out of the penalty box" << endl;
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

    cout << m_players[m_currentPlayer] << "'s new location is " << m_places[m_currentPlayer] << endl;
    cout << "The category is " << currentCategory() << endl;
    askQuestion();
  }
}

void Game::askQuestion()
{
  if (currentCategory() == "Pop")
  {
    cout << m_popQuestions.front() << endl;
    m_popQuestions.pop_front();
  }
  if (currentCategory() == "Science")
  {
    cout << m_scienceQuestions.front() << endl;
    m_scienceQuestions.pop_front();
  }
  if (currentCategory() == "Sports")
  {
    cout << m_sportsQuestions.front() << endl;
    m_sportsQuestions.pop_front();
  }
  if (currentCategory() == "Rock")
  {
    cout << m_rockQuestions.front() << endl;
    m_rockQuestions.pop_front();
  }
}

string Game::currentCategory()
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
      cout << "Answer was correct!!!!" << endl;
      m_purses[m_currentPlayer]++;
      cout << m_players[m_currentPlayer]
           << " now has "
           << m_purses[m_currentPlayer]
        <<  " Gold Coins." << endl;

      bool winner = didPlayerWin();
      m_currentPlayer++;
      if (m_currentPlayer == m_players.size())
      {
        m_currentPlayer = 0;
      }

      return winner;
    }
    else
    {
      m_currentPlayer++;
      if (m_currentPlayer == m_players.size())
      {
        m_currentPlayer = 0;
      }
      
      return true;
    }
  }
  else
  {

    cout << "Answer was corrent!!!!" << endl;
    m_purses[m_currentPlayer]++;
    cout << m_players[m_currentPlayer]
        << " now has "
        << m_purses[m_currentPlayer]
      << " Gold Coins." << endl;

    bool winner = didPlayerWin();
    m_currentPlayer++;
    if (m_currentPlayer == m_players.size())
    {
      m_currentPlayer = 0;
    }

    return winner;
  }
}

bool Game::wrongAnswer()
{
  cout << "Question was incorrectly answered" << endl;
  cout << m_players[m_currentPlayer] + " was sent to the penalty box" << endl;
  m_inPenaltyBox[m_currentPlayer] = true;

  m_currentPlayer++;
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
