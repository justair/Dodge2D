#include "MenuScene.h"
#include "MenuLayer.h"

MenuScene::MenuScene(void)
{
}


MenuScene::~MenuScene(void)
{
}

bool MenuScene::init()
{
	bool b = false;
	do{
        MenuLayer *layer = MenuLayer::create();
        this ->addChild(layer);
        b = true;
	}while(0);
	
    return b;
}