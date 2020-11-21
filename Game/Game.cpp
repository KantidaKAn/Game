#include "Game.h"
//start window
void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game", sf::Style::Close |sf::Style::Resize| sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->menu = new Mainmenu(this->window->getSize().x, window->getSize().y);
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
	this->font.loadFromFile("Font/Lobster-Regular.ttf");
	//std::cout << "ERROR::GAME::Failed to load font" << "/n";

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
	//Textbox playernametextbox(100, sf::Color::White, true);
	//playernametextbox.setFont(this->font);
	//playernametextbox.setPosition({ 500.f,320.f });
	//playernametextbox.setlimit(true, 10);

	int j = 0;

	//this->fp = fopen("./score.txt", "r");
	//for (int i = 0; i < 5; i++) {
	//	fscanf(fp, "%s", &temp);
	//	name[i] = temp;
	//	fscanf(fp, "%d", &score[i]);
	//	userScore.push_back(make_pair(score[i], name[i]));
	//}

	sf::Event e;
	while (this->window->isOpen())
	{

		while (this->window->pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window->close();
			case sf::Event::TextEntered:
				if (playername) {
					//playernametextbox.typeOn(e);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					gamestate = 0;
					checkname = false;
				}
			}

		}
		this->window->clear(); //for clear old frame
		this->updateMousePositions();
		if (gamestate == 0) {
			this->menu->update();
			this->menu->draw(*this->window);
			if (checkname && !(playstatus)) {
				this->menu->drawnamespace(*this->window);
				//playernametextbox.drawTo(*this->window);
			}
			if (this->menu->getBounds_0().contains(this->mousePosview)) {
				this->menu->buttoncheck(0);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (playstatus) {
						gamestate = 1;
					}
					checkname = true;
					playername = true;
				}
			}
			else if (this->menu->getBounds_1().contains(this->mousePosview)) {
				this->menu->buttoncheck(1);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					gamestate = 2;
				}
			}
			else if (this->menu->getBounds_2().contains(this->mousePosview)) {
				this->menu->buttoncheck(2);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					gamestate = 3;
				}
			}
			else if (this->menu->getBounds_3().contains(this->mousePosview)) {
				this->menu->buttoncheck(3);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					this->window->close();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && checkname) {
				playstatus = true;
				checkname = false;
				gamestate = 1;
				this->menu->getplay(playstatus);
				//name[5] = playernametextbox.gettext();
			}
		}
		else if (gamestate == 1) {
			if (this->player->getHp() != 0) {
				this->update();
				this->render();
				cangetnewscores = true;
			}
		}
		else if (gamestate == 2) {
			this->menu->drawscore(*this->window);
			if (this->menu->beforegetbounds().contains(this->mousePosview)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->nextpage.getElapsedTime().asSeconds() > 0.25f) {
					this->gamestate = 0;
					this->nextpage.restart();
				}
			}
		}
		else if (gamestate == 3) {
			this->menu->howtoplay(*this->window);
			if (this->menu->nextgetbounds().contains(this->mousePosview)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->nextpage.getElapsedTime().asSeconds() > 0.25f) {
					this->menu->nextpages();
					this->nextpage.restart();
				}
			}
			else if (this->menu->beforegetbounds().contains(this->mousePosview)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->nextpage.getElapsedTime().asSeconds() > 0.25f) {
					if (this->menu->getpages() == 0) {
						this->gamestate = 0;
					}
					this->menu->beforepages();
					this->nextpage.restart();
				}
			}
		}
		this->window->display(); //for update new frame
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosview = this->window->mapPixelToCoords(this->mousePosWindow);
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
		this->ITEM.push_back(new item(2000, rand()%(500-200)+200));
		this->spawntime = 0.f;
	}
	for (int i = 0; i < this->ITEM.size(); ++i) {
		bool item_removed = false;
		this->ITEM[i]->updated();
		if (this->player->getBounds().intersects(this->ITEM[i]->getBounds()))
		{
			this->ITEM.erase(this->ITEM.begin());
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
			this->enemies.push_back(new Enemy(2400.f, 350.f));
		}
		else if (random == 1) {
			this->enemies.push_back(new Enemy(2400.f, 450.f));
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
}