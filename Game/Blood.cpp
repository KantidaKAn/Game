#include "Blood.h"

Blood::Blood(sf::Texture* texture, float pos_x, float pos_y)
{
	this->texture.set
}

Blood::~Blood()
{
}

const sf::FloatRect Blood::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Blood::update()
{
	this->shape.move(-2.f, 0.f);
}

void Blood::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}