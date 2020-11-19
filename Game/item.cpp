#include "item.h"

void item::inititemTexture()
{
	this->itemtexture.loadFromFile("Cat/Candy.png");
}

void item::inititemSprite()
{
	this->itemsprite.setTexture(this->itemtexture);
	this->itemsprite.setTextureRect(sf::IntRect((rand() % 5) * 103, (rand() % 5) * 104, 103, 104));
	this->itemsprite.setScale(0.7f, 0.7f);
}

item::item(float pos_x, float pos_y)
{
	this->itemposition = sf::Vector2f(pos_x, pos_y);
	this->itemsprite.setPosition(sf::Vector2f(this->itemposition));

	this->inititemTexture();
	this->inititemSprite();
}

item::~item()
{
}

const sf::FloatRect item::getBounds() const
{
	return this->itemsprite.getGlobalBounds();
}

void item::updatemovement()
{
	this->itemsprite.move(-3.0f, 0.f);
}

void item::updated()
{
	this->updatemovement();
}

void item::render(sf::RenderTarget& target)
{
	target.draw(this->itemsprite);
}
