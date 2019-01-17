#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	Vector2f m_Position;

	Sprite m_Sprite;

	Texture m_Texture;

	Vector2f m_Resolution;

	IntRect m_Arena;

	int m_TileSize;

	bool m_UpPressed;
	bool m_DownPressed;
	bool m_RightPressed;
	bool m_LeftPressed;

	int m_Health;

	int m_MaxHealth;

	Time m_LastHit;

	float m_Speed;
public:
	//constructor
	Player();
	//spawn a new player
	void spawn(IntRect arena, Vector2f resolution, int tileSize);
	//reset player stats to base values
	void resetPlayerStats();
	//check and store hit
	Time getLastHit();
	bool hit(Time timeHit);

	//getters
	FloatRect getPosition();
	Vector2f getCeter();

	float getRotation();

	Sprite getSprite();
	//movement
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	void stopUp();
	void stopDown();
	void stopRight();
	void stopLeft();
	//update function that is repeatedly called
	void update(float elapsedTime, Vector2i mousePosition);
	//upgrades/in-game pickups
	void upgradeSpeed();

	void upgradeHealth();

	void increaseHealthLevel(int);

	void getHealth();

};

