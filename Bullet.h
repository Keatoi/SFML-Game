#pragma once
#include<iostream>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
class Bullet
{
private:
	//pointer because we aren't going to load the texture every time we create a bullet
	
	sf::Sprite BulletSprite;
	sf::Vector2f Direction;
	float MoveSpeed;
public:
	Bullet();
	Bullet(sf::Texture& texture, float dir_x, float dir_y, float move_speed);
	virtual ~Bullet();

	void update();
	void render(sf::RenderTarget* target);
};

