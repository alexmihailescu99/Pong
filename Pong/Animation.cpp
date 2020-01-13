#include "Animation.h"
#include "GameObject.h"

Animation::Animation(int noFrames, std::string tag) {
	this->noFrames = noFrames;
	this->tag = tag;
}

Animation::~Animation() {
	for (SDL_Texture* frame : this->frames) {
		delete frame;
	}
}

void Animation::loadFrame(std::string framePath, std::string frameFormat) {
	SDL_Texture* frame = Loader::getInstance()->loadTexture(framePath, frameFormat);
	this->frames.push_back(frame);
}

void Animation::play() {
	// Set the current animation of the parent to this
	this->parent->setCurrAnimation(this);
	// Send the frame to render
	this->parent->setCurrentFrame(this->frames.at(currFrame));
	// Move on to the next frame
	this->currFrame++;
	SDL_Delay(10);
	// Check if we are out of bounds
	if (this->currFrame >= this->noFrames) {
		this->currFrame = 0;
	}
}

SDL_Texture* Animation::getFrame(int frameNumber) {
	return this->frames.at(frameNumber);
}
