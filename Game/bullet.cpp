#include "bullet.h"


bullet::bullet(sf::Texture*textuer, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*textuer);

	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

bullet::~bullet()
{

}

const sf::FloatRect bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void bullet::update()
{
	//Movement
	this->shape.move(this->movementSpeed*this->direction);
}

void bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
