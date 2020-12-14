#include "Game.h"
//start window
void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game", sf::Style::Close |sf::Style::Resize| sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->mainmenu = new Mainmenu(this->window->getSize().x, window->getSize().y);
}

//get new player
void Game::initplayer()
{
	this->player = new Player();
}

void Game::inititem()
{
	this->spawntimeitemMax = 4.f;
	this->spawntimeitem = this->spawntimeitemMax;
}

void Game::initbackground()
{
	this->bg = new background();
}

void Game::initEnemies()
{
	this->spawnTimerEnemiesMax = 50.f;
	this->spawnTimerEnemies = this->spawnTimerEnemiesMax;
}

void Game::initGUI()
{
	//Load font
	this->font.loadFromFile("Font/Lobster-Regular.ttf");
	this->Lamooned.loadFromFile("Font/FC Lamoon Bold Italic ver 1.00.ttf");
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

	this->Kradod.loadFromFile("Sound/Jumping.wav");
	this->KADO.setBuffer(this->Kradod);

	this->ButtonClick.loadFromFile("Sound/Click.wav");
	this->ButtonClicking.setBuffer(this->ButtonClick);

	this->snack.loadFromFile("Sound/Item.wav");
	this->SNACKS.setBuffer(this->snack);

	this->SORE.loadFromFile("Sound/sore.wav");
	this->sores.setBuffer(this->SORE);

	this->die.loadFromFile("Sound/Game Over.wav");
	this->GameOver.setBuffer(this->die);

	musicBG.openFromFile("Sound/Bongo cat.wav");
	musicBG.setVolume(30);
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
	for (auto &i : this-> textures )
	{
		delete i.second;
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
	Textbox playernametextbox(55, sf::Color::Black, true);
	playernametextbox.setFont(this->font);
	playernametextbox.setPosition({ 520.f,350.f });
	playernametextbox.setlimit(true, 10);

	int j = 0;

	this->fp = fopen("./score.txt", "r");
	for (int i = 0; i < 5; i++) {
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
	}


	sf::Event e;
	musicBG.play();
	musicBG.setLoop(true);
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
					playernametextbox.typeOn(e);
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
			this->mainmenu->update();
			this->mainmenu->draw(*this->window);
			if (checkname && !(playstatus)) {
				this->mainmenu->drawnamespace(*this->window);
				playernametextbox.drawTo(*this->window);
			}
			if (this->mainmenu->getBounds_0().contains(this->mousePosview)) {
				this->mainmenu->buttoncheck(0);
				this->ButtonClicking.play();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (playstatus) {
						gamestate = 1;
					}
					checkname = true;
					playername = true;
				}
			}
			else if (this->mainmenu->getBounds_1().contains(this->mousePosview)) {
				this->mainmenu->buttoncheck(1);
				this->ButtonClicking.play();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					gamestate = 2;
				}
			}
			else if (this->mainmenu->getBounds_2().contains(this->mousePosview)) {
				this->mainmenu->buttoncheck(2);
				this->ButtonClicking.play();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					gamestate = 3;
				}
			}
			else if (this->mainmenu->getBounds_3().contains(this->mousePosview)) {
				this->mainmenu->buttoncheck(3);
				this->ButtonClicking.play();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					this->window->close();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && checkname) {
				playstatus = true;
				checkname = false;
				gamestate = 1;
				this->mainmenu->getplay(playstatus);
				name[5] = playernametextbox.gettext();
			}
		}
		else if (gamestate == 1) {
			if (this->player->getHp() != 0) {
				this->update();
				this->render();
				cangetnewscores = true;
			}
			else if (this->player->getHp() == 0 && deadtimes.getElapsedTime().asSeconds() <= 5.f) {
				this->mainmenu->drawdie(*this->window);
			}
			else if (this->player->getHp() == 0 && cangetnewscores && deadtimes.getElapsedTime().asSeconds() > 3.f) {
				this->updateItem();
				this->updateEnemiesandcombat();
				j++;
				point = pointed;
				this->fp = fopen("./score.txt", "r");
				score[5] = point;
				userScore.push_back(make_pair(score[5], name[5]));
				sort(userScore.begin(), userScore.end());
				fclose(fp);
				fopen("./score.txt", "w");
				for (int i = 4 + j; i >= 0 + j; i--) {
					strcpy(temp, userScore[i].second.c_str());
					fprintf(fp, "%s %d\n", temp, userScore[i].first);
				}
				fclose(fp);

				this->player->setHp(100);
				cangetnewscores = false;
				this->gamestate = 0;
				playstatus = false;
				firstendgames = true;
				checkname = false;
				pointed = 0;
			}
		}
		else if (gamestate == 2) {
			this->mainmenu->drawscore(*this->window);
			if (firstendgames == false) {
				showhighscore(950, 258, to_string(userScore[0].first), *this->window, &Lamooned);
				showhighscore(590, 258, userScore[0].second, *this->window, &Lamooned);

				showhighscore(950, 335, to_string(userScore[1].first), *this->window, &Lamooned);
				showhighscore(590, 335, userScore[1].second, *this->window, &Lamooned);

				showhighscore(950, 405, to_string(userScore[2].first), *this->window, &Lamooned);
				showhighscore(590, 405, userScore[2].second, *this->window, &Lamooned);

				showhighscore(950, 474, to_string(userScore[3].first), *this->window, &Lamooned);
				showhighscore(590, 474, userScore[3].second, *this->window, &Lamooned);

				showhighscore(950, 543, to_string(userScore[4].first), *this->window, &Lamooned);
				showhighscore(590, 543, userScore[4].second, *this->window, &Lamooned);
			}
			else if (firstendgames == true) 
			{
				showhighscore(950, 258, to_string(userScore[4+j].first), *this->window, &Lamooned);
				showhighscore(590, 258, userScore[4+j].second, *this->window, &Lamooned);

				showhighscore(950, 335, to_string(userScore[3+j].first), *this->window, &Lamooned);
				showhighscore(590, 335, userScore[3+j].second, *this->window, &Lamooned);

				showhighscore(950, 405, to_string(userScore[2+j].first), *this->window, &Lamooned);
				showhighscore(590, 405, userScore[2+j].second, *this->window, &Lamooned);

				showhighscore(950, 474, to_string(userScore[1+j].first), *this->window, &Lamooned);
				showhighscore(590, 474, userScore[1+j].second, *this->window, &Lamooned);

				showhighscore(950, 543, to_string(userScore[0+j].first), *this->window, &Lamooned);
				showhighscore(590, 543, userScore[0+j].second, *this->window, &Lamooned);
			}
			if (this->mainmenu->beforegetbounds().contains(this->mousePosview)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->nextpage.getElapsedTime().asSeconds() > 0.25f) {
					this->gamestate = 0;
					this->nextpage.restart();
				}
			}
		}
		else if (gamestate == 3) {
			this->mainmenu->howtoplay(*this->window);
			if (this->mainmenu->nextgetbounds().contains(this->mousePosview)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->nextpage.getElapsedTime().asSeconds() > 0.25f) {
					this->mainmenu->nextpages();
					this->nextpage.restart();
				}
			}
			else if (this->mainmenu->beforegetbounds().contains(this->mousePosview)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->nextpage.getElapsedTime().asSeconds() > 0.25f) {
					if (this->mainmenu->getpages() == 0) {
						this->gamestate = 0;
					}
					this->mainmenu->beforepages();
					this->nextpage.restart();
				}
			}
		}
		this->window->display(); //for update new frame
	}
}

