#include "Player.h"


Player::Player()
{
	this->initVar();
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

void Player::initVar()
{
	this->MoveSpeed = 10.f;
	this->CNNCooldownMax = 10.f;
	this->CNNCooldown = this->CNNCooldownMax;
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

const bool Player::bCanAttack()
{
	if (this->CNNCooldown >= this->CNNCooldownMax)
	{
		this->CNNCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::Update(float deltaTime)
{
	this->UpdateAttacks();
}

void Player::UpdateAttacks()
{
	if (this->CNNCooldown < this->CNNCooldownMax)
	{
		this->CNNCooldown += 0.75f;
	}
	
}

void Player::Render(sf::RenderTarget& Target)
{
	Target.draw(this->sprite);
	
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
	
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
