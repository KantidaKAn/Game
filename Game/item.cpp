#include "item.h"

void item::inititemTexture()
{
	if (types == 0) {
		this->itemtexture.loadFromFile("Cat/Candy.png");
	}
	else if (types == 1) {
		this->itemtexture.loadFromFile("Cat/blood.png");
	}
	else if (types==2)
	{
		this->itemtexture.loadFromFile("Cat/food.png");
	}
}

void item::inititemSprite()
{
	if (types == 0) {
		this->itemsprite.setTexture(this->itemtexture);
		this->itemsprite.setTextureRect(sf::IntRect((rand() % 5) * 103, (rand() % 5) * 104, 103, 104));
		this->itemsprite.setScale(0.7f, 0.7f);
	}
	else if (types == 1) {
		this->itemsprite.setTexture(this->itemtexture);
		this->itemsprite.setScale(0.3f, 0.3f);
	}
	else if (types == 2) {
		this->itemsprite.setTexture(this->itemtexture);
		this->itemsprite.setScale(0.5f, 0.5f);
	}
}

item::item(float pos_x, float pos_y,int type)
{
		this->itemposition = sf::Vector2f(pos_x, pos_y);
		this->itemsprite.setPosition(sf::Vector2f(this->itemposition));


		types = type;

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

const int item::gettype() const
{
	return this->types;
}





void item::updated(float plus)
{
	this->itemsprite.move(-3.0f-plus, 0.f);
}

void item::render(sf::RenderTarget& target)
{
	target.draw(this->itemsprite);
}
