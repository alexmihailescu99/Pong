#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <iostream>
#include "Window.h"
// Game class
// Follows singleton design pattern
class Game {
private:
	Game();
	~Game();
	static Game* instance;
	bool quit = false;
	SDL_Event eventHandler;
public:
	// Initialises SDL subsystems
	// Creates SDL_Window
	// Returns true if succesful, or false if not
	bool init();
	static Game* getInstance();
	void run();
};

#endif // GAME_H_
