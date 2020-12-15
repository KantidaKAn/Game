#include "Mainmenu.h"

Mainmenu::Mainmenu(float width, float height)
{
	BGTexture.loadFromFile("Cat/menu.png");
	BGSprite.setTexture(this->BGTexture);

	scoreTexture.loadFromFile("Cat/HIHGSCOR.png");
	scoresprite.setTexture(this->scoreTexture);

	howtoplays[0].loadFromFile("Cat/How_to_play1.png");
	howtoplays[1].loadFromFile("Cat/How_to_play2.png");
	howtoplays[2].loadFromFile("Cat/How_to_play3.png");
	howtoplays[3].loadFromFile("Cat/How_to_play4.png");
	for (int i = 0; i < 4 ; i++) {
		howtoplaysprites[i].setTexture(howtoplays[i]);
	}

	font.loadFromFile("Font/Good Things.ttf");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(70);
	menu[0].setPosition(sf::Vector2f((width / 2) - 300.f, (height / (MAX_NUMBER_OF_ITEMS + 1) * 1) - 60));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Score");
	menu[1].setCharacterSize(70);
	menu[1].setPosition(sf::Vector2f((width / 2) - 300.f,( height / (MAX_NUMBER_OF_ITEMS + 1) * 2)-70));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("how to play");
	menu[2].setCharacterSize(70);
	menu[2].setPosition(sf::Vector2f((width / 2) - 350.f, (height / (MAX_NUMBER_OF_ITEMS + 1) * 3)-70));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setCharacterSize(70);
	menu[3].setPosition(sf::Vector2f((width / 2) - 300.f, (height / (MAX_NUMBER_OF_ITEMS + 1) * 4)-70));

	buttonname.loadFromFile("Cat/namespace3.png");
	namebuttonsprite.setTexture(this->buttonname);
	namebuttonsprite.setPosition(sf::Vector2f((width / 2) - 150.f, (height / 2) - 150.f));

	nextbutton.loadFromFile("Cat/arrow.png");
	nextbuttonsprite.setSize(sf::Vector2f(105.f, 75.f));
	nextbuttonsprite.setTexture(&this->nextbutton);
	nextbuttonsprite.setPosition(1150.f, 600.f);

	beforebuttonsprite.setSize(sf::Vector2f(105.f, 75.f));
	beforebuttonsprite.setScale(-1.f, 1.f);
	beforebuttonsprite.setTexture(&this->nextbutton);
	beforebuttonsprite.setPosition(130.f, 600.f);
	selectedITEMindex = 0;

	dietexture.loadFromFile("Cat/GameOver.png");
	diespite.setTexture(this->dietexture);

	onoffsoundt.loadFromFile("Cat/Void.png");
	onoffsounds.setTexture(this->onoffsoundt);
	onoffsounds.setScale(0.5f, 0.5f);
	onoffsounds.setPosition(10.f, 0.f);

	soundoff.setSize(sf::Vector2f(50.f,50.f));
	soundoff.setPosition(10.f, 10.f);
	soundoff.setFillColor(sf::Color::Transparent);

	soundon.setSize(sf::Vector2f(50.f, 50.f));
	soundon.setPosition(100.f, 10.f);
	soundon.setFillColor(sf::Color::Transparent);

	Eastereggtextures.loadFromFile("Cat/easteregg.png");
	Eastereggsprite.setTexture(this->Eastereggtextures);
	Eastereggsprite.setPosition(725.f,0.f);
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
	//window.draw()
}

void Mainmenu::drawscore(sf::RenderWindow& window)
{
	window.draw(this->scoresprite);
	window.draw(this->beforebuttonsprite);
}

void Mainmenu::drawnamespace(sf::RenderWindow& window)
{
	window.draw(namebuttonsprite);
}

void Mainmenu::drawpics(sf::RenderWindow& window)
{
	window.draw(this->Eastereggsprite);
	window.draw(this->onoffsounds);
	window.draw(this->soundoff);
	window.draw(this->soundon);
}

void Mainmenu::getplay(bool play)
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
	return this->menu[0].getGlobalBounds();
}
const sf::FloatRect Mainmenu::getBounds_1() const
{
	return this->menu[1].getGlobalBounds();
}

const sf::FloatRect Mainmenu::getBounds_2() const
{
	return this->menu[2].getGlobalBounds();
}

const sf::FloatRect Mainmenu::getBounds_3() const
{
	return this->menu[3].getGlobalBounds();
}

const sf::FloatRect Mainmenu::nextgetbounds() const
{
	return this->nextbuttonsprite.getGlobalBounds();
}

const sf::FloatRect Mainmenu::beforegetbounds() const
{
	return this->beforebuttonsprite.getGlobalBounds();
}

const sf::FloatRect Mainmenu::soundoffbound() const
{
	return this->soundoff.getGlobalBounds();
}

const sf::FloatRect Mainmenu::soundonbound() const
{
	return this->soundon.getGlobalBounds();
}

const sf::FloatRect Mainmenu::easterbound() const
{
	return this-> Eastereggsprite.getGlobalBounds();
}

void Mainmenu::update()
{
	if (playstate) {
		menu[0].setString("RESUME");
	}
}

void Mainmenu::howtoplay(sf::RenderWindow& window)
{
	window.draw(this->howtoplaysprites[this->pages]);
	if (this->pages < 3) {
		window.draw(this->nextbuttonsprite);
	}
	window.draw(this->beforebuttonsprite);
}

void Mainmenu::nextpages()
{
	if (this->pages < 3) {
		(this->pages)++;
	}
}

void Mainmenu::beforepages()
{
	if (this->pages > 0) {
		(this->pages)--;
	}
	else this->pages = 0;
}

const int Mainmenu::getpages() const
{
	return this->pages;
}

void Mainmenu::drawdie(sf::RenderWindow& window)
{
	window.draw(this->diespite);
}
