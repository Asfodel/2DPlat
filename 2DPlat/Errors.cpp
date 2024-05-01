#include "Errors.h"

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit..." << std::endl;
	int temp;
	std::cin >> temp;
	SDL_Quit();
	exit(11);
}