#pragma once
#include"Player.h"
#include"background.h"
#include<map>
#include"bullet.h"
#include"item.h"
#include"enemy.h"
#include<string>
#include<sstream>
class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	Player* player;
	background* bg;

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