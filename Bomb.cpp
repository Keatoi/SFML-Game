#include "Bomb.h"

Bomb::Bomb()
{
}

Bomb::Bomb(sf::Texture* texture, float scale_X, float scale_Y, float X_Origin, float Y_Origin, float dir_x, float dir_y)
{
	this->BombSprite.setTexture(*texture);
	this->BombSprite.setScale(scale_X, scale_Y);
	this->BombSprite.setPosition(X_Origin, Y_Origin);
	this->initSound();
}

void Bomb::initSprite()
{
}

void Bomb::initSound()
{
	SM.loadSound("bomb", "Audio/SoundWave.wav");
}


void Bomb::explode()
{
	std::cout << "BOOM" << std::endl;
	SM.playSound("bomb");
	bExploded = true;
	bombTimer = 0.5f;
	//Visuals
	xplodeCS.setPosition(getPosition());
	xplodeCS.setRadius(radius);
	xplodeCS.setOrigin(radius, radius);
	xplodeCS.setOutlineColor(sf::Color::Magenta);
	xplodeCS.setOutlineThickness(2.f);
	xplodeCS.setFillColor(sf::Color(255, 0, 255, 100));
	
}

const sf::FloatRect Bomb::getBounds() const
{
	return sf::FloatRect();
}

Bomb::~Bomb()
{
}

void Bomb::update(float deltaTime)
{
	
	if (!bExploded)
	{
		bombTimer -= deltaTime;
		if (bombTimer <= 0.f)
		{
			explode();
			bombTimer = 0.25f;
		}
	}
	else
	{
		bombTimer -= deltaTime;
		if (bombTimer <= 0.f)
		{
			bDelete = true;
		}
		
	}
	
}

void Bomb::render(sf::RenderTarget* target)
{
	if (!bExploded)
	{
		target->draw(this->BombSprite);
	}
	else
	{
		target->draw(this->xplodeCS);
	}

}
	
