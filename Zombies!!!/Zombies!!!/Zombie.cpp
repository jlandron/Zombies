#include "pch.h"
#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

bool Zombie::hit(){
	m_Health--;
	//check is zombie was killed
	if (m_Health <= 0) {
		//zombie is dead
		m_Active = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));

		return true;
	}
	//zombie was injured by not dead
	return false;
}
bool Zombie::isActive(){
	return m_Active;
}
void Zombie::spawn(float startX, float startY, int type, int seed){
	//switch to create the zombie type, parameters of zombie can be edited in Zombie.h
	switch (type){
	case 0: //blaoter
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;
	case 1:
		//chaser
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;
	case 2:
		//crawler
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	default:
		break;
	}
	//make each zombie unique
	srand((int)time(0) * seed);
	//I want a number that is reasonable, constants can be changed in Zombie.h
	float modifier = (rand() % MAX_VARIANCE) + OFFSET;

	//express modifier as a fraction of 1
	modifier /= 100;
	m_Speed *= modifier;
	//initialize zombie location
	m_Position.x = startX;
	m_Position.y = startY;

	//set the origin of the sprite to the center of the texture(50x50 px)
	m_Sprite.setOrigin(25, 25);
	//set its position
	m_Sprite.setPosition(m_Position);
}
FloatRect Zombie::getPosition(){
	return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite(){
	return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation){
	//the zombie needs to know where the player is
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	//update the zombie position variables
	if (playerX > m_Position.x) {
		m_Position.x = m_Position.x + m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y) {
		m_Position.y = m_Position.y + m_Speed * elapsedTime;
	}
	if (playerX < m_Position.x) {
		m_Position.x = m_Position.x - m_Speed * elapsedTime;
	}
	if (playerY < m_Position.y) {
		m_Position.y = m_Position.y - m_Speed * elapsedTime;
	}
	//move the sprite
	m_Sprite.setPosition(m_Position);

	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;
	m_Sprite.setRotation(angle);
}
