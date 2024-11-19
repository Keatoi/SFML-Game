#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
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
	//misc
	sf::Vector2i mousePos;
	//Private Functions
	void InitVariables();
	void InitWindow();
	void InitEnemies();
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
};

