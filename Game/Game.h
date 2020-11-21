#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Player.h"
#include"background.h"
#include<map>
#include"bullet.h"
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

	Mainmenu* menu;
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

	//GUI
	sf::Font font;
	sf::Text pointext;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;

	float spawnTimerblood;
	float spawnTimerbloodMax;

	int directioncheck;
	unsigned pointed;

	sf::Clock nextpage;

	//Resources
	std::map <std::string, sf::Texture*>textuers;
	std::vector<bullet*>Bullets;
	std::vector<Enemy*> enemies;
	std::vector<item*>ITEM;
	//Function
	void initwindow();
	void initplayer();
	void inititem();
	void initbackground();
	void inittextuer();
	void initEnemies();
	void initGUI();
	void initsystems();

	float spawntime;
	float spawntimeMax;

public:
	//Game
	Game();
	virtual ~Game();

	//Update and render
	void run();

	void updateMousePositions();
	//update function
	void updatePlayer();
	void updateItem();
	void updateCollision();
	void updateInput();
	void update();
	void updatebullet();
	void updateEnemiesandcombat();
	void updateGUI();

	//render function
	void renderPlayer();
	void renderGUI();
	void render();
};