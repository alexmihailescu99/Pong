#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Window.h"
#include "GameObject.h"
// Game class
// Follows singleton design pattern
class Game {
private:
	Game();
	~Game();
	void handleEvents();
	static Game* instance;
	bool quit = false;
	SDL_Event eventHandler;
	std::vector<GameObject*> gameObjects;
	void drawGameObjects();
	void update();
	GameObject* player;
public:
	// Initialises SDL subsystems
	// Creates SDL_Window
	// Returns true if succesful, or false if not
	bool init();
	static Game* getInstance();
	void run();
	// Add a new GameObject into the world
	void addGameObject(std::string texturePath, std::string textureFormat, std::string tag);
	void addGameObject(std::string tag, Animation* idleAnimation);
	void removeGameObject(std::string tag);
	// Returns object if found, nullptr if not
	GameObject* findObjectByTag(std::string tag);
};

#endif // GAME_H_
