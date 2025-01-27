#include "Game.h"
Game* Game::instance = nullptr;
const uint SCREEN_WIDTH = 640;
const uint SCREEN_HEIGHT = 480;
const int FPS = 30;
const int DELAY = 1000 / FPS;

Game::Game() {

}

Game::~Game() {
	SDL_Quit();
	for (GameObject* obj : this->gameObjects) {
		delete obj;
	}
	if (this->instance) {
		delete this->instance;
	}
}

bool Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
std::cerr << "Error: Could not initialise SDL subsystems!\n";
return false;
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cerr << "Could not init PNG & JPG loading!\n";
	}
	Window::getInstance()->setWindowTitle("Pong");
	Window::getInstance()->setWindowWidth(SCREEN_WIDTH);
	Window::getInstance()->setWindowHeight(SCREEN_HEIGHT);
	if (!(Window::getInstance()->createWindow())) {
		return false;
	}
	return true;
}

Game* Game::getInstance() {
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}

void Game::handleEvents() {
	while (SDL_PollEvent((&this->eventHandler)) != 0) {
		// If the user presses the X button
		if (this->eventHandler.type == SDL_QUIT) {
			this->quit = true;
		}
		// If the user presses a key
		if (this->eventHandler.type == SDL_KEYDOWN) {
			// Check which key it is
			switch (eventHandler.key.keysym.sym) {
			case SDLK_DOWN:
				break;
			case SDLK_UP:
				break;
			case SDLK_LEFT:
				if (this->player->getXPos() - 8 < 0) break;
				this->player->setWalking(true);
				this->player->setCurrAnimation(player->findAnimationByTag("Walk"));
				this->player->setXPos(player->getXPos() - 4);
				this->player->setFlipped(true);
				break;

			case SDLK_RIGHT:
				if (this->player->getXPos() + this->player->getWidth() + 4 >
					Window::getInstance()->getWindowWidth()) break;
				this->player->setWalking(true);
				this->player->setCurrAnimation(player->findAnimationByTag("Walk"));
				this->player->setXPos(player->getXPos() + 4);
				this->player->setFlipped(false);
				break;
			default:
				break;
			}
		}
	}
}

void Game::addGameObject(std::string texturePath, std::string textureFormat, std::string tag) {
	GameObject* obj = new GameObject(texturePath, textureFormat, tag);
	this->gameObjects.push_back(obj);
}

void Game::removeGameObject(std::string tag) {
	GameObject* obj = this->findObjectByTag(tag);
	if (obj == nullptr) {
		std::cerr << "Can not remove " << tag << " : it does not exist";
		return;
	}
	//this->gameObjects.erase(std::remove(this->gameObjects.begin(), this->gameObjects.end(), obj), this->gameObjects.end());
}

void Game::addGameObject(std::string tag, Animation* idleAnimation) {
	GameObject* obj = new GameObject(tag, idleAnimation);
	this->gameObjects.push_back(obj);
}

GameObject* Game::findObjectByTag(std::string tag) {
	for (GameObject* obj : this->gameObjects) {
		if (obj->getTag() == tag) {
			return obj;
		}
	}
	return nullptr;
}

void Game::drawGameObjects() {
	SDL_RenderClear(Window::getInstance()->getRenderer());
	for (GameObject* obj : this->gameObjects) {
		if (obj->isAnimated()) {
			if (!obj->isWalking()) {
				obj->setCurrAnimation(obj->findAnimationByTag("Idle"));
			}
			obj->playCurrAnimation();
			if (obj->getTag() == "Player") {
				obj->setWalking(false);
			}
		}
		if (obj->getVisible()) {
			Window::getInstance()->draw(obj);
		}
	}
	SDL_RenderPresent(Window::getInstance()->getRenderer());
}

void Game::run() {
	this->player = Game::getInstance()->findObjectByTag("Player");
	int frame = 0;
	Uint32 frameStart;
	int frameTime;
	GameObject* coin = Game::getInstance()->findObjectByTag("Coin");
	GameObject* hp = Game::getInstance()->findObjectByTag("HPPotion");
	while (!this->quit) {
		frameStart = SDL_GetTicks();
		// Listen for events
		this->handleEvents();
 		this->drawGameObjects();
		if (SDL_HasIntersection(this->player->getRect(), coin->getRect()) == SDL_TRUE) {
			coin->setVisible(false);
		}
		if (SDL_HasIntersection(this->player->getRect(), hp->getRect()) == SDL_TRUE) {
			hp->setVisible(false);
		}
		frameTime = SDL_GetTicks() - frameStart;
		if (DELAY > frameTime) {
			SDL_Delay(DELAY - frameTime);
		}
	}
}
