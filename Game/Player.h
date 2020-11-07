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
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();


	void resetAnimationTimer();
	void move(const float dir_x,const float dir_y);
	void updatePhysics();
	
	//Movement Update
	void updatemovement();
	void updateAnimations();

	bool jumping = false;
	bool jumpingUp = false;
	bool gravityBool = false;


	//Player update and render
	void updated();
	void render(sf::RenderTarget& target);
};
