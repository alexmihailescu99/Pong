#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Loader.h"
class GameObject;
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
	std::string title;
	int xPos = SDL_WINDOWPOS_UNDEFINED;
	int yPos = SDL_WINDOWPOS_UNDEFINED;
	int width = -1;
	int height = -1;
	SDL_WindowFlags flag = SDL_WINDOW_OPENGL;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Renderer* renderer = nullptr;
public:
	static Window* getInstance();
	void setWindowTitle(std::string title);
	std::string getWindowTitle();
	void setWindowXPos(int xPos);
	void setWindowYPos(int yPos);
	void setWindowWidth(int width);
	int getWindowWidth() { return this->width; };
	void setWindowHeight(int height);
	int getWindowHeight() { return this->height; };
	void setWindowFlag(SDL_WindowFlags flag);
	// Creates an SDL_Window, along with an SDLSurface
	// Returns true if window was created, false if error
	// Assumes that SDL subsystems are initialised by the Game class
	bool createWindow();
	// Returns a pointer to the SDL_Window field
	SDL_Window* getWindow();
	// Load an image into an SDL_Surface
	// Supported image formats : BMP, PNG
	// Returns true if successful, or false if not
	// Sets the currImgSurface and currImgPath fields if succesful
	
	// Draw the specified color(in RGB) onto the SDL_Surface of the SDL_Window, then update the window
	void drawColor(uint r, uint g, uint b);
	// Draw the image from the specified path onto the SDL_Surface of the SDL_Window, then update the window
	// Supported image formats : BMP, PNG, JPG
	void drawImage(std::string imagePath, std::string imageFormat);
	void drawTexture(std::string texturePath, std::string textureFormat, int xPos, int yPos);
	// Draw specified GameObject onto the window
	void draw(GameObject* obj);
	SDL_Renderer* getRenderer() { return this->renderer; };
};
#endif // WINDOW_H_
