#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include <string>

class Game{
  public:
    Game();
    
    std::string createRockQuestion(int t_index);
    
    std::string getPopQuestion(int t_index);
    std::string getScienceQuestion(int index);
    std::string getSportsQuestion(int t_index);
    std::string getRockQuestion(int t_index);
    std::string getPlayer(int t_index);
    
    int getPlace(int t_index);
    int getPurse(int t_index);
    int getCurrentPlayer();
    
    bool isInPenaltyBox(int t_index);
    bool getIsGettingOutOfPenaltyBox();
    
    void add(std::string t_playerName);
    bool isPlayable();
    int howManyPlayers();
    void roll(int t_roll);
    
    bool wasCorrectlyAnswered();
    void wrongAnswer();

    std::string currentCategory();

  private:
    std::vector<std::string> m_players;

    int m_places[6];
    int m_purses[6];

    bool m_inPenaltyBox[6];

    std::list<std::string> m_popQuestions;
    std::list<std::string> m_scienceQuestions;
    std::list<std::string> m_sportsQuestions;
    std::list<std::string> m_rockQuestions;

    int m_currentPlayer;
    bool m_isGettingOutOfPenaltyBox;

    void askQuestion();

    bool didPlayerWin();
};

#endif // GAME_H_