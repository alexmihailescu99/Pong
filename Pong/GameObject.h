#ifndef GAME_OBJECT_
#define GAME_OBJECT_
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "Loader.h"
#include "Window.h"
#include "Animation.h"
class GameObject {
private:
	bool isVisible = true;
	bool flipped = false;
	bool animated = false;
	bool walking = false;
	bool running = false;
	bool active = true;
	int x;
	int y;
	int h;
	int w;
	std::string tag;
	std::vector<Animation*> animations;
	Animation* currAnimation;
	SDL_Texture* currentFrame = nullptr;
	SDL_Rect* objRect;
public:
	GameObject(std::string texturePath, std::string textureFormat, std::string tag);
	GameObject(std::string tag, Animation* idleAnimation);
	~GameObject();
	void setVisible(bool isVisible) { this->isVisible = isVisible; };
	void setXPos(int xPos) { this->x = xPos; this->objRect->x = xPos; };
	void setYPos(int yPos) { this->y = yPos; this->objRect->y = yPos;};
	void setWidth(int width) { this->w = width; this->objRect->w = width; };
	void setHeight(int height) { this->h = height; this->objRect->h = height; };
	void setTag(std::string tag) { this->tag = tag; };
	int getXPos() { return this->x; };
	int getYPos() { return this->y; };
	int getHeight() { return this->h; };
	int getWidth() { return this->w; };
	int getVisible() { return this->isVisible; };
	std::string getTag() { return this->tag; };
	void setCurrAnimation(Animation* animation) { this->currAnimation = animation; };
	Animation* getCurrAnimation() { return this->currAnimation; };
	void setCurrentFrame(SDL_Texture* frame) { this->currentFrame = frame; };
	SDL_Texture* getCurrentFrame() { return this->currentFrame; };
	void setFlipped(bool val) { this->flipped = val; };
	bool isFlipped() { return this->flipped; };
	void addAnimation(Animation* animation);
	void playCurrAnimation();
	Animation* findAnimationByTag(std::string animationTag);
	void setAnimated(bool val) { this->animated = val; };
	bool isAnimated() { return this->animated; };
	void setWalking(bool val) { this->walking = val; };
	bool isWalking() { return this->walking; };
	void setRunning(bool val) { this->walking = val; };
	bool isRunning() { return this->running; };
	void scale(int scaleVal);
	void setActive(bool val);
	SDL_Rect* getRect() { return this->objRect; };
};

#endif // GAME_OBJECT_
