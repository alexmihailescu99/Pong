#include "Loader.h"
Loader* Loader::instance = nullptr;

Loader* Loader::getInstance() {
	if (instance == nullptr) {
		instance = new Loader();
	}
	return instance;
}

Loader::~Loader() {
	if (instance) {
		delete this->instance;
	}
}

SDL_Surface* Loader::loadImage(std::string imagePath, std::string imageFormat) {
	SDL_Surface* imageSurface = nullptr;
	if (imageFormat == "BMP") {
		imageSurface = SDL_LoadBMP(imagePath.c_str());
	}
	if (imageFormat == "PNG" || imageFormat == "JPG") {
		imageSurface = IMG_Load(imagePath.c_str());
	}
	if (imageSurface != nullptr) {
		return imageSurface;
	}
	else {
		std::cerr << "Could not load image from " << imagePath << std::endl;
		return nullptr;
	}
}

SDL_Texture* Loader::loadTexture(std::string texturePath, std::string textureFormat) {
	SDL_Surface* textureSurface = nullptr;
	SDL_Texture* texture = nullptr;
	if (textureFormat == "BMP") {
		textureSurface = this->loadImage(texturePath, "BMP");
		if (textureSurface == nullptr) {
			std::cerr << "Could not load image texture from " << texturePath << std::endl;
			return nullptr;
		}
	}
	if (textureFormat == "PNG") {
		textureSurface = this->loadImage(texturePath, "PNG");
		if (textureSurface == nullptr) {
			std::cerr << "Could not load image texture from " << texturePath << std::endl;
			return nullptr;
		}
	}
	if (textureFormat == "JPG") {
		textureSurface = this->loadImage(texturePath, "JPG");
		if (textureSurface == nullptr) {
			std::cerr << "Could not load image texture from " << texturePath << std::endl;
			return nullptr;
		}
	}
	texture = SDL_CreateTextureFromSurface(Window::getInstance()->getRenderer(), textureSurface);
	if (texture == nullptr) {
		std::cout << "TEXTURE NULLPTR\n";
	}
	SDL_FreeSurface(textureSurface);
	return texture;
}
