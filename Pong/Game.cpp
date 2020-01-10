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
	while (this->quit != true) {
		while (SDL_PollEvent((&this->eventHandler)) != 0) {
			if ((this->eventHandler).type == SDL_QUIT) {
				this->quit = true;
			}
		}
		Window::getInstance()->drawImage("hello_world.bmp");
	}
}
