#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Sprite shape;
	sf::Texture textture;
	float speed;
	void initShape();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Function
	void update(float plus);
	void render(sf::RenderTarget& target);
};

#endif //!ENEMY_H