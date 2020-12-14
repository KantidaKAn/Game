#ifndef PICS_H
#define PICS_H
#include<SFML/Graphics.hpp>
#include<iostream>
class Pics
{
private:
	//texture and sprite fire
	sf::Sprite shape;
	sf::Texture* texture;

	//fire status
	sf::Vector2f direction;
	float movementSpeed;

public:
	//fire functions
	Pics(sf::Texture* texture, float pos_x, float pos_y);
	virtual ~Pics();

	//getBounds functions
	const sf::FloatRect getBounds() const;

	//render and update functions
	void update();
	void render(sf::RenderTarget* target);
};
#endif // !PICS_H
