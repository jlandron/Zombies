#include "pch.h"
#include "Player.h"

using namespace sf;

Player::Player() {
	//start the player with default values
	m_Health = START_HEALTH;
	m_Speed = START_SPEED;
	m_MaxHealth = START_HEALTH;
	//load the needed texture
	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);
	//set the center of the sprite based on the image
	m_Sprite.setOrigin(25, 25);
}
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize) {
	//Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	//copy the details o fthe arena to the Player
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	//store how big a tile is for the arena
	m_TileSize = tileSize;

	//store the resolution
	m_Resolution.x = resolution.x;
	m_Resilution.y = resolution.y;
}
//player need to be reset
void Player::resetPlayerStats() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}
Time Player::getLastHit() {
	return m_LastHit;
}
bool Player::hit(Time timeHit) {
	//player can only be hit 5 times a second
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else {
		return false;
	}
}
FloatRect Player::getPosition() {
	return m_Sprite.getGlobalBounds();
}
Vector2f Player::getCeter() {
	return m_Position;
}
float Player::getRotation() {
	return m_Sprite.getRotation();
}
Sprite Player::getSprite() {
	return m_Sprite;
}
void Player::getHealth() {
	return m_Health;
}
//-----------Begin player movment-------------
void Player::moveUp() {
	m_UpPressed = true;
}
void Player::moveDown() {
	m_DownPressed = true;
}
void Player::moveRight() {
	m_RightPressed = true;
}
void Player::moveLeft() {
	m_LeftPressed = true;
}

void Player::stopUp() {
	m_UpPressed = false;
}
void Player::stopDown() {
	m_DownPressed = false;
}
void Player::stopRight() {
	m_RightPressed = false;
}
void Player::stopLeft() {
	m_LeftPressed = false;
}
//--------------End playe movment------------
/*
this fucntion will be called many times per second, 
*/
void Player::update(float elapsedTime, Vector2i mousePosition) {\
	if (m_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}
	if (m_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}
	if (m_RIghtPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position);

	//code to keep the player sprite in the boundry of the arena
	if (m_Position > m_Arena.width - m_TileSize) {
		m_Position.x = m_Arena.width - m_TileSize;
	}
	if (m_Position < m_Arena.left + m_TileSize) {
		m_Position.x = m_Arena.left + m_TileSize;
	}
	if (m_Position > m_Arena.height - m_TileSize) {
		m_Position.x = m_Arena.height - m_TileSize;
	}
	if (m_Position < m_Arena.top + m_TileSize) {
		m_Position.x = m_Arena.top + m_TileSize;
	}
	//calculate the angle using trig
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, 
					mousePosition.x - m_Resolution.x / 2) 
					* 180) / 3.141;
}
void Player::upgradeSpeed() {
	m_Speed += (START_HEALTH * 0.2);
}
void Player::upgradeHealth() {
	m_MaxHealth += (START_HEALTH * 0.2);
}
void Player::increaseHealthLevel(int amount) {

	m_Health += amount;
	//check if health goes to high
	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
}

