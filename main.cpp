#include<iostream>
#include "Game.h"
int main()
{
	//Init GameEngine
	Game Engine;
	//GameLoop
	while (Engine.Running())
	{
		
		//UPDATE LOOP
		Engine.update();
		//RENDER LOOP
		Engine.render();
		//Draw game

		
	}
	//EOA
	return 0;
}