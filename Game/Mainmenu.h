#pragma once
#include"player.h"

#define MAX_NUMBER_OF_ITEMS 4
class Mainmenu
{
private:
	int selectedITEMindex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Texture BGTexture;
	sf::Sprite BGSprite;
	sf::RectangleShape button[MAX_NUMBER_OF_ITEMS];

	int playstate;


public:
	Mainmenu(float width, float height);
	virtual ~Mainmenu();
	int GetPressedItem() { return selectedITEMindex; };
	void draw(sf::RenderWindow& window);
	void getplay(const int play);
	void Moveup();
	void Movedown();
	void buttoncheck(const int button);
	const sf::FloatRect getBounds_0() const;
	const sf::FloatRect getBounds_1() const;
	const sf::FloatRect getBounds_2() const;
	const sf::FloatRect getBounds_3() const;
	void update();
}; class Menu
{
};

