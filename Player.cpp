#include "Player.h"


Player::Player()
{
	this->MoveSpeed = 10.f;
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::initTexture()
{
	//Load Texture from file
	if (texture.loadFromFile("Textures/player.png"))
	{
		std::cout << "Player Sprite found\n";
		
	}
}

void Player::initSprite()
{

	//Load texture to sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(initial_X, initial_Y);
	//Resize sprite
	this->sprite.scale(3.f, 3.f);
}

void Player::Move(const float dirX, const float dirY)
{
	this->sprite.move(this->MoveSpeed * dirX, this->MoveSpeed * dirY);
}

void Player::Update()
{
}

void Player::Render(sf::RenderTarget& Target)
{
	Target.draw(this->sprite);
	
}
