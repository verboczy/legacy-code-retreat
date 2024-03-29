﻿#include <stdlib.h>
#include <time.h>

#include "Game.h"

int main()
{
	Game aGame;
  bool isGameOver = false; 

  Player chet{"Chet"};
	aGame.add(chet);
  Player pat{"Pat"};
	aGame.add(pat);
  Player sue{"Sue"};
	aGame.add(sue);
  
  srand(time(NULL));  // Initialise random seed

	while (!isGameOver)
	{
		bool shouldAskQuestion = aGame.roll(rand() % 6 + 1); // [1, 6]

    if (shouldAskQuestion)
    {
      aGame.askQuestion();
      if (rand() % 5 == 0) // p(wrongAnswer) = 0.2 -> p(goodAnswer) = 0.8
      {
        aGame.wrongAnswer();
      }
      else
      {
        isGameOver = aGame.wasCorrectlyAnswered();
      }
    }
    aGame.changeCurrentPlayerToNextPlayer();    
	}
}
