#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture,float scale_X, float scale_Y, float X_Origin, float Y_Origin, float dir_x,float dir_y,float move_speed)
{
	this->BulletSprite.setTexture(*texture);
	this->BulletSprite.scale(scale_X, scale_Y);
	this->BulletSprite.setPosition(X_Origin, Y_Origin);
	this->Direction.x = dir_x;
	this->Direction.y = dir_y;
	this->MoveSpeed = move_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->BulletSprite.getGlobalBounds();
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
