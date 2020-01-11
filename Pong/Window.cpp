#include "Window.h"
#include "GameObject.h"
Window* Window::instance = nullptr;

Window::Window() {

}

Window::~Window() {
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;
	SDL_FreeSurface(this->surface);
	this->surface = nullptr;
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
	if (this->instance) {
		delete this->instance;
	}
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

void Window::setWindowHeight(int height) {
	this->height = height;
}

void Window::setWindowWidth(int width) {
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
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (!this->renderer) {
		std::cerr << "SDL Renderer could not be created! (SDL Error)\n";
		return false;
	}
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	return true;
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

void Window::drawTexture(std::string texturePath, std::string textureFormat, int xPos, int yPos) {
	if (window == nullptr) {
		if (!(this->createWindow())) {
			return;
		}
	}
	SDL_Texture* texture = nullptr;
	if (textureFormat == "BMP") {
		texture = Loader::getInstance()->loadTexture(texturePath, "BMP");
		if (texture == nullptr) {
			return;
		}
	}
	if (textureFormat == "PNG") {
		texture = Loader::getInstance()->loadTexture(texturePath, "PNG");
		if (texture == nullptr) {
			std::cerr << "Could not load texture from " << texturePath << std::endl;
			return;
		}
	}
	if (textureFormat == "JPG") {
		texture = Loader::getInstance()->loadTexture(texturePath, "JPG");
		if (texture == nullptr) {
			return;
		}
	}
	SDL_RenderClear(this->renderer);
	SDL_Rect dstRect;
	int width = 0, height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	dstRect.w = width;
	dstRect.h = height;
	dstRect.x = xPos;
	dstRect.y = yPos;

	SDL_RenderCopy(this->renderer, texture, NULL, &dstRect);
	SDL_RenderPresent(this->renderer);
	SDL_DestroyTexture(texture);
}

void Window::draw(GameObject* obj) {
	if (window == nullptr) {
		if (!(this->createWindow())) {
			return;
		}
	}
	if (obj->getCurrentFrame() == nullptr) {
		std::cerr << "Can not draw " << obj->getTag() << " : No texture found" << std::endl;
		return;
	}
	SDL_Rect dstRect;
	dstRect.w = obj->getWidth();
	dstRect.h = obj->getHeight();
	dstRect.x = obj->getXPos();
	dstRect.y = obj->getYPos();
	if (obj->isFlipped()) {
		SDL_RenderCopyEx(this->renderer, obj->getCurrentFrame(), NULL, &dstRect, NULL, NULL, SDL_FLIP_HORIZONTAL);
		return;
	}
	SDL_RenderCopy(this->renderer, obj->getCurrentFrame(), NULL, &dstRect);
}

