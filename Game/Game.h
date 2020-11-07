#pragma once
#include"Player.h"
#include"background.h"
class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	Player* player;
	background* bg;
	int directioncheck;

	//Function
	void initwindow();
	void initplayer();
	void initbackground();

public:
	//Game
	Game();
	virtual ~Game();

	//Update and render
	void run();

	//update function
	void updatePlayer();
	void updateCollision();
	void updateInput();
	void update();

	//render function
	void renderPlayer();
	void render();
};