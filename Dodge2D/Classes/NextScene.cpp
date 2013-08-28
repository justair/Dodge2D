//
//  NextScene.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "NextScene.h"
#include "NextLayer.h"

NextScene::NextScene(void)
{
}


NextScene::~NextScene(void)
{
}

bool NextScene::init()
{
	bool b = false;
	do{
        NextLayer *layer = NextLayer::create();
        this ->addChild(layer);
        b = true;
	}while(0);
	
    return b;
}
