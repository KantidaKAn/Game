#include "Game.h"
//start window
void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

//get new player
void Game::initplayer()
{
	this->player = new Player();
}

void Game::initbackground()
{
	this->bg = new background();
}


//start BG

//start bullet

//Main starter functions
Game::Game()
{
	this->initwindow();
	this->directioncheck = 0;
	this->initbackground();
	this->initplayer();
}

//delete main function anythings 
Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->bg;
}

//run your game
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

//player updated
void Game::updatePlayer()
{
	this->player->updated();
}

void Game::updateCollision()
{
	//collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height + 30 > this->window->getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, this->window->getSize().y - this->player->getGlobalBounds().height - 30);
		this->player->jumping = false;
		this->player->jumpingUp = false;
		this->player->gravityBool = false;
	}
}

//update input
void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->directioncheck = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->directioncheck = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->directioncheck = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->directioncheck = 3;
	}
}


//window updated  
void Game::update()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		
		if (e.Event::type == sf::Event::KeyReleased &&
			(e.Event::key.code == sf::Keyboard::Up ||
				e.Event::key.code == sf::Keyboard::Down)
			)
		{
			this->player->resetAnimationTimer();
		}
	}
	this->bg->update();
	this->updatePlayer(); //for update player in window 
	this->updateInput();
	this->updateCollision();
}

//render player
void Game::renderPlayer()
{
	this->player->render(*this->window);
}

//render window
void Game::render()
{
	this->window->clear(); //for clear old frame
	this->bg->render(*this->window);
	this->renderPlayer(); //for made player
	this->window->display(); //for update new frame
}