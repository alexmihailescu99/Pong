#ifndef ANIMATION_H_
#define ANIMATION_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Loader.h"
class GameObject;
class Animation {
private:
	int noFrames;
	std::vector<SDL_Texture*> frames;
	int currFrame = 0;
	GameObject* parent;
	std::string tag;
public:
	Animation(int noFrames, std::string tag);
	~Animation();
	void loadFrame(std::string framePath, std::string frameFormat);
	void play();
	void setParent(GameObject* parent) { this->parent = parent; };
	GameObject* getParent() { return this->parent; };
	void setTag(std::string tag) { this->tag = tag; };
	std::string getTag() { return this->tag; };
};

#endif // ANIMATION_H_