void Game::showhighscore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font)
{
	sf::Text text;
	text.setFillColor(sf::Color::Black);
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(60);
	window.draw(text);
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
	this->spawntimeitem += 0.1f;
	if (this->pushbackitem.getElapsedTime().asSeconds() >= 20.f) {
		this->spawntimeitemMax -= 0.4f;
		this->pushbackitem.restart();
	}
	if (this->spawntimeitem >= this->spawntimeitemMax)
	{
		if (this->bloodcount >= 20) {
			this->ITEM.push_back(new item(2000, rand() % (500 - 175) + 175, 1));
			this->spawntimeitem = 0.f;
			this->bloodcount -= 20;
		}
		else {
			this->ITEM.push_back(new item(2000, rand() % (500 - 175) + 175, 0));
			this->spawntimeitem = 0.f;
		}
	}
	if (this->speeditemincrease.getElapsedTime().asSeconds() >= 10.f) {
		this->speeditem += 1.f;
		this->speeditemincrease.restart();
	}
	for (int i = 0; i < this->ITEM.size(); ++i) {
		bool item_removed = false;
		this->ITEM[i]->updated(speeditem); 
		if (this->player->getBounds().intersects(this->ITEM[i]->getBounds())&&this->ITEM[i]->gettype()==0)
		{
			this->SNACKS.play();
			this->ITEM.erase(this->ITEM.begin() + i);
			this->pointed += 3;
			item_removed = true;
			this->bloodcount++;
		}
		if (this->player->getBounds().intersects(this->ITEM[i]->getBounds()) && this->ITEM[i]->gettype() == 1)
		{
			this->ITEM.erase(this->ITEM.begin() + i);
			this->player->permHp(20);
			item_removed = true;
		}
		if (this->ITEM[i]->getBounds().left + ITEM[i]->getBounds().width < 0.f) {
			this->ITEM.erase(this->ITEM.begin() + i);
			item_removed = true;
		}
		if (this->player->getHp() == 0) {
			if (ITEM.size() == 1) {
				this->ITEM.erase(this->ITEM.begin());
				std::cout << "delete" << endl;
			}
			else {
				if (i == 0) {
					this->ITEM.erase(this->ITEM.begin());
				}
				this->ITEM.erase(this->ITEM.begin() + i);
			}
			this->pushbackitem.restart();
			this->spawntimeitemMax = 4.f;
			this->speeditem = 0.f;
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

	this->updateItem();
	
	this->updateCollision();
	
	this->updateEnemiesandcombat();

	this->updateGUI();

}


void Game::updateEnemiesandcombat()
{
	this->spawnTimerEnemies += 0.5f;
	if (this->pushbackenemy.getElapsedTime().asSeconds() >= 20.f) {
		this->spawnTimerEnemiesMax -= 5.f;
		this->pushbackenemy.restart();
	}
	if (this->spawnTimerEnemies >= this->spawnTimerEnemiesMax)
	{
		int random = rand() % 2;
		if (random == 0) {
			this->enemies.push_back(new Enemy(2400.f, 420.f));
		}
		else if (random == 1) {
			this->enemies.push_back(new Enemy(2400.f, 300.f));
		}
		this->spawnTimerEnemies = 0.f;
	}

	for (int i =0; i <this->enemies.size();++i)
	{
		bool enemy_removed = false;
		if (this->speedincrease.getElapsedTime().asSeconds() >= 10.f) {
			this->plusSpeed += 1.f;
			this->speedincrease.restart();
		}
		this->enemies[i]->update(plusSpeed);
		//Remove enemies at the bottom of the screen
		if (this->enemies[i]->getBounds().left +this->enemies[i]->getBounds().width< 0.f )
		{
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;
		}
		if (this->player->getBounds().intersects(this->enemies[i]->getBounds()))
		{
			this->sores.play();
			this->player->loseHp(10);
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;
		}
		if (this->player->getHp() == 0) {
			if (enemies.size() == 1) {
				this->enemies.erase(this->enemies.begin());
				std::cout << "delete" << endl;
			}
			else {
				if (i == 0) {
					this->enemies.erase(this->enemies.begin());
				}
				this->enemies.erase(this->enemies.begin() + i);
			}
			this->pushbackenemy.restart();
			this->spawnTimerEnemiesMax = 50.f;
			this->plusSpeed = 0.f;
			this->player->setPosition(100, 300);
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

	if (this->player->getHp() == 0) {
		this->deadtimes.restart();
	}

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