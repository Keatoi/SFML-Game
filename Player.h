#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include "SoundManager.h"
class Player
{
private:
	int initial_X = 10;
	int initial_Y = 10;
	float HP = 100.f;
	SoundManager SM;
public:
	Player();
	virtual ~Player();
	sf::Sprite sprite;
	sf::Texture texture;

	float MoveSpeed;
	float CNNCooldown;
	float CNNCooldownMax;
	bool bIsImmortal = false;
	float ImmortalTimer;
	float MaxImmortal = 2.f;

	void initTexture();
	void initVar();
	void initSprite();
	void initSound();
	
	//Game funcs
	void Move(const float dirX, const float dirY);
	const bool bCanAttack();
	void Update(float deltaTime);
	void LookAtMouse(sf::RenderWindow& Win);
	void UpdateAttacks();
	void Render(sf::RenderTarget& Target);
	void teleport(float XCoord, float YCoord);
	float OnHit(float damage);
	//Getters
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
};

