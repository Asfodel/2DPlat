#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "Texture.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

#include <string>

class ImageLoader
{
public:
	static Texture loadPNG(const std::string& filePath);
};

#endif  //IMAGELOADER_H