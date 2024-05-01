#include "IOManager.h"

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	//to end
	file.seekg(0, std::ios::end);

	//get file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	
	//Reduce file size by header size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();

	return true;
}