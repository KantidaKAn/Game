
#pragma once
#include "Player.h"
class background
{
private:
	//variables
	sf::Sprite SpriteBG;
	sf::Texture TextureBG;

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