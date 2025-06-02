#pragma once
#include<iostream>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include "SoundManager.h"
class Bullet
{
private:
	//pointer because we aren't going to load the texture every time we create a bullet
	
	sf::Sprite BulletSprite;
	sf::Vector2f Direction;
	float MoveSpeed;
	SoundManager SM;
public:
	Bullet();
	Bullet(sf::Texture* texture, float scale_X, float scale_Y,float X_Origin, float Y_Origin, float dir_x, float dir_y, float move_speed);
	virtual ~Bullet();
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);

};

