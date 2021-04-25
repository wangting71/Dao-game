// DaoDriver.cpp: Driver for the game Dao.
// Author:		  Michael R. Scheessele
// Date:		  02/19/12
// Microsoft Visual C++
#include "Dao.h"

int main()
{
	// Seed random number generator.
	srand(time(0));

	Game game;	//'Game' is the environment class for the agents.

	do {
		game.playround();
	} while (!game.isover());

	// Show final state of the board and the winner.
	game.showstate();

	return 0;
}

