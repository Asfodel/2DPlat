#ifndef TEXTURECACHE_HJ
#define TEXTURECACHE_H

#include <map>
#include <string>
#include <iostream>

#include "Texture.h"
#include "ImageLoader.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	Texture getTexture(std::string texturePath);

private:
	std::map<std::string, Texture> m_textureMap;
};

#endif  //TEXTURECACHE_H