
#pragma once
#include "Player.h"
class background
{
private:
	//variables
	sf::Sprite SpriteBG;
	sf::Texture TextureBG;
	sf::Vector2f positionBG;

	sf::Sprite Spritefloor;
	sf::Texture Texturefloor;
	sf::Vector2f positionfloor;

	//Function
	void initSpiteBG();
	void initTextureBG();



public:
	background();
	virtual ~background();

	void update();

	//render
	void render(sf::RenderTarget& target);
};