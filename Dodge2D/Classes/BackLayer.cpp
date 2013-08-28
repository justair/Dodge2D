//
//  BackLayer.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "BackLayer.h"


BackLayer::BackLayer(void)
{
}

BackLayer::~BackLayer(void)
{
}

bool BackLayer::init()
{
	bool b = false;
	do{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* back=CCSprite::create("backgroud.png");
        float sx = size.width/800;
        float sy = size.height/480;
        float sc;
        if(sx > sy)
            sc = sx;
        else
            sc = sy;
        back->setScaleX(sc);
        back->setScaleY(sc);
		back ->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(back);
        
        CCScaleTo * scaleIn = CCScaleTo::create(1,sc * 1.02,sc * 1.02);
        CCScaleTo * scaleOut = CCScaleTo::create(1,sc,sc);
        CCEaseSineInOut* easeIn = CCEaseSineInOut::create(scaleIn);
        CCEaseSineInOut* easeOut = CCEaseSineInOut::create(scaleOut);
        CCSequence* sequence = CCSequence::create(easeIn,easeOut,NULL);
        CCRepeat * repeat = CCRepeat::create(sequence,999999);
        back->runAction(repeat);
        
		b=true;
	}while(0);
    
	return b;
}
