#include "enemy.h"

void Enemy::initShape()
{
	this->textture.loadFromFile("Cat/1.png");
	this->shape.setScale(0.4f,0.4f);
	this->shape.setTexture(this->textture);
}



Enemy::Enemy(float pos_x,float pos_y)
{
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
	this->speed = 5.0f;
}

Enemy::~Enemy()
{

}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

//Function
void Enemy::update(float plus)
{
	this->shape.move(-((this->speed)+plus), 0.f);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}


