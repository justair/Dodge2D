//
//  NextLayer.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__NextLayer__
#define __dodge__NextLayer__

#include <iostream>

#endif /* defined(__dodge__NextLayer__) */
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class NextLayer : public cocos2d::CCLayer
{
public:
    CCMenu* pMenu;
    
    NextLayer(void);
    ~NextLayer(void);
    
    //÷ÿ–¥init
    virtual bool init();
    CREATE_FUNC(NextLayer);
    void menuCloseCallback(CCObject* pSender);
    void menuNextCallback(CCObject* pSender);
    void nextGame(CCNode* pSender);
};

