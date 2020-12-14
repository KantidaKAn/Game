#include "pics.h"

Pics::Pics(sf::Texture* texture, float pos_x, float pos_y)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.5f,0.5f);
	this->shape.setPosition(pos_x, pos_y);
}

Pics::~Pics()
{
}

const sf::FloatRect Pics::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Pics::update()
{
	this->shape.move(0.f,-2.f);
}

void Pics::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}