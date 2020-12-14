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
#include<SFML/Audio.hpp>
#include"pics.h"


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
	bool playername;
	bool playstatus;
	bool cangetnewscores;
	bool firstendgames;

	int bloodcount = 0;

	//GUI
	sf::Font font;
	sf::Font Lamooned;
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

	bool sounddies;
	bool goldencat;
	sf::Music musicBG;

	sf::SoundBuffer ButtonClick;
	sf::Sound ButtonClicking;
	sf::SoundBuffer snack;
	sf::Sound SNACKS;
	sf::SoundBuffer SORE;
	sf::Sound sores;
	sf::SoundBuffer die;
	sf::Sound GameOver;
	sf::SoundBuffer Heal;
	sf::Sound blood;
	sf::SoundBuffer piwpiw;
	sf::Sound piw;

	sf::Clock deadtimes;
	sf::Clock nextpage;
	sf::Clock speedincrease;
	sf::Clock speeditemincrease;
	sf::Clock pushbackenemy;
	sf::Clock pushbackitem;
	sf::Clock randomskills;
	sf::Clock Bigtimes;
	sf::Clock goldencattimes;
	sf::Clock eastereggtimes;

	float plusSpeed=0.f;
	float speeditem = 0.f;

	int random;
	//Resources
	std::map <std::string, sf::Texture*>textures;
	std::map<std::string, sf::Texture*> pic;
	std::vector<Pics*> easter_egg;
	std::map<std::string, sf::Texture*> pic2;
	std::vector<Pics*> easter_egg2;
	std::map<std::string, sf::Texture*> pic3;
	std::vector<Pics*> easter_egg3;
	std::map<std::string, sf::Texture*> pic4;
	std::vector<Pics*> easter_egg4;
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

	bool bigbool;
	bool canswitch;
	bool opensound;

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
	void updateeasteregg();

	//render function
	void renderPlayer();
	void renderGUI();
	void render();
};