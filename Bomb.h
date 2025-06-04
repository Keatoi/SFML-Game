#pragma once
#include<iostream>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include "SoundManager.h"
class Bomb
{
private:
	//pointer because we aren't going to load the texture every time we create a bullet

	sf::Sprite BombSprite;
	sf::CircleShape xplodeCS;
	SoundManager SM;
	float bombTimer = 3.f;
	float radius = 150.f;
	bool bExploded = false;
	bool bDelete = false;
	
public:
	Bomb();
	Bomb(sf::Texture* texture, float scale_X, float scale_Y, float X_Origin, float Y_Origin, float dir_x, float dir_y);
	void initSprite();
	void initSound();
	void explode();
	const sf::FloatRect getBounds() const;
	virtual ~Bomb();
	void update(float deltaTime);
	void render(sf::RenderTarget* target);
	bool isExploded() const { return bDelete; }
	sf::Vector2f getPosition() const { return BombSprite.getPosition(); }
	float getBlastRadius() const { return radius; }
};

