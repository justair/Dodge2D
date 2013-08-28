//
//  EndLayer.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "EndLayer.h"
#include "SpriteScene.h"
#include "Global.h"
#include "SimpleAudioEngine.h"

EndLayer::EndLayer(void)
{
}

EndLayer::~EndLayer(void)
{
}

bool EndLayer::init()
{
	bool b = false;
	do{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        CCMenuItemSprite *pAgainItem = CCMenuItemSprite::create(
                                                                CCSprite::createWithSpriteFrameName( "againMenu1.png"),
                                                                CCSprite::createWithSpriteFrameName( "againMenu2.png"),
                                                                this,
                                                                menu_selector(EndLayer::menuAgainCallback));
        pAgainItem->setPosition(ccp(size.width/2, size.height/2));
        
        CCMenuItemSprite *pNewItem = CCMenuItemSprite::create(
                                                              CCSprite::createWithSpriteFrameName( "startMenu1.png"),
                                                              CCSprite::createWithSpriteFrameName( "startMenu2.png"),
                                                              this,
                                                              menu_selector(EndLayer::menuStartCallback));
        pNewItem->setPosition(ccp(size.width/2, size.height/2-70));
        
        CCMenuItemSprite *pEndItem = CCMenuItemSprite::create(
                                                              CCSprite::createWithSpriteFrameName("endMenu1.png"),
                                                              CCSprite::createWithSpriteFrameName("endMenu2.png"),
                                                              this,
                                                              menu_selector(EndLayer::menuCloseCallback));
        pEndItem->setPosition(ccp(size.width/2, size.height/2 - 145));
        
        pMenu = CCMenu::create(pAgainItem,pNewItem,pEndItem,NULL);
        pMenu->setPosition(CCPointZero);
        
        this->addChild(pMenu, 1000);
        
        CCSprite *pic = CCSprite::createWithSpriteFrameName("zhangyu_0021.png");
        pic->setPosition(ccp(size.width/2, size.height/2 + 110));
        this->addChild(pic, 1000);
        
        b = true;
	}while(0);
    
	return b;
}

void EndLayer::menuAgainCallback(CCObject* pSender)
{
	CCFadeTo * fade =  CCFadeTo::create(0.0f,0);
	CCCallFuncN* enter = CCCallFuncN::create(this,callfuncN_selector(EndLayer::againGame));
    
	CCAction* action = CCSequence::create(fade,enter,NULL);
    
	pMenu->runAction(action);
}


void EndLayer::menuStartCallback(CCObject* pSender)
{
	CCFadeTo * fade =  CCFadeTo::create(0.0f,0);
	CCCallFuncN* enter = CCCallFuncN::create(this,callfuncN_selector(EndLayer::enterGame));
    
	CCAction* action = CCSequence::create(fade,enter,NULL);
    
	pMenu->runAction(action);
}

void EndLayer::enterGame(CCNode* pSender)
{
	g_stage = 1;
	g_point = 0;
	SpriteScene* SpriteScene = SpriteScene::create();
	CCDirector::sharedDirector()->replaceScene(SpriteScene);
	//CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipAngular::create(2,SpriteScene));
}

void EndLayer::againGame(CCNode* pSender)
{
	g_point = 0;
	SpriteScene* SpriteScene = SpriteScene::create();
	CCDirector::sharedDirector()->replaceScene(SpriteScene);
	//CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipAngular::create(2,SpriteScene));
}

void EndLayer::menuCloseCallback(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector::sharedDirector()->end();
}
