//
//  NextLayer.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "NextLayer.h"
#include "SpriteScene.h"
#include "SpriteLayer.h"
#include "Global.h"
#include "SimpleAudioEngine.h"

NextLayer::NextLayer(void)
{
}

NextLayer::~NextLayer(void)
{
}

bool NextLayer::init()
{
	bool b = false;
	do{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
        
		CCMenuItemSprite *pNextItem = CCMenuItemSprite::create(
                                                               CCSprite::createWithSpriteFrameName( "nextMenu1.png"),
                                                               CCSprite::createWithSpriteFrameName( "nextMenu2.png"),
                                                               this,
                                                               menu_selector(NextLayer::menuNextCallback));
        pNextItem->setPosition(ccp(size.width/2, size.height/2 -20));
        
        
        CCMenuItemSprite *pEndItem = CCMenuItemSprite::create(
                                                              CCSprite::createWithSpriteFrameName("endMenu1.png"),
                                                              CCSprite::createWithSpriteFrameName("endMenu2.png"),
                                                              this,
                                                              menu_selector(NextLayer::menuCloseCallback));
        pEndItem->setPosition(ccp(size.width/2, size.height/2 - 90));
        
        pMenu = CCMenu::create(pNextItem,pEndItem,NULL);
        pMenu->setPosition(CCPointZero);
        
        this->addChild(pMenu, 1000);
        
        CCSprite *pic = CCSprite::createWithSpriteFrameName("flower_0001.png");
        pic->setPosition(ccp(size.width/2, size.height/2 + 90));
        this->addChild(pic, 1000);
        
        b = true;
	}while(0);
    
	return b;
}


void NextLayer::menuNextCallback(CCObject* pSender)
{
	CCFadeTo * fade =  CCFadeTo::create(0.0f,0);
    
	CCCallFuncN* enter = CCCallFuncN::create(this,callfuncN_selector(NextLayer::nextGame));
    
	CCAction* action = CCSequence::create(fade,enter,NULL);
    
	pMenu->runAction(action);
}

void NextLayer::nextGame(CCNode* pSender)
{
	g_stage = g_stage+1;
	CCLog("NextLayer:%d",g_stage);
	SpriteScene* SpriteScene = SpriteScene::create();
	CCDirector::sharedDirector()->replaceScene(SpriteScene);
	//CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipAngular::create(2,SpriteScene));
}


void NextLayer::menuCloseCallback(CCObject* pSender)
{
   CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector::sharedDirector()->end();
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}
