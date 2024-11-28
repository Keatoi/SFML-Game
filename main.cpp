#include<iostream>
#include "Game.h"
int main()
{
	srand((unsigned)time(0));
	//Init GameEngine
	Game Engine;
	//GameLoop
	Engine.run();
	//EOA
	return 0;
}