#include "TextureCache.h"

TextureCache::TextureCache()
{}

TextureCache::~TextureCache()
{}

Texture TextureCache::getTexture(std::string texturePath)
{
	std::map<std::string, Texture>::iterator mit = m_textureMap.find(texturePath);

	if (mit == m_textureMap.end())
	{
		Texture newTexture = ImageLoader::loadPNG(texturePath);

		std::pair<std::string, Texture> newPair(texturePath, newTexture);
		m_textureMap.insert(newPair);
		std::cout << "New Texture" << std::endl;
		return newTexture;
	}
	std::cout << "Old texture" << std::endl;
	return mit->second;
}