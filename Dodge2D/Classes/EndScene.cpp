//
//  EndScene.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//
#include "EndScene.h"
#include "EndLayer.h"

EndScene::EndScene(void)
{
}


EndScene::~EndScene(void)
{
}

bool EndScene::init()
{
	bool b = false;
	do{
        EndLayer *layer = EndLayer::create();
        this ->addChild(layer);
        b = true;
	}while(0);
	
    return b;
}