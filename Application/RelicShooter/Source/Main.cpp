#include "Game/Game.h"

int main()
{
	//Create Instance of the Game on the Stack
	Game game;
	//Initialise the Game's State
	game.Initialise();
	//Run the Game (Blocking Call)
	game.Run();


	//If we reach here, the game loop has executed
	return 0;
}
