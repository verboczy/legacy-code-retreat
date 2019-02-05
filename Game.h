#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include <string>

class Player
{
  friend class Game;
  public:
    Player(std::string t_name);
    std::string getName();
    int getPurse();
    int getPlace();
    bool getIsInPenaltyBox();
    
    bool operator==(Player const & t_rhs);
    bool operator!=(Player const & t_rhs);
    
    friend std::ostream& operator<<(std::ostream& t_os, Player const & t_player);
    
  private:
    std::string m_name;
    int m_purse;
    int m_place;
    bool m_isInPenaltyBox;
};

class Game
{
  public:
    const int PLACE_SIZE = 12;
  
    Game();
    
    std::string createRockQuestion(int t_index);
    
    std::string getPopQuestion(int t_index);
    std::string getScienceQuestion(int index);
    std::string getSportsQuestion(int t_index);
    std::string getRockQuestion(int t_index);
    
    Player getPlayer(int t_index);
    int getCurrentPlayerId();        
    bool getIsGettingOutOfPenaltyBox();
    
    bool isPlayable();
    void add(Player t_player); // Intentionally passed by value
    bool isPlayingAlready(Player const & t_player);
    int howManyPlayers();
    void roll(int t_roll);
    
    bool wasCorrectlyAnswered();
    void wrongAnswer();

    std::string getCurrentCategory();
    void changeCurrentPlayerToNextPlayer();
    void askQuestion();
    bool didPlayerWin();
    
  private:
    std::vector<Player> m_players;
    std::vector<std::string> m_currentCategory;

    std::list<std::string> m_popQuestions;
    std::list<std::string> m_scienceQuestions;
    std::list<std::string> m_sportsQuestions;
    std::list<std::string> m_rockQuestions;

    unsigned int m_currentPlayerId;
    bool m_isGettingOutOfPenaltyBox;
    
    void incrementPlace(int t_roll);
    bool correctAnswerNotRemainInPenalty();
};

#endif // GAME_H_