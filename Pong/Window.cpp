#include "Window.h"

Window* Window::instance = nullptr;

Window::Window() {

}

Window::~Window() {
	SDL_DestroyWindow(this->window);
}



Window* Window::getInstance() {
	if (instance == nullptr) {
		instance = new Window();
	}
	return instance;
}

void Window::setWindowTitle(std::string title) {
	this->title = title;
}

std::string Window::getWindowTitle() {
	return this->title;
}

void Window::setWindowXPos(int xPos) {
	this->xPos = xPos;
}

void Window::setWindowYPos(int yPos) {
	this->yPos = yPos;
}

void Window::setWindowHeight(uint height) {
	this->height = height;
}

void Window::setWindowWidth(uint width) {
	this->width = width;
}

void Window::setWindowFlag(SDL_WindowFlags flag) {
	this->flag = flag;
}

SDL_Window* Window::getWindow() {
	return this->window;
}

bool Window::createWindow() {
	// If not all fields are set, window cannot be created
	if (title.empty()
		|| xPos == -1
		|| yPos == -1
		|| width == -1
		|| height == -1) {
		std::cerr << "Could not create window : not all parameters are set!\n";
		return false;
	}
	this->window = SDL_CreateWindow(this->title.c_str(), this->xPos, this->yPos,
		this->width, this->height, this->flag);
	// If, for some reason, window was not created
	if (!this->window) {
		std::cerr << "SDL window could not be created! (SDL Error)\n";
		return false;
	}
	// If, for some reason, surface was not retrieved
	this->surface = SDL_GetWindowSurface(this->window);
	if (!this->surface) {
		std::cerr << "SDL surface could not be created! (SDL Error)\n";
		return false;
	}
}

void Window::drawColor(uint r, uint g, uint b) {
	// If the window onto which we'll draw does not exist, create it
	if (window == nullptr) {
		if (!(this->createWindow())) {
			return;
		}
	}
	// If the surface of the window exists, draw on it
	if (surface) {
		SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, r, g, b));
		SDL_UpdateWindowSurface(this->window);
	}
	else {
		std::cerr << "Could not draw : SDL_Surface does not exist!\n";
	}
}

bool Window::loadImage(std::string imagePath, std::string imageFormat) {
	SDL_Surface* imageSurface = nullptr;
	if (imageFormat == "BMP") {
		imageSurface = SDL_LoadBMP(imagePath.c_str());
	}
	if (imageFormat == "PNG" || imageFormat == "JPG") {
		imageSurface = IMG_Load(imagePath.c_str());
	}
	if (imageSurface != nullptr) {
		this->currImgSurface = imageSurface;
		this->currImgPath = imagePath;
		return true;
	}
	else {
		std::cerr << "Could not load image from " << imagePath << std::endl;
		return false;
	}
}

void Window::drawImage(std::string imagePath, std::string imageFormat) {
	if (window == nullptr) {
		if (!(this->createWindow())) {
			return;
		}
	}
	// Only load the image if the currImgSurface field is empty or the image is different from what we already have
	if (this->currImgSurface == nullptr
		|| imagePath != this->currImgPath) {
		if (imageFormat == "BMP") {
			if (!this->loadImage(imagePath, "BMP")) {
				return;
			}
		}
		if (imageFormat == "PNG") {
			if (!this->loadImage(imagePath, "PNG")) {
				return;
			}
		}
		if (imageFormat == "JPG") {
			if (!this->loadImage(imagePath, "JPG")) {
				return;
			}
		}
		this->stretching = false;
	}
	// If the image is smaller than the screen, scale it
	if (this->currImgSurface->w != this->surface->w
		|| this->currImgSurface->h != this->surface->h) {
		this->stretching = true;
		SDL_Surface* scaledImgSurface = SDL_ConvertSurface(this->currImgSurface,
			this->surface->format, 0);
		SDL_FreeSurface(this->currImgSurface);
		this->currImgSurface = scaledImgSurface;
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = this->width;
		stretchRect.h = this->height;
		SDL_BlitScaled(this->currImgSurface, NULL, this->surface, &stretchRect);
	}
	if (!stretching) {
		if (imageFormat == "PNG") {
			SDL_ConvertSurface(this->currImgSurface, this->surface->format, 0);
		}
		SDL_BlitSurface(this->currImgSurface, NULL, this->surface, NULL);
	}
	SDL_UpdateWindowSurface(this->window);
}

void Window::destroyWindow() {
	SDL_FreeSurface(this->surface);
	this->surface = nullptr;
	SDL_FreeSurface(this->currImgSurface);
	this->currImgSurface = nullptr;
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
	if (this->instance) {
		delete this->instance;
	}
}
