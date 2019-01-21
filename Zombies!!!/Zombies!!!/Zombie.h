#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie {
private:
	//zombie speed for each type of zombie
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float	CRAWLER_SPEED = 20;

	//zombie health
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float	CRAWLER_HEALTH = 3;

	//allow the zombies speed to vary slightly
	const int MAX_VARIANCE = 50;
	const int OFFSET = 126 - MAX_VARIANCE;

	//where is the zombie?
	Vector2f m_Position;
	//zombie sprite
	Sprite m_Sprite;
	//how fast can this zombie move?
	float m_Speed;
	//how much health?
	float m_Health;
	//is this zombie alive?
	bool m_Active;

public:
	//zombie being hit by bullet
	bool hit();
	//is zombie still active?
	bool isActive();
	//spawn a new zombie
	void spawn(float startX, float startY, int type, int seed);
	//return the rectangle that is the zombie position in the world
	FloatRect getPosition();
	//return the sprite
	Sprite getSprite();
	//update the zombie
	void update(float elapsedTime, Vector2f playerLocation);
};