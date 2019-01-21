#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

//singleton class to hold zombie texture
class TextureHolder {
private:
	//An STL map that holder string,Texture pairs
	std::map<std::string, Texture> m_Textures;

	//Pointer of the same type as the class so that only one instance
	//of the class exists
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static Texture& GetTexture(std::string const&);
};