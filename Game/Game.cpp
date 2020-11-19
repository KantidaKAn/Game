#include "Game.h"
//start window
void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

//get new player
void Game::initplayer()
{
	this->player = new Player();
}

void Game::inititem()
{
	this->spawntimeMax = 10.f;
	this->spawntime = this->spawntimeMax;
}

void Game::initbackground()
{
	this->bg = new background();
}

void Game::inittextuer()
{
	this->textuers["BULLET"] = new sf::Texture();
	this->textuers["BULLET"]->loadFromFile("Cat/bullet.png");
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initGUI()
{
	//Load font
	if(this->font.loadFromFile("font/Lobster-Regular.ttf"));
	std::cout << "ERROR::GAME::Failed to load font" << "/n";

	//INit point texr
	this->pointext.setFont(this->font);
	this->pointext.setCharacterSize(20);
	this->pointext.setFillColor(sf::Color::Black);
	this->pointext.setPosition(sf::Vector2f(1130.f,10.f));
	this->pointext.setOutlineColor(sf::Color::White);
	this->pointext.setOutlineThickness(3);


	this->playerHpBar.setSize(sf::Vector2f(400.f, 30.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initsystems()
{
	this->pointed = 0;
}


//start BG

//start bullet

//Main starter functions
Game::Game()
{
	this->initwindow();
	
	this->directioncheck = 0;
	
	this->initbackground();
	
	this->initsystems();
	
	this->initplayer();
	
	this->inititem();
	
	this->inittextuer();
	
	this->initEnemies();

	this->initGUI();
}

//delete main function anythings 
Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->bg;

	//Delete textuer
	for (auto &i : this-> textuers )
	{
		delete i.second;
	}
	//Delete bulletsm
	for (auto* i : this->Bullets)
	{
		delete i;
	}

	//Delete item
	for (auto* i : this->ITEM) 
	{
		delete i;
	}

	//Delete enemies
	for (auto* i : this->enemies) 
	{
		delete i;
	}
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

void Game::updateItem()
{
	this->spawntime += 0.1f;
	if (this->spawntime >= this->spawntimeMax)
	{
		this->ITEM.push_back(new item(1380, rand()%(500-200)+200));
		this->spawntime = 0.f;
	}
	for (int i = 0; i < this->ITEM.size(); ++i) {
		bool item_removed = false;
		this->ITEM[i]->updated();
		if (this->player->getBounds().intersects(this->ITEM[i]->getBounds()))
		{
			this->ITEM.erase(this->ITEM.begin() + i);
			this->pointed += 3;
			std::cout << this->pointed << "\n";
			item_removed = true;
		}
		
		if (this->ITEM[i]->getBounds().left + ITEM[i]->getBounds().width < 0.f) {
			this->ITEM.erase(this->ITEM.begin() + i);
			item_removed = true;
		}
	}
}

void Game::updateCollision()
{
	//collision bottom of screen
	if (this->player->getpos().y + this->player->getBounds().height + 200 > this->window->getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getpos().x, this->window->getSize().y - this->player->getBounds().height - 200);
		this->player->jumping = false;
		this->player->jumpingUp = false;
		this->player->gravityBool = false;
	}
	if (this->player->getpos().x <= 0)
	{
		this->player->setPosition(0.f, this->player->getpos().y);
	}
	if (this->player->getpos().x + 186.f >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - 186.f, this->player->getpos().y);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& this-> player->canAttack())
	{
		this->Bullets.push_back(
			new bullet(this->textuers["BULLET"],
			(this->player->getpos().x+ this->player->getBounds().width/2.f)+50,
			(this->player->getpos().y)+130,1.f,0.f,12.f));
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
	
	this->updatebullet();

	this->updateItem();
	
	this->updateCollision();
	
	this->updateEnemiesandcombat();

	this->updateGUI();


}

void Game::updatebullet()
{
	unsigned counter = 0;
	for (auto* bulleter : this->Bullets)
	{
		bulleter->update();

		if (bulleter->getBounds().left + bulleter->getBounds().width > 1280.f)
		{
			delete this-> Bullets.at(counter);
			this->Bullets.erase(this->Bullets.begin() + counter);
			--counter;

		}

		++counter;
	}
}

void Game::updateEnemiesandcombat()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		int random = rand() % 2;
		if (random == 0) {
			this->enemies.push_back(new Enemy(2000.f, 350.f));
		}
		else if (random == 1) {
			this->enemies.push_back(new Enemy(2000.f, 450.f));
		}
		this->spawnTimer = 0.f;
	}

	for (int i =0; i <this->enemies.size();++i)
	{
		bool enemy_removed = false;
		this->enemies[i]->update();
		for (size_t k = 0; k < this->Bullets.size()&&!enemy_removed ; k++)
		{
			if (this->Bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				enemy_removed = true;
				this->pointed += 1;
				this->enemies.erase(this->enemies.begin() + i);
				this->Bullets.erase(this->Bullets.begin() + k);
			}
		}
		//Remove enemies at the bottom of the screen
		if (this->enemies[i]->getBounds().left +this->enemies[i]->getBounds().width< 0.f )
		{
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;
		}
		if (this->player->getBounds().intersects(this->enemies[i]->getBounds()))
		{
			this->player->loseHp(5);
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;
		}
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Scores  :  " << this->pointed;
	this->pointext.setString(ss.str());



	//hp of player
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(400.f * hpPercent, this->playerHpBar.getSize().y));

}

//render player
void Game::renderPlayer()
{
	this->player->render(*this->window);
}

void Game::renderGUI()
{
	this->window->draw(this->pointext);

	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

//render window
void Game::render()
{
	this->window->clear(); //for clear old frame
	this->bg->render(*this->window);
	for (auto* bulleter : this->Bullets)
	{
		bulleter->render(this->window);
	}

	for (auto* items : this->ITEM)
	{
		items->render(*this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->window);
	}
	this->renderPlayer(); //for made player
	this->renderGUI();
	this->window->display(); //for update new frame
}