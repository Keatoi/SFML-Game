#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
class Player
{
private:
	int initial_X = 10;
	int initial_Y = 10;
public:
	Player();
	virtual ~Player();
	sf::Sprite sprite;
	sf::Texture texture;

	float MoveSpeed;

	void initTexture();
	void initSprite();
	
	//Game funcs
	void Move(const float dirX, const float dirY);
	void Update();
	void Render(sf::RenderTarget& Target);
};

