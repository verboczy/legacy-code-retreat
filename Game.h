#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include <string>
using namespace std;

class Game{
  public:
    Game();
    
    string createRockQuestion(int t_index);
    
    string getPopQuestion(int t_index);
    string getScienceQuestion(int index);
    string getSportsQuestion(int t_index);
    string getRockQuestion(int t_index);
    string getPlayer(int t_index);
    
    int getPlace(int t_index);
    int getPurse(int t_index);
    int getCurrentPlayer();
    
    bool isInPenaltyBox(int t_index);
    bool getIsGettingOutOfPenaltyBox();
    
    bool isPlayable();
    bool add(string t_playerName);
    bool wasCorrectlyAnswered();
    bool wrongAnswer();

    int howManyPlayers();
    void roll(int t_roll);

    string currentCategory();

  private:
    vector<string> m_players;

    int m_places[6];
    int m_purses[6];

    bool m_inPenaltyBox[6];

    list<string> m_popQuestions;
    list<string> m_scienceQuestions;
    list<string> m_sportsQuestions;
    list<string> m_rockQuestions;

    int m_currentPlayer;
    bool m_isGettingOutOfPenaltyBox;

    void askQuestion();

    bool didPlayerWin();
};

#endif // GAME_H_