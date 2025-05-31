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
	float SpawnX;
	float SpawnY;
	float freq = 0.05f;
	float amp = 50.f;
	float phaseOffset = 0.f;
	void initTexture();
	void initVar(int EnemyType);
	void initSprite();

public:
	float initial_X = 10.f;
	float initial_Y = 10.f;

	Enemy(int type,float scaleX,float scaleY, float posX, float posY, float amplitude, float frequency, float phase);
	~Enemy();
	//Getters
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int getPoints() const;

	void update(sf::Time DeltaTime);
	void render(sf::RenderTarget* target);
};

