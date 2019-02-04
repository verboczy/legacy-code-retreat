#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include <string>

class Player;

class Game
{
  public:
    Game();
    
    std::string createRockQuestion(int t_index);
    
    std::string getPopQuestion(int t_index);
    std::string getScienceQuestion(int index);
    std::string getSportsQuestion(int t_index);
    std::string getRockQuestion(int t_index);
    Player getPlayer(int t_index);
    
    int getPlace(int t_index);
    int getPurse(int t_index);
    int getCurrentPlayer();
    
    bool isInPenaltyBox(int t_index);
    bool getIsGettingOutOfPenaltyBox();
    
    void add(Player t_player);
    bool isPlayable();
    int howManyPlayers();
    void roll(int t_roll);
    
    bool wasCorrectlyAnswered();
    void wrongAnswer();

    std::string getCurrentCategory();

  private:
    std::vector<Player> m_players;
    std::vector<std::string> m_currentCategory;

    std::list<std::string> m_popQuestions;
    std::list<std::string> m_scienceQuestions;
    std::list<std::string> m_sportsQuestions;
    std::list<std::string> m_rockQuestions;

    int m_currentPlayer;
    bool m_isGettingOutOfPenaltyBox;

    void askQuestion();

    bool didPlayerWin();
};

class Player
{
  friend class Game;
  public:
    Player(std::string t_name);
    std::string getName();
    int getPurse();
    int getPlace();
    bool getIsInPenaltyBox();
    
    friend std::ostream& operator<<(std::ostream& t_os, Player const & t_player);
    
  private:
    std::string m_name;
    int m_purse;
    int m_place;
    bool m_isInPenaltyBox;
};

#endif // GAME_H_