#include "enemy.h"

void Enemy::initShape()
{
	this->textture.loadFromFile("Cat/1.png");
	this->shape.setScale(0.3f,0.3f);
	this->shape.setTexture(this->textture);
}

void Enemy::initVariables()
{
	this->speed = 5.0f;
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->initShape();
	this->initVariables();

	this->shape.setPosition(pos_x, pos_y);
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
void Enemy::update()
{
	this->shape.move(-(this->speed), 0.f);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}


