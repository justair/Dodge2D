//
//  MenuLayer.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "MenuLayer.h"
#include "MenuLayer.h"
#include "SpriteScene.h"
#include "SimpleAudioEngine.h"

MenuLayer::MenuLayer(void)
{
}

MenuLayer::~MenuLayer(void)
{
}

bool MenuLayer::init()
{
	bool b = false;
	do{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
        
		/*CCMenuItemImage *pStartItem = CCMenuItemImage::create(
         "startMenu1.png",
         "startMenu2.png",
         this,
         menu_selector(MenuLayer::menuStartCallback));
         
		 CCMenuItemImage *pEndItem = CCMenuItemImage::create(
         "endMenu1.png",
         "endMenu2.png",
         this,
         menu_selector(MenuLayer::menuCloseCallback));
		 */
        
		CCMenuItemSprite*pStartItem = CCMenuItemSprite::create(
                                                               CCSprite::createWithSpriteFrameName( "startMenu1.png"),
                                                               CCSprite::createWithSpriteFrameName( "startMenu2.png"),
                                                               this,
                                                               menu_selector(MenuLayer::menuStartCallback));
        pStartItem->setPosition(ccp(size.width/2, size.height/2 - 20));
        
        CCMenuItemSprite *pEndItem = CCMenuItemSprite::create(
                                                              CCSprite::createWithSpriteFrameName("endMenu1.png"),
                                                              CCSprite::createWithSpriteFrameName("endMenu2.png"),
                                                              this,
                                                              menu_selector(MenuLayer::menuCloseCallback));
        pEndItem->setPosition(ccp(size.width/2, size.height/2 - 100));
		
        pMenu = CCMenu::create(pStartItem,pEndItem,NULL);
        pMenu->setPosition(CCPointZero);
        
        this->addChild(pMenu, 1000);
        
        CCLabelBMFont *label = CCLabelBMFont::create("the string", "konqa32-hd.fnt");
		this->addChild(label);
		label->setScale(1.2);
		label->setPosition(ccp(size.width/2, size.height/2 +100));
		label->setString("dodge octopus");
        
        b = true;
	}while(0);
    
	return b;
}

void MenuLayer::menuStartCallback(CCObject* pSender)
{
	CCFadeTo * fade =  CCFadeTo::create(0.0f,0);
	CCCallFuncN* enter = CCCallFuncN::create(this,callfuncN_selector(MenuLayer::enterGame));
    
	CCAction* action = CCSequence::create(fade,enter,NULL);
    
	pMenu->runAction(action);
}

void MenuLayer::enterGame(CCNode* pSender)
{
	SpriteScene* scene = SpriteScene::create();
	CCDirector::sharedDirector()->replaceScene(scene);
	//CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipAngular::create(2,SpriteScene));
}

void MenuLayer::menuCloseCallback(CCObject* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector::sharedDirector()->end();
}