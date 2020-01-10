#include "Game.h"

Game* Game::instance = nullptr;
const uint SCREEN_WIDTH = 640;
const uint SCREEN_HEIGHT = 480;
Game::Game() {

}

Game::~Game() {
	SDL_Quit();
	if (this->instance) {
		delete this->instance;
	}
}

bool Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Error: Could not initialise SDL subsystems!\n";
		return false;
	}
	int imgFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlag) & imgFlag)) {
		std::cerr << "Could not init PNG loading!\n";
	}
	Window::getInstance()->setWindowTitle("Pong");
	Window::getInstance()->setWindowWidth(SCREEN_WIDTH);
	Window::getInstance()->setWindowHeight(SCREEN_HEIGHT);
	return true;
}

Game* Game::getInstance() {
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}

void Game::run() {
	while (!this->quit) {
		// Listen for events
		while (SDL_PollEvent((&this->eventHandler)) != 0) {
			// If the user presses the X button
			if (eventHandler.type == SDL_QUIT) {
				this->quit = true;
			}
			// If the user presses a key
			if (eventHandler.type == SDL_KEYDOWN) {
				// Check which key it is
				switch (eventHandler.key.keysym.sym) {
				case SDLK_DOWN:
					std::cout << "Down key pressed!\n";
					break;
				case SDLK_UP:
					std::cout << "Up key pressed!\n";
					break;
				default:
					break;
				}
			}
		}
		Window::getInstance()->drawImage("image.jpg", "JPG");
	}
}
