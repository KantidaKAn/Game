#ifndef BLOOD_H
#define BLOOD_H

#include"Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Blood
{
private:
	//texture and sprite Blood
	sf::Sprite shape;
	sf::Texture* texture;

	//Bloods status
	sf::Vector2f direction;
	float movementSpeed;

public:
	//bullet functions
	Blood(sf::Texture* texture, float pos_x, float pos_y);
	virtual ~Blood();

	//getBounds functions
	const sf::FloatRect getBounds() const;

	//render and update functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif // !BLOOD_H