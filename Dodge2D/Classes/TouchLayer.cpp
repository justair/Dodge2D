//
//  TouchLayer.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "TouchLayer.h"

TouchLayer::TouchLayer(void)
{
}

TouchLayer::~TouchLayer(void)
{
}

bool TouchLayer::init()
{
	bool b = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
		this->setTouchEnabled(true);
        
		//this->registerWithTouchDispatcher();
        //this->setDelegate(NULL);
        b = true;
    } while (0);
    
    return b;
}

void TouchLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void TouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if(pTouches->count() == 1) {
        CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
        CCPoint position = touch->getLocationInView();
        position = CCDirector::sharedDirector()->convertToGL(position);
        if(this->getDelegate())
            this->getDelegate()->touchesBegan(position);
    }
}

void TouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if(pTouches->count() == 1) {
        CCTouch* touch=dynamic_cast<CCTouch*>(pTouches->anyObject());
        CCPoint position = touch->getLocationInView();
        position = CCDirector::sharedDirector()->convertToGL(position);
        if(this->getDelegate())
            this->getDelegate()->touchesEnd(position);
    }
}

void TouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if(pTouches->count() == 1){
        CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
        CCPoint position = touch->getLocationInView();
        position = CCDirector::sharedDirector()->convertToGL(position);
        if(this->getDelegate())
            this->getDelegate()->touchesEnd(position);
    }
}
