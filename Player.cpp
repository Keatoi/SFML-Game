#include "Player.h"


Player::Player()
{
	this->initVar();
	this->initTexture();
	this->initSprite();
	this->initSound();
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
	this->CNNCooldownMax = 5.f;
	this->CNNCooldown = this->CNNCooldownMax;
	this->MaxImmortal = 3.f;
	this->ImmortalTimer = MaxImmortal;
}

void Player::initSprite()
{

	//Load texture to sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(initial_X, initial_Y);
	//Resize sprite
	this->sprite.scale(3.f, 3.f);
}

void Player::initSound()
{
	SM.loadSound("PCDeath", "Audio/Explosion.wav");
	
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
	if (bIsImmortal)
	{
		this->ImmortalTimer -= deltaTime;
		if (this->ImmortalTimer <= 0)
		{
			
			bIsImmortal = false;
		}
	}
	
}

void Player::LookAtMouse(sf::RenderWindow &Win)
{
	sf::Vector2f currPos = this->sprite.getPosition();
	sf::Vector2i mousePos = sf::Mouse::getPosition(Win);
	const float PI = 3.14159265;

	float dX = currPos.x - mousePos.x;
	float dY = currPos.y - mousePos.y;

	float rotation = (atan2(dX, dY)) * 180 / PI;
	
	this->sprite.setRotation(rotation + 180);
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

void Player::teleport(float XCoord, float YCoord)
{
	this->sprite.setPosition(XCoord, YCoord);
}

float Player::OnHit(float damage)
{
	if (!bIsImmortal)
	{
		bIsImmortal = true;
		HP -= damage;
		this->ImmortalTimer = this->MaxImmortal;
		if (HP <= 0)
		{
			//ENDGAME
			SM.playSound("PCDeath");
		}
	}
	
	return HP;
	
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
	
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
