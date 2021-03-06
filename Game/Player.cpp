#include "Player.h"
//for variables
void Player::initVariables()
{
	
	this->animState = PlAYER_ANIMATION_STATES::IDLE;
	this->movementSpeed = 2.f;
	this->attackcooldownMax = 30.f;
	this->attackcooldown = this->attackcooldownMax;

	//player hp
	this->hpMax = 100;
	this->hp = this->hpMax;
}

//include picture from files
void Player::initTexture()
{
	this->playertexture.loadFromFile("Cat/Cat_Game.png");
}

//settings sprites of player
void Player::initSprite()
{
	this->playersprite.setTexture(this->playertexture);
	this->currentFrame = sf::IntRect(0, 0, 620, 800);
	this->playersprite.setTextureRect(sf::IntRect(this->currentFrame));
	this->playersprite.setScale(0.3f, 0.3f);
	this->playerposition = sf::Vector2f(100, 300);
	this->playersprite.setPosition(sf::Vector2f(this->playerposition));
	this->rectangle.setSize(sf::Vector2f(60.f, 100.f));
	this->rectangle.setFillColor(sf::Color::Transparent);
	this->rectangle.setPosition(this->playerposition.x+80,this->playerposition.y+70);
	this->rectangle.setOutlineThickness(-1.f);
	this->rectangle.setOutlineColor(sf::Color::Transparent);
}

//settings animation timer 
void Player::initAnimations()
{
	this->animatetimer.restart();
	this->animationSwitc = true;

}

void Player::initPhysics()
{
	this->drag = 0.9f;
	this->gravity = 0.6f;
}

//all funtion about player
Player::Player()
{

	//variables
	this->initVariables();

	this->initVariables();
	//player sprite and texture
	this->initTexture();
	this->initSprite();

	//player animations
	this->initAnimations();

	//player physics
	this->initPhysics();

	this->Kradod.loadFromFile("Sound/Jumping.wav");
	this->KADO.setBuffer(this->Kradod);
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	// TODO: insert return statement here
	bool anim_switch = this->animationSwitc;
	if (this->animationSwitc)
		this->animationSwitc = false;

	return anim_switch;
}

const sf::FloatRect Player::getBounds() const
{
	return this->rectangle.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->playersprite.setPosition(x, y);
	if (setbig == false) {
		this->rectangle.setPosition(x + 80, y + 70);
	}
	else if (setbig == true) {
		this->rectangle.setPosition(x + 160, y + 140);
	}
	this->playerposition.x = x;
	this->playerposition.y = y;
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}

const sf::Vector2f& Player::getpos() const
{
	return this->playersprite.getPosition();
}

void Player::resetAnimationTimer()
{
	this->animatetimer.restart();
	this->animationSwitc = true;
}

void Player::updatePhysics()
{
	if (this->jumping == true && this->gravityBool == false)
	{
		if (this->velocity.y < 0)
			this->jumpingUp = false;
		if (this->jumpingUp == true)
			this->velocity.y -= 1.f;
		else
		{
			//gravity
			this->velocity.y += (1.0 * this->gravity);
			if (std::abs(this->velocity.x) > this->velocityMaxY)
				this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
		}
	}
	else
		this->velocity.y += (1.0 * this->gravity);	//gravity

	if (this->gravityBool == true)
		this->velocity.y += (1.0 * this->gravity);

	//decceleration
	this->velocity *= (this->drag);

	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
	}

	this->playersprite.move(this->velocity);
	this->playerposition.x += velocity.x;
	this->playerposition.y += velocity.y;
	if (this->setbig == false) {
		this->rectangle.setPosition(this->playerposition.x + 80, this->playerposition.y + 70);
	}
	else if(this->setbig == true) {
		this->rectangle.setPosition(this->playerposition.x + 160, this->playerposition.y + 140);
	}
}

//get HP of player
const int& Player::getHp() const
{
	return this->hp;
}

//get HPMax of player
const int& Player::getHpMax() const
{
	return this->hpMax;
}

//setting player HP
void Player::setHp(const int hp)
{
	this->hp = hp;
}

//lose Hp function
void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::permHp(const int value)
{
	this->hp += value;
	if (this->hp > 100)
		this->hp = 100;
}

//Movement functions
void Player::updatemovement()
{
	this->animState = PlAYER_ANIMATION_STATES::IDLE; //not walk
	this->rectangle.setSize(sf::Vector2f(60.f, 100.f));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&jumping==false)
	{
		this->gravityBool = true;
		this->animState = PlAYER_ANIMATION_STATES::MOVING_DOWN; //go down
		this->rectangle.setSize(sf::Vector2f(100.f, 50.f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->jumping == false)
	{
		this->KADO.play();
		this->jumping = true;
		this->jumpingUp = true;
		this->gravityBool = true;
		this->velocity.y = -50.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&this->playerposition.x<=1100.f) {
		this->playersprite.move(5.f, 0.f);
		this->rectangle.move(5.f, 0.f);
		this->playerposition.x += 5.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left ) && this->playerposition.x > 0.f) {
		this->playersprite.move(-5.f, 0.f);
		this->rectangle.move(-5.f, 0.f);
		this->playerposition.x -= 5.f;
	}
}


//function for play next sprite
void Player::updateAnimations()
{
	if (this->animState == PlAYER_ANIMATION_STATES::IDLE) {
		if (this->animatetimer.getElapsedTime().asSeconds() >= 0.1f||this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 620.f;
			if (this->currentFrame.left >= 1860.f) {
				this->currentFrame.left = 0;
			}
			this->animatetimer.restart();
			this->playersprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PlAYER_ANIMATION_STATES::MOVING_DOWN) {
		if (this->animatetimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 800.f;
			this->currentFrame.left += 620.f;
			if (this->currentFrame.left >= 1860.f) {
				this->currentFrame.left = 0;
			}
			this->animatetimer.restart();
			this->playersprite.setTextureRect(this->currentFrame);
		}
	}
	
	else if (this->animState == PlAYER_ANIMATION_STATES::MOVING_TOP) {
		if (this->animatetimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 1600.f;
			this->currentFrame.left += 620.f;
			if (this->currentFrame.left >= 1860.f) {
				this->currentFrame.left = 0;
			}
			this->animatetimer.restart();
			this->playersprite.setTextureRect(this->currentFrame);
		}
	}
}


const bool Player::canAttack()
{
	if (this->attackcooldown >= this->attackcooldownMax)
	{
		this->attackcooldown = 0.f;
		return true;
	}
	return false;
}

void Player::getsize(float x, float y)
{
	this->playersprite.setScale(x, y);
	if (x == 0.6f && y == 0.6f) {
		this->rectangle.setScale(2.f, 2.f);
		this->setbig = true;
	}
	else if (x == 0.3f && y == 0.3f) {
		this->rectangle.setScale(1.f, 1.f);
		this->setbig = false;
	}
}

void Player::updateAttack()
{
	if (this->attackcooldown < this->attackcooldownMax)
		this->attackcooldown += 0.5f;
}

//player update
void Player::updated()
{
	this->updatemovement();
	this->updateAnimations();
	this->updatePhysics();
	this->updateAttack();
}

//player render
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->rectangle);
	target.draw(this->playersprite);
}