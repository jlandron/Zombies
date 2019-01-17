#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{
	//The game will only be in one of four states as declared in this enumeration
	enum class State {
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING;
	};
	//Start game in GAME_OVER State
	State state = STATE::GAME_OVER;

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), 
		"Zombie Arena", Style::Fullscreen);
	return 0;
}
