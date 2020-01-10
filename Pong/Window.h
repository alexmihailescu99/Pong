#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL.h>
#include <iostream>
#include <string>
typedef unsigned int uint;
// Wrapper class for SDL_Window
// Follows singleton design pattern
// Required fields:
// std::string title
// int windowXPos (default is SDL_WINDOWPOS_UNDEFINED)
// int windowYPos (default is SDL_WINDOWPOS_UNDEFINED)
// int windowWidth
// int windowHeight
// SDL_WindowFlags flag (default is SDL_WINDOW_OPENGL)
class Window {

private:
	static Window* instance;
	Window();
	~Window();
	// Creates an SDL_Window, along with an SDLSurface
	// Returns true if window was created, false if error
	// Assumes that SDL subsystems are initialised by the Game class
	// The SDL_Window is created by the draw functions if needed
	// This abstracts away some code from the programmer, but is rather dangerous
	// E.G. Adding a new draw function requires calling this function first
	bool createWindow();
	// Load an image into an SDL_Surface
	// Returns true if successful, or false if not
	// Sets the currImgSurface and currImgPath fields if succesful
	bool loadImage(std::string imagePath);
	std::string title;
	int xPos = SDL_WINDOWPOS_UNDEFINED;
	int yPos = SDL_WINDOWPOS_UNDEFINED;
	uint width = -1;
	uint height = -1;
	SDL_WindowFlags flag = SDL_WINDOW_OPENGL;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	// Needed to prevent loading the same image over and over again
	SDL_Surface* currImgSurface = nullptr;
	// Needed to prevent loading the same image over and over again
	std::string currImgPath;
	// Needed to know if we are stretching source image or not
	bool stretching = false;
public:
	static Window* getInstance();
	void setWindowTitle(std::string title);
	std::string getWindowTitle();
	void setWindowXPos(int xPos);
	void setWindowYPos(int yPos);
	void setWindowWidth(uint width);
	void setWindowHeight(uint height);
	void setWindowFlag(SDL_WindowFlags flag);
	// Returns a pointer to the SDL_Window field
	SDL_Window* getWindow();
	// Draw the specified color(in RGB) onto the SDL_Surface of the SDL_Window, then update the window
	void drawColor(uint r, uint g, uint b);
	// Draw the image from the specified path onto the SDL_Surface of the SDL_Window, then update the window
	void drawImage(std::string imagePath);
	// Deallocates memory for the Window object
	// Calls the specific SDL Destruction functions
	void destroyWindow();
};
#endif // WINDOW_H_
