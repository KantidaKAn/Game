#include "Background.h"
#include<SFML/Graphics.hpp>
//Texture BG
void background::initTextureBG()
{
	this->TextureBG.loadFromFile("Cat/GB.png");
	this->Texturefloor.loadFromFile("Cat/floor.png");
}

//Sprite BG
void background::initSpiteBG()
{
	this->SpriteBG.setTexture(this->TextureBG);
	this->positionBG = sf::Vector2f(0.f, 0.f);
	this->SpriteBG.setPosition(this->positionBG);

	this->Spritefloor.setTexture(this->Texturefloor);
	this->positionfloor = sf::Vector2f(0.f, 600.f);
	this->Spritefloor.setPosition(this->positionfloor);
}

background::background()
{
	//texture and Sprite
	this->initTextureBG();
	this->initSpiteBG();
}

background::~background()
{
}

void background::update()
{
	this->SpriteBG.move(-0.1f, 0.f);
	this->positionBG.x -= 0.1f;
	if (this->positionBG.x < -9187.5f)
	{
		this->positionBG.x = 0.0f;
		this->SpriteBG.setPosition(this->positionBG);
	}
}

//render BG
void background::render(sf::RenderTarget& target)
{
	target.draw(this->SpriteBG);
	target.draw(this->Spritefloor);
}