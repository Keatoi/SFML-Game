#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture& texture, float dir_x,float dir_y,float move_speed)
{
	this->BulletSprite.setTexture(texture);
	this->Direction.x = dir_x;
	this->Direction.y = dir_y;
	this->MoveSpeed = move_speed;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	//Movement
	this->BulletSprite.move(this->MoveSpeed * Direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->BulletSprite);
}
