#pragma once
#include"Player.h"

/* Game Engine wrapper class*/
class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* Window;
	sf::Event EV;
	sf::VideoMode VidMode;

	//GO
	sf::RectangleShape TestEnemy;
	//Player
	Player* player;

	//misc
	sf::Vector2i mousePos;
	//Private Functions
	void InitVariables();
	void InitWindow();
	void InitEnemies();
	void InitPlayer();
public:
	//Constructors & Destructors
	Game();
	~Game();
	
	//getters
	const bool Running();
	//Functions
	void EventUpdate(); //poll events
	void update();
	void render();
	void run();
};

