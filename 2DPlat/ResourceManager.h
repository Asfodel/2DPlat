#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>

#include "TextureCache.h"

class ResourceManager
{
public:
	static Texture getTexture(std::string texturePath);

private:
	static TextureCache m_textureCache;
};

#endif  //RESOURCEMANAGER_H