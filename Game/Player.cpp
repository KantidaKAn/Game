#include "Player.h"
//for variables
void Player::initVariables()
{
	this->animState = PlAYER_ANIMATION_STATES::IDLE;
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
	this->playersprite.setScale(0.2f, 0.2f);
	this->playerposition = sf::Vector2f(12, 13);
	this->playersprite.setPosition(sf::Vector2f(this->playerposition));
}

//settings animation timer 
void Player::initAnimations()
{
	this->animatetimer.restart();
	this->animationSwitc = true;

}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.9f;
	this->gravity = 0.6f;
	this->velocityMaxY = 1.f;
}

//all funtion about player
Player::Player()
{

	//variables
	this->initVariables();


	//player sprite and texture
	this->initTexture();
	this->initSprite();

	//player animations
	this->initAnimations();

	//player physics
	this->initPhysics();
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

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->playersprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const
{
	return this->playersprite.getPosition();
}

void Player::setPosition(const float x, const float y)
{
	this->playersprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animatetimer.restart();
	this->animationSwitc = true;
}

void Player::move(const float dir_x,const float dir_y)
{
	this->playersprite.move(dir_x,dir_y);

	//acceleration
	this->velocity.x += dir_x * this->acceleration;
	//this->velocity.y += dirY * this->accelerationJump;

	//limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
	/*if (std::abs(this->velocity.y) > this->velocityMax)
	{
		this->velocity.y = this->velocityMax * ((this->velocity.y < 0.f) ? -1.f : 1.f);
		printf("%f", this->velocity.y);
	}*/
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

	//limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
	}

	this->playersprite.move(this->velocity);
}

//Movement functions
void Player::updatemovement()
{
	this->animState = PlAYER_ANIMATION_STATES::IDLE; //not walk
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->gravityBool = true;
		this->animState = PlAYER_ANIMATION_STATES::MOVING_DOWN; //go down
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->jumping == false)
	{
		this->jumping = true;
		this->jumpingUp = true;
		this->gravityBool = true;
		this->velocity.y = -30.f;
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


//player update
void Player::updated()
{
	this->updatemovement();
	this->updateAnimations();
	this->updatePhysics();
}

//player render
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playersprite);
}