#include "Enemy.h"
#include "iostream"



void Enemy::initTexture()
{
	switch (this->type)
	{
	case 0:
		texture.loadFromFile("Textures/ship_B.png");
		std::cout << "using type 1";
			break;
	case 1:
		texture.loadFromFile("Textures/enemy_C.png");
		std::cout << "using type 1";
		break;
	default:
		break;
	}
}

void Enemy::initVar(int EnemyType)
{
	switch (EnemyType)
	{
	case 0:
		this->type = 0;
		this->maxHP = 1;
		this->hp = maxHP;
		this->damage = 1;
		this->points = 10;
		this->speed = 2.f;
		break;
	case 1:
		this->type = 1;
		this->maxHP = 5;
		this->hp = maxHP;
		this->damage = 1;
		this->points = 100;
		this->speed = 1.f;
		break;
	default:
		this->type = 2;
		this->maxHP = 1;
		this->hp = maxHP;
		this->damage = 1;
		this->points = 50;
		this->speed = 5.f;
		break;
	}
}

void Enemy::initSprite()
{
	//Load texture to sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(initial_X, initial_Y);
	//Resize sprite
	this->sprite.scale(3.f, 3.f);
}

Enemy::Enemy(int Enemytype, float scaleX, float scaleY, float posX, float posY)
{
	
	initVar(Enemytype);
	initTexture();
	initSprite();
	this->sprite.setPosition(posX, posY);
	this->sprite.scale(scaleX, scaleY);
}

Enemy::~Enemy()
{

}

const sf::Vector2f& Enemy::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Enemy::update()
{
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
