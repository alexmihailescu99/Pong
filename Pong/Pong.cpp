#include <iostream>
#include "Game.h"

int main(int argc, char *argv[]) {
    Game::getInstance()->init();
    Game::getInstance()->addGameObject("assets/background.jpg", "JPG", "Background");
    Animation* animation = new Animation(10, "Idle");
    Animation* animation2 = new Animation(10, "Idle");
    Animation* animation3 = new Animation(10, "Walk");
    Animation* animation4 = new Animation(8, "Idle");
    Animation* animation5 = new Animation(8, "Idle");
    for (int i = 0; i < 10; ++i) {
        std::string name = "assets/Knight2/png/Idle (" + std::to_string(i + 1) + ").png";
        animation->loadFrame(name, "PNG");
        name = "assets/Knight2/png/Walk (" + std::to_string(i + 1) + ").png";
        animation3->loadFrame(name, "PNG");
        name = "assets/Enemy/Idle/" + std::to_string(i) + ".png";
        animation2->loadFrame(name, "PNG");
    }
    for (int i = 0; i < 8; ++i) {
        std::string name = "assets/2D/view-front/images/coin000" + std::to_string(i) + ".png";
        animation4->loadFrame(name, "PNG");
        name = "assets/Bed/bottlePotionHealth000" + std::to_string(i) + ".png";
        animation5->loadFrame(name, "PNG");
    }
    Game::getInstance()->addGameObject("Player", animation);
    Game::getInstance()->addGameObject("Enemy", animation2);
    Game::getInstance()->addGameObject("Coin", animation4);
    Game::getInstance()->addGameObject("HPPotion", animation5);
    GameObject* obj = Game::getInstance()->findObjectByTag("Player");
    obj->setWidth(148);
    obj->setHeight(186);
    obj->setXPos(0);
    obj->setYPos(Window::getInstance()->getWindowHeight() - obj->getHeight());
    obj->addAnimation(animation3);
    obj = Game::getInstance()->findObjectByTag("Enemy");
    obj->setWidth(236);
    obj->setHeight(298);
    obj->setYPos(Window::getInstance()->getWindowHeight() - obj->getHeight() + 50);
    obj->setXPos(400);
    obj = Game::getInstance()->findObjectByTag("Coin");
    obj->setXPos(200);
    obj->setYPos(Window::getInstance()->getWindowHeight() - obj->getHeight() - 30);
    obj = Game::getInstance()->findObjectByTag("HPPotion");
    obj->setXPos(300);
    obj->setYPos(Window::getInstance()->getWindowHeight() - obj->getHeight() - 30);
    Game::getInstance()->run();
    return 0;
}
