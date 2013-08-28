//
//  SpriteScene.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "SpriteScene.h"
#include "SpriteLayer.h"
#include "TouchLayer.h"
#include "BackLayer.h"

SpriteScene::SpriteScene(void)
{
}

SpriteScene::~SpriteScene(void)
{
}

bool SpriteScene::init()
{
	bool b = false;
	do{
		BackLayer *backLayer = BackLayer::create();
        CC_BREAK_IF(! backLayer);
        this ->addChild(backLayer);
        
        SpriteLayer *layer = SpriteLayer::create();
        CC_BREAK_IF(! layer);
        this ->addChild(layer);
        
        TouchLayer* touchLayer = TouchLayer::create();
        touchLayer->setDelegate(layer);
        this->addChild(touchLayer);
        
        b = true;
	}while(0);
	
    return b;
}