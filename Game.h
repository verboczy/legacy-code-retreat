#include <iostream>
#include <list>
#include <vector>
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game{

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

public:
	Game();
  string getPopQuestion(int index);
  string getScienceQuestion(int index);
  string getSportsQuestion(int index);
  string getRockQuestion(int index);
	string createRockQuestion(int index);
  string getPlayer(int index);
  int getPlace(int index);
  int getPurse(int index);
  bool isInPenaltyBox(int index);
  bool getIsGettingOutOfPenaltyBox();
  int getCurrentPlayer();
	bool isPlayable();
	bool add(string playerName);

	int howManyPlayers();
	void roll(int roll);

	private:
		void askQuestion();
		string currentCategory();

				public:
					bool wasCorrectlyAnswered();
					bool wrongAnswer();

private:
	bool didPlayerWin();
};

#endif /* GAME_H_ */
