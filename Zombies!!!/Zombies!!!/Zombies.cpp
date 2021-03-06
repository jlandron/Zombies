#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Zombies.h"
#include "TextureHolder.h"

using namespace sf;

int main() {
	TextureHolder holder;

	//initial game setup
	//The game will only be in one of four states as declared in this enumeration
	enum class State {
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};
	//Start game in GAME_OVER State
	State state = State::GAME_OVER;

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);
	//setting the frame limit doe snot reduce the frame drops on keyboard input. 
	//moving the mouse continuousl does???
	//-----------------------investiage more-------------------------------------
	//window.setFramerateLimit(30);

	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	Clock clock;
	Time gameTimeTotal;
	//where is the mouse in relation to the world
	Vector2f mouseWorldPosition;
	//where is the mouse in realtion to the screen
	Vector2i mouseScreenPosition;

	Player player;

	IntRect arena;

	//Create the Background
	VertexArray background;
	//Load the texture for the background tiles
	Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

	int numZombies;
	int numZombiesActive;
	Zombie* zombies = nullptr;

	//main game loop
	while(window.isOpen()){
		//Event Handling
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				//pause the game with enter
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING) {
					state = State::PAUSED;
				}
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED) {
					state = State::PLAYING;
					//restart clock to keep frames from jumping
					clock.restart();
				}
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER) {
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING) {

				}
			}
			//end of event polling for gameplay

			//Handle player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}

			//handle controls for WASD
			if (state == State::PLAYING) {
				if (Keyboard::isKeyPressed(Keyboard::W)) {
					player.moveUp();
				}
				else {
					player.stopUp();
				}
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					player.moveDown();
				}
				else {
					player.stopDown();
				}
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					player.moveLeft();
				}
				else {
					player.stopLeft();
				}
				if (Keyboard::isKeyPressed(Keyboard::D)) {
					player.moveRight();
				}
				else {
					player.stopRight();
				}
			}//end controls for WASD

			//handle the levelling up
			if (state == State::LEVELING_UP) {
				if (event.key.code == Keyboard::Num1) {
					state = State::PLAYING;
				}
				if (event.key.code == Keyboard::Num2) {
					state = State::PLAYING;
				}
				if (event.key.code == Keyboard::Num3) {
					state = State::PLAYING;
				}
				if (event.key.code == Keyboard::Num4) {
					state = State::PLAYING;
				}
				if (event.key.code == Keyboard::Num5) {
					state = State::PLAYING;
				}
				if (event.key.code == Keyboard::Num6) {
					state = State::PLAYING;
				}
				//once a option is selected, state will change to playing
				if (state == State::PLAYING) {
					//prepare the level
					arena.width = 5000;
					arena.height = 5000;
					arena.left - 0;
					arena.top = 0;

					//set tilesize pass the vertex array by reference
					//to the createBackground function
					int tileSize = createBackground(background, arena);

					//spawn the player
					player.spawn(arena, resolution, tileSize);

					//create a horde of zombies
					numZombies = 500;
					//delete old array of zombies to avoid crashing game with heap overflow
					delete[] zombies;
					zombies = createHorde(numZombies, arena);
					numZombiesActive = numZombies;
					//reset the clock
					clock.restart();
				}
			}//end of leveling up

			//updating the frame
			if (state == State::PLAYING) {
				//update the time change
				Time dt = clock.restart();
				//update the total game time
				gameTimeTotal += dt;
				//Make a decimal fraction of 1 from dt
				float dtAsSeconds = dt.asSeconds();

				//Where is the mouse pointer
				mouseScreenPosition = Mouse::getPosition();

				//Convert the mouse position to world coordinates of MainView
				mouseWorldPosition = window.mapPixelToCoords(
					Mouse::getPosition(), mainView);
				//update the player object
				player.update(dtAsSeconds, Mouse::getPosition());

				//Make note of players new Position
				Vector2f playerPosition(player.getCenter());

				//Update the view to center on the player
				mainView.setCenter(player.getCenter());

				//loop through each zombie in the array and update them
				for (int i = 0; i < numZombies; i++) {
					if (zombies[i].isActive()) {
						zombies[i].update(dt.asSeconds(), playerPosition);
					}
				}
			}//end of frame updating

			//draw the scene
			if (state == State::PLAYING) {
				window.clear();
				//set the mainView to be displayed in the window
				//and draw everything related to it
				window.setView(mainView);
				//draw the background
				window.draw(background, &textureBackground);
				//draw all zombies
				for (int i = 0; i < numZombies; i++) {
					window.draw(zombies[i].getSprite());
				}
				//draw the player
				window.draw(player.getSprite());
			}
			if (state == State::LEVELING_UP) {

			}
			if (state == State::PAUSED) {

			}
			if (state == State::GAME_OVER) {

			}
			window.display();
			
		}
	}//end of game loop
	//delete the previous allocated memory
	delete[] zombies;
	return 0;
}
