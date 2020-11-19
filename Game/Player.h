#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include <iostream>
enum PlAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_TOP, MOVING_DOWN }; //for check player direction 
class Player
{
private:
	//Sprite and Textures player
	sf::Sprite playersprite;
	sf::Texture playertexture;
	sf::RectangleShape rectangle;
	
	float movementSpeed;

	float attackcooldown;
	float attackcooldownMax;

	//Animation 
	sf::Clock animatetimer; //to set animation time 
	short animState;
	sf::IntRect currentFrame; //for show next sprite
	sf::Vector2f playerposition;
	bool animationSwitc;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//hp variables
	int hp;
	int hpMax;



	//Function
	void initVariables();
	
	//player texture and sprite function
	void initTexture();
	void initSprite();

	//player animation function
	void initAnimations();
	void initPhysics();

public:
	//Player
	Player();
	virtual ~Player();

	//Accessore
	const bool& getAnimSwitch();

	const sf::FloatRect getBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	//accessor
	const sf::Vector2f& getpos() const;

	void resetAnimationTimer();
	void updatePhysics();

	//Hp functions
	const int& getHp() const;
	const int& getHpMax() const;

	void setHp(const int hp);
	void loseHp(const int value);
	
	//Movement Update
	void updatemovement();
	void updateAnimations();

	bool jumping = false;
	bool jumpingUp = false;
	bool gravityBool = false;
	const bool canAttack();

	//Player update and render
	void updateAttack();
	void updated();
	void render(sf::RenderTarget& target);
};
