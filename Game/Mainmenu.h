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
	sf::Texture scoreTexture;
	sf::Sprite scoresprite;
	sf::Texture nextbutton;
	sf::RectangleShape nextbuttonsprite;
	sf::RectangleShape beforebuttonsprite;
	sf::RectangleShape button[MAX_NUMBER_OF_ITEMS];
	sf::Texture buttonname;
	sf::Sprite namebuttonsprite;
	sf::Texture howtoplays[5];
	sf::Sprite howtoplaysprites[5];
	sf::Texture dietexture;
	sf::Sprite diespite;
	sf::Texture onoffsoundt;
	sf::Sprite onoffsounds;

	sf::RectangleShape soundoff;
	sf::RectangleShape soundon;
	bool playstate = false;
	int pages = 0;

public:
	Mainmenu(float width, float height);
	virtual ~Mainmenu();
	int GetPressedItem() { return selectedITEMindex; };
	void draw(sf::RenderWindow& window);
	void drawscore(sf::RenderWindow& window);
	void drawnamespace(sf::RenderWindow& window);
	void getplay(bool play);
	void Moveup();
	void Movedown();
	void buttoncheck(const int button);
	const sf::FloatRect getBounds_0() const;
	const sf::FloatRect getBounds_1() const;
	const sf::FloatRect getBounds_2() const;
	const sf::FloatRect getBounds_3() const;

	const sf::FloatRect nextgetbounds() const;
	const sf::FloatRect beforegetbounds() const;

	const sf::FloatRect soundoffbound() const;
	const sf::FloatRect soundonbound() const;
	void update();
	void howtoplay(sf::RenderWindow& window);
	void nextpages();
	void beforepages();
	const int getpages() const;
	void drawdie(sf::RenderWindow& window);
};
