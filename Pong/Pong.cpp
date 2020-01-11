#include <iostream>
#include "Game.h"

int main(int argc, char *argv[]) {
    Game::getInstance()->init();
    Game::getInstance()->addGameObject("assets/background.jpg", "JPG", "Background");
    Game::getInstance()->addGameObject("assets/Knight2/png/Idle (1).png", "PNG", "Player");
    GameObject* obj = Game::getInstance()->findObjectByTag("Player");
    Animation* animation = new Animation(10, "Walk");
    for (int i = 0; i < 10; ++i) {
        std::string name = "assets/Knight2/png/Walk (" + std::to_string(i + 1) + ").png";
        animation->loadFrame(name, "PNG");
    }
    obj->addAnimation(animation);
    obj->setWidth(148);
    obj->setHeight(186);
    obj->setXPos(0);
    obj->setYPos(Window::getInstance()->getWindowHeight() - obj->getHeight());
    Game::getInstance()->run();
    return 0;
}
