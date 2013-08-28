//
//  MenuLayer.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__MenuLayer__
#define __dodge__MenuLayer__

#include <iostream>

#endif /* defined(__dodge__MenuLayer__) */

#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MenuLayer : public cocos2d::CCLayer
{
public:
    CCMenu* pMenu;
    
    MenuLayer(void);
    ~MenuLayer(void);
    
    //÷ÿ–¥init
    virtual bool init();
    CREATE_FUNC(MenuLayer);
    void menuCloseCallback(CCObject* pSender);
    void menuStartCallback(CCObject* pSender);
    void enterGame(CCNode* pSender);
};

