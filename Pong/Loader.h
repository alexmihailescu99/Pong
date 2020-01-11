#ifndef LOADER_H_
#define LOADER_H_
#include <iostream>
#include "Window.h"
#include <SDL.h>
#include <SDL_image.h>
class Loader {
private:
	static Loader* instance;
	Loader() {};
	~Loader();
public:
	static Loader* getInstance();
	SDL_Surface* loadImage(std::string imagePath, std::string imageFormat);
	SDL_Texture* loadTexture(std::string texturePath, std::string textureFormat);
};

#endif // LOADER_H_

