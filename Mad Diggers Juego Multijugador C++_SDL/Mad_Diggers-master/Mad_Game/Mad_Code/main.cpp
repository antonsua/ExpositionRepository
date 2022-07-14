//Mad_Diggers

#include "checkML.h" //for memory leaks
#include "Game.h"

int main(int ac, char** av)
{
	//see if there are memory leaks (in debug mode)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.start();

	return 0;
}
