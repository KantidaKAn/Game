#include "Mainmenu.h"

Mainmenu::Mainmenu(float width, float height)
{
	BGTexture.loadFromFile("Sprite/BGmenu.png");
	BGSprite.setTexture(this->BGTexture);

	font.loadFromFile("font/Lobster-Regular.ttf");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(40);
	menu[0].setPosition(sf::Vector2f((width / 2) - 15.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	button[0].setSize(sf::Vector2f(200.f, 50.f));
	button[0].setFillColor(sf::Color::Black);
	button[0].setPosition(sf::Vector2f((width / 2) - 100.f, (height / (MAX_NUMBER_OF_ITEMS + 1) * 1) + 10.f));


	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("score");
	menu[1].setCharacterSize(40);
	menu[1].setPosition(sf::Vector2f((width / 2) - 15.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	button[1].setSize(sf::Vector2f(200.f, 50.f));
	button[1].setFillColor(sf::Color::Black);
	button[1].setPosition(sf::Vector2f((width / 2) - 100.f, (height / (MAX_NUMBER_OF_ITEMS + 1) * 2) + 10.f));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("how to play");
	menu[2].setCharacterSize(40);
	menu[2].setPosition(sf::Vector2f((width / 2) - 50.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	button[2].setSize(sf::Vector2f(200.f, 50.f));
	button[2].setFillColor(sf::Color::Black);
	button[2].setPosition(sf::Vector2f((width / 2) - 100.f, (height / (MAX_NUMBER_OF_ITEMS + 1) * 3) + 10.f));


	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(40);
	menu[3].setPosition(sf::Vector2f((width / 2) - 15.f, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));
	button[3].setSize(sf::Vector2f(200.f, 50.f));
	button[3].setFillColor(sf::Color::Black);
	button[3].setPosition(sf::Vector2f((width / 2) - 100.f, (height / (MAX_NUMBER_OF_ITEMS + 1) * 4) + 10.f));

	selectedITEMindex = 0;
}

Mainmenu::~Mainmenu()
{

}

void Mainmenu::draw(sf::RenderWindow& window)
{
	window.draw(this->BGSprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(button[i]);
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void Mainmenu::getplay(const int play)
{
	this->playstate = play;
}

void Mainmenu::Moveup()
{
	if (selectedITEMindex - 1 >= 0) {
		menu[selectedITEMindex].setFillColor(sf::Color::White);
		selectedITEMindex--;
		menu[selectedITEMindex].setFillColor(sf::Color::Red);
	}
}

void Mainmenu::Movedown()
{
	if (selectedITEMindex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedITEMindex].setFillColor(sf::Color::White);
		selectedITEMindex++;
		menu[selectedITEMindex].setFillColor(sf::Color::Red);
	}
}

void Mainmenu::buttoncheck(const int button)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		if (button == i) {
			selectedITEMindex = button;
			menu[selectedITEMindex].setFillColor(sf::Color::Red);
		}
		else {
			menu[i].setFillColor(sf::Color::White);
		}
	}
}
const sf::FloatRect Mainmenu::getBounds_0() const
{
	return this->button[0].getGlobalBounds();
}
const sf::FloatRect Mainmenu::getBounds_1() const
{
	return this->button[1].getGlobalBounds();
}

const sf::FloatRect Mainmenu::getBounds_2() const
{
	return this->button[2].getGlobalBounds();
}

const sf::FloatRect Mainmenu::getBounds_3() const
{
	return this->button[3].getGlobalBounds();
}

void Mainmenu::update()
{
	if (playstate == 1) {
		menu[0].setString("RESUME");
	}
	else if (playstate == 0) {}
}