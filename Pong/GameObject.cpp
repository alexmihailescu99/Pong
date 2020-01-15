#include "GameObject.h"

GameObject::GameObject(std::string texturePath, std::string textureFormat, std::string tag) {
	this->currentFrame = Loader::getInstance()->loadTexture(texturePath, textureFormat);
	if (this->currentFrame == nullptr) {
		std::cerr << "Error, could not create GameObject\n";
	}
	this->tag = tag;
	// Save the width and height of the texture into the object
	SDL_QueryTexture(this->currentFrame, NULL, NULL, &this->w, &this->h);
	this->x = 0;
	this->y = 0;
	this->objRect = new SDL_Rect;
	this->objRect->h = this->h;
	this->objRect->w = this->w;
	this->objRect->x = this->x;
	this->objRect->y = this->y;
	this->animated = false;
}

GameObject::GameObject(std::string tag, Animation* idleAnimation) {
	this->tag = tag;
	this->addAnimation(idleAnimation);
	this->currentFrame = idleAnimation->getFrame(0);
	this->setCurrAnimation(idleAnimation);
	// Save the width and height of the texture into the object
	SDL_QueryTexture(this->currentFrame, NULL, NULL, &this->w, &this->h);
	this->x = 0;
	this->y = 0;
	this->objRect = new SDL_Rect;
	this->objRect->h = this->h;
	this->objRect->w = this->w;
	this->objRect->x = this->x;
	this->objRect->y = this->y;
	this->animated = true;
}

GameObject::~GameObject() {
	SDL_DestroyTexture(this->currentFrame);
	this->currentFrame = nullptr;
	delete this->objRect;
	this->objRect = nullptr;
	if (this->animated) {
		for (Animation* anim : this->animations) {
			delete anim;
		}
	}
}

void GameObject::addAnimation(Animation* animation) {
	this->animations.push_back(animation);
	animation->setParent(this);
}

void GameObject::playCurrAnimation() {
	this->currAnimation->play();
}

void GameObject::scale(int scaleVal) {
	if (scaleVal == 0) {
		return;
	}
	if (scaleVal > 0) {
		this->w *= scaleVal;
		this->h *= scaleVal;
	}
	else {
		this->w /= scaleVal;
		this->h /= scaleVal;
	}
}

Animation* GameObject::findAnimationByTag(std::string animationTag) {
	for (Animation* animation : this->animations) {
		if (animation->getTag() == animationTag) {
			return animation;
		}
	}
}