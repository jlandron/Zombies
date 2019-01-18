#include "pch.h"
#include "Arena.h"
#include "SFML/Graphics.hpp"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena) {
	//Everything done here to rVA is done directly to the VA object
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;
	//what type of SFML primitive are we using?
	rVA.setPrimitiveType(Quads);
	//set the size fo the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
	//start at the beggining of the vertexArray
	int currentVertex = 0;
	for (int w = 0; w < worldWidth; w++) {
		for (int h = 0; h < worldHeight; h++) {
			//Position each vertex in the current quad
			rVA[currentVertex].position = 
				Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = 
				Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE));
			rVA[currentVertex + 2].position = 
				Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = 
				Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			//Define the position in the Texture for the current quad
			//either grass, stone, bush, or wall
			if (h == 0 || h == worldHeight - 1 ||
				w == 0 || w == worldWidth - 1) {
				//use the wall texture to make the edges
				rVA[currentVertex].texCoords =
					Vector2f(0, TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
			}
			else {
				//select and use a random tile texture
				srand((int)time(0) + h * w - h);
				int tileChoice = (rand() % TILE_TYPES);
				int verticalOffset = tileChoice * TILE_SIZE;

				rVA[currentVertex].texCoords =
					Vector2f(0, verticalOffset);
				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, verticalOffset);
				rVA[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE + verticalOffset);
			}
			//Position ready for the next vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}