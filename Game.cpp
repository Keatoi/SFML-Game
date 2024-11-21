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
	this->Window->setFramerateLimit(30);
}

void Game::InitEnemies()
{
	this->TestEnemy.setPosition(10.f,10.f);
	this->TestEnemy.setSize(sf::Vector2f(50.f, 50.f));
	this->TestEnemy.setFillColor(sf::Color::Magenta);
	this->TestEnemy.setOutlineColor(sf::Color::Black);
	this->TestEnemy.setOutlineThickness(1.f);
}

void Game::InitPlayer()
{
	//Create a new player object
	this->player = new Player();
}

Game::Game()
{
	this->InitVariables();
	this->InitWindow();
	this->InitPlayer();
	this->InitEnemies();
}

Game::~Game()
{
	//prevent mem leak
	delete this->Window;
	delete this->player;
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
	//update mouse Pos relative to window
	//std::cout << "Mouse Pos ( " << sf::Mouse::getPosition(*this->Window).x << " , " << sf::Mouse::getPosition(*this->Window).y << " ) \n";
	mousePos = sf::Mouse::getPosition(*this->Window);
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->player->Move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->player->Move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->player->Move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->player->Move(0.f, 1.f);
	
}

void Game::render()
{
	this->Window->clear(sf::Color::Black);//Clear last frame
	/*++++++++++++++++
	+++DRAW OBJ++++++++
	+++++++++++++++++++*/
	//this->Window->draw(TestEnemy);
	this->player->Render(*this->Window);
	this->Window->display();//Send frame to display
}

void Game::run()
{
	while (Running())
	{
		update();
		render();
	}
}
