#include "pch.h"
#include "TextureHolder.h"
//Assert feature is needed
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}
Texture & TextureHolder::GetTexture(std::string const & filename){
	//get a reference to m_Textures using m_s_Instance
	//auto is taking the place of the map<>
	auto& m = m_s_Instance->m_Textures;
	//create the iterator again using auto
	auto keyValuePair = m.find(filename);

	//if match was found
	if (keyValuePair != m.end()) {
		//return the texture
		return keyValuePair->second;
	}
	else {
		//load the texture and return it
		auto& texture = m[filename];
		//load texture from passed file
		texture.loadFromFile(filename);

		return texture;
	}
}