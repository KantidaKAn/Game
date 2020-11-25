#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Player.h"
#include"background.h"
#include<map>
#include"item.h"
#include"enemy.h"
#include<string>
#include<sstream>
#include"Mainmenu.h"
#include"Textbox.h"
#include<utility>
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;
class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	Player* player;
	background* bg;

	Mainmenu* mainmenu;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosview;
	bool checkname = false;

	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	vector<pair<int, string>>userScore;
	int gamestate = 0;
	bool playername = false;
	bool playstatus = false;
	bool cangetnewscores = false;
	bool firstendgames = false;

	int bloodcount = 0;
	//GUI
	sf::Font font;
	sf::Text pointext;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimerEnemies;
	float spawnTimerEnemiesMax;

	float spawnTimerblood;
	float spawnTimerbloodMax;

	float spawntimeitem;
	float spawntimeitemMax;

	int directioncheck;
	unsigned pointed;
	unsigned point;

	sf::Clock deadtimes;

	sf::Clock nextpage;
	sf::Clock speedincrease;
	sf::Clock pushbackenemy;

	float plusSpeed=0.f;


	//Resources
	std::map <std::string, sf::Texture*>textures;
	std::vector<Enemy*> enemies;
	std::vector<item*>ITEM;
	//Function
	void initwindow();
	void initplayer();
	void inititem();
	void initbackground();
	void initEnemies();
	void initGUI();
	void initsystems();



public:
	//Game
	Game();
	virtual ~Game();

	//Update and render
	void run();
	void showhighscore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font);

	void updateMousePositions();
	//update function
	void updatePlayer();
	void updateItem();
	void updateCollision();
	void updateInput();
	void update();
	void updateEnemiesandcombat();
	void updateGUI();

	//render function
	void renderPlayer();
	void renderGUI();
	void render();
};