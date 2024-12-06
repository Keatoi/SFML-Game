#pragma once
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

class Enemy
{
private:
	
	sf::Sprite sprite;
	sf::Texture texture;
	int type;
	int hp;
	int maxHP;
	float speed;
	int damage;
	int points;
	void initTexture();
	void initVar(int EnemyType);
	void initSprite();

public:
	int initial_X = 10;
	int initial_Y = 10;

	Enemy(int type,float scaleX,float scaleY, float posX, float posY);
	~Enemy();
	//Getters
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const float getPoints() const;

	void update();
	void render(sf::RenderTarget* target);
};

