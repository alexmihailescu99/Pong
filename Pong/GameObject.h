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
	SDL_Texture* currentFrame = nullptr;
	int x;
	int y;
	int h;
	int w;
	bool isVisible;
	std::string tag;
	bool flipped = false;
	std::vector<Animation*> animations;
	Animation* currAnimation;
public:
	GameObject(std::string texturePath, std::string textureFormat, std::string tag);
	~GameObject();
	void setVisible(bool isVisible) { this->isVisible = isVisible; };
	void setXPos(int xPos) { this->x = xPos; };
	void setYPos(int yPos) { this->y = yPos; };
	void setWidth(int width) { this->w = width; };
	void setHeight(int height) { this->h = height; };
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
};

#endif // GAME_OBJECT_
