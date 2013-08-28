//
//  EndLayer.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__EndLayer__
#define __dodge__EndLayer__

#include <iostream>

#endif /* defined(__dodge__EndLayer__) */
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class EndLayer : public cocos2d::CCLayer
{
public:
    CCMenu* pMenu;
    
    EndLayer(void);
    ~EndLayer(void);
    
    //÷ÿ–¥init
    virtual bool init();
    CREATE_FUNC(EndLayer);
    void menuCloseCallback(CCObject* pSender);
    void menuStartCallback(CCObject* pSender);
    void menuAgainCallback(CCObject* pSender);
    void enterGame(CCNode* pSender);
    void againGame(CCNode* pSender);
};