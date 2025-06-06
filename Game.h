#pragma once

#include<map>
#include"Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "bomb.h"

/* Game Engine wrapper class*/
enum class GameState
{
	EMENU,
	EGAME,
	EOVER
};
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
	std::vector<std::unique_ptr<Bomb>> Bombs;
	float spawnTimer;
	float spawnTimerMax;
	GameState currState = GameState::EMENU;
	//GO
	sf::RectangleShape TestEnemy;
	std::vector<std::unique_ptr<Enemy>> enemies;
	//Player
	Player* player;
	//GUI
	sf::Font font;
	sf::Text scoreText;
	sf::Text HPText;
	sf::Text WaveText;
	//MenuGUI
	sf::Text MenuText;
	sf::Image Title;
	//Game Over GUI
	sf::Text GETitle;
	sf::Text GEScore;
	sf::Text GEQuit;
	//Sound
	SoundManager SM;
	//misc
	int waveCount = 0;
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
	void updateMenu();
	void updateInput();
	void updatePhysics();
	void spawnEnemyGroup(int count);
	void updateEnemies();
	void WaveTransition();
	void updateBattle();
	void updateGUI();
	void updateEnd();
	void renderMenu();
	void renderGame();
	void RenderEnd();
	void render();
	void renderGUI();
	void run();
	void restart();
	float distance(sf::Vector2f a, sf::Vector2f b) {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
};

