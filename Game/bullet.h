#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class bullet
{
private :

	sf::Sprite shape;
	sf::Texture *textuer;

	sf::Vector2f direction;
	float movementSpeed;


public:

	bullet(sf::Texture *textuer,float pos_x,float pos_y, float dir_x ,float dir_y,float movement_speed);
	virtual ~bullet();

	//accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif //!BULLET