
#include "Background.h"
#include<SFML/Graphics.hpp>
//Texture BG
void background::initTextureBG()
{
	this->TextureBG.loadFromFile("Cat/GB.png");
}

//Sprite BG
void background::initSpiteBG()
{
	this->SpriteBG.setTexture(this->TextureBG);
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
	this->SpriteBG.move(-0.10f, 0.f);
}

//render BG
void background::render(sf::RenderTarget& target)
{
	target.draw(this->SpriteBG);
}