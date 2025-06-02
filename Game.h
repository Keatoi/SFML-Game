#pragma once

#include<map>
#include"Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "SoundManager.h"

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
	std::vector<std::unique_ptr<Bullet>> Projectiles;
	float spawnTimer;
	float spawnTimerMax;
	//GO
	sf::RectangleShape TestEnemy;
	std::vector<std::unique_ptr<Enemy>> enemies;
	//Player
	Player* player;
	//GUI
	sf::Font font;
	sf::Text scoreText;
	sf::Text HPText;
	//Sound
	SoundManager SM;
	//misc
	sf::Vector2i mousePos;
	int score;
	sf::Time deltaTime;
	int enemyCount;
	int spawnCount;
	int maxEnemies;
	//Private Functions
	void InitVariables();
	void InitWindow();
	void InitTextures();
	void InitEnemies();
	void InitPlayer();
	void InitGUI();
	void InitSound();
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
	void spawnEnemyGroup(int count);
	void updateEnemies();
	void updateBattle();
	void updateGUI();
	void render();
	void renderGUI();
	void run();
};

