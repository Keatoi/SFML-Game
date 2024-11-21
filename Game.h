#pragma once

#include<map>
#include"Player.h"
#include "Bullet.h"

/* Game Engine wrapper class*/
class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* Window;
	sf::Event EV;
	sf::VideoMode VidMode;
	//Resource maps
	std::map<std::string, sf::Texture*> Textures;
	std::vector<Bullet*> Projectiles;
	//GO
	sf::RectangleShape TestEnemy;
	//Player
	Player* player;

	//misc
	sf::Vector2i mousePos;
	//Private Functions
	void InitVariables();
	void InitWindow();
	void InitTextures();
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
	void updateInput();
	void updatePhysics();
	void render();
	void run();
};

