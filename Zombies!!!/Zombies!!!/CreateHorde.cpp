#include "pch.h"
#include "Zombies.h"
#include "Zombie.h"

Zombie* createHorde(int numZombies, IntRect arena){
	Zombie* zombies = new Zombie[numZombies];

	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numZombies; i++) {
		//random zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side) {
		case 0:
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1:
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2:
			x = (rand() % maxX) + minX;
			y = minY;
			break;
		case 3:
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}
		//random number to generate the type of zombie
		//--------------change this as more zombie types are added-------------
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);
		zombies[i].spawn(x, y, type, i);

	}
	//return the array of zombies
	return zombies;
}