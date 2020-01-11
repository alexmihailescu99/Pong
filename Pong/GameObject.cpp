#include "GameObject.h"

GameObject::GameObject(std::string texturePath, std::string textureFormat, std::string tag) {
	this->currentFrame = Loader::getInstance()->loadTexture(texturePath, textureFormat);
	if (this->currentFrame == nullptr) {
		std::cerr << "Error, could not create GameObject\n";
	}
	this->tag = tag;
	this->isVisible = true;
	// Save the width and height of the texture into the object
	SDL_QueryTexture(this->currentFrame, NULL, NULL, &this->w, &this->h);
	this->x = 0;
	this->y = 0;
}

GameObject::~GameObject() {
	SDL_DestroyTexture(this->currentFrame);
	this->currentFrame = nullptr;
	for (Animation* anim : this->animations) {
		delete anim;
	}
}

void GameObject::addAnimation(Animation* animation) {
	this->animations.push_back(animation);
	animation->setParent(this);
}

void GameObject::playCurrAnimation() {
	this->currAnimation->play();
}

Animation* GameObject::findAnimationByTag(std::string animationTag) {
	for (Animation* animation : this->animations) {
		if (animation->getTag() == animationTag) {
			return animation;
		}
	}
}