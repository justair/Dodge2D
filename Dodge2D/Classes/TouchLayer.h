//
//  TouchLayer.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__TouchLayer__
#define __dodge__TouchLayer__

#include <iostream>

#endif /* defined(__dodge__TouchLayer__) */
#pragma once
#include "cocos2d.h"
#include "SpriteLayer.h"
USING_NS_CC;

class TouchLayer : public cocos2d::CCLayer
{
public:
    CC_SYNTHESIZE(SpriteLayer*,_pDelegate,Delegate);
    
public:
	TouchLayer(void);
	~TouchLayer(void);
	bool init();
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	//virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	void onExit();
    
	CREATE_FUNC(TouchLayer);
};

