#include "Game.h"

void Game::InitVariables()
{
	this->Window = nullptr;
}

void Game::InitWindow()
{
	this->VidMode.height = 480;
	this->VidMode.width = 640;
	this->Window = new sf::RenderWindow(this->VidMode, "Test", sf::Style::Titlebar | sf::Style::Close);
}

Game::Game()
{
	this->InitVariables();
	this->InitWindow();
}

Game::~Game()
{
	//prevent mem leak
	delete this->Window;
}
const bool Game::Running()
{
	return this->Window->isOpen();
}
void Game::EventUpdate()
{
	//Event Polling (while window is still recieving events)
	while (this->Window->pollEvent(this->EV))
	{
		switch (this->EV.type)
		{
			//Close Game Window via exit button and ESC
		case sf::Event::Closed:
			this->Window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->EV.key.code == sf::Keyboard::Escape) this->Window->close();
			break;
		}
	}
}
//FUNCTIONS
void Game::update()
{
	this->EventUpdate();
}

void Game::render()
{
	this->Window->clear(sf::Color::Red);//Clear last frame
	/*++++++++++++++++
	+++DRAW OBJ++++++++
	+++++++++++++++++++*/
	this->Window->display();//Send frame to display
}
