#include <iostream>
#include <list>
#include <vector>
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game{
  public:
    Game();
    
    string createRockQuestion(int index);
    
    string getPopQuestion(int index);
    string getScienceQuestion(int index);
    string getSportsQuestion(int index);
    string getRockQuestion(int index);
    string getPlayer(int index);
    int getPlace(int index);
    int getPurse(int index);
    bool isInPenaltyBox(int index);
    bool getIsGettingOutOfPenaltyBox();
    int getCurrentPlayer();
    
    bool isPlayable();
    bool add(string playerName);
    bool wasCorrectlyAnswered();
    bool wrongAnswer();

    int howManyPlayers();
    void roll(int roll);

    string currentCategory();

  private:
    vector<string> players;

    int places[6];
    int purses[6];

    bool inPenaltyBox[6];

    list<string> popQuestions;
    list<string> scienceQuestions;
    list<string> sportsQuestions;
    list<string> rockQuestions;

    int currentPlayer;
    bool isGettingOutOfPenaltyBox;

    void askQuestion();

    bool didPlayerWin();
};

#endif /* GAME_H_ */
