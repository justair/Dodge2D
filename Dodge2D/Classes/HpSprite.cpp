//
//  HpSprite.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#include "HpSprite.h"
#include "Global.h"

HpSprite::HpSprite(void)
{
}


HpSprite::~HpSprite(void)
{
}

bool HpSprite::init()
{
	_currentNum = 0;
	_maxNum = g_energyNum;
    
	CCSprite::init();
	_hpLogo = CCSprite::createWithSpriteFrameName("hpLogo.png");
	//_hpLogo->setAnchorPoint(ccp(0,0));
	_hpBack = CCSprite::createWithSpriteFrameName("hpBarBack.png");
	_hpBack->setAnchorPoint(ccp(0,0));
    
	_hpEffectBar = CCSprite::createWithSpriteFrameName("hpBarEffect.png");
	_hpEffectBar->setAnchorPoint(ccp(0,0));
    
	_hpBar = CCSprite::createWithSpriteFrameName("hpBar.png");
	_hpBar->setAnchorPoint(ccp(0,0));
	_hpBar->setScaleX(0);
    
	_hpBack->setPosition(ccp(24,0));
	this->addChild(_hpBack);
	_hpEffectBar->setPosition(ccp(25,0));
	this->addChild(_hpEffectBar);
	_hpBar->setPosition(ccp(25,0));
	this->addChild(_hpBar);
	_hpLogo->setPosition(ccp(18,17));
	this->addChild(_hpLogo);
    
	_label = CCLabelBMFont::create("the string", "konqa32.fnt");
	_label->setScale(.4);
	_label->setPosition(ccp(135, 6));
	sprintf(keyname,"0/%d",_maxNum);
	_label->setString(keyname);
	this->addChild(_label);
    
	_pointLabel =  CCLabelBMFont::create("0", "konqa32.fnt");
	_pointLabel->setAnchorPoint(ccp(0,0));
	_pointLabel->setScale(1);
	_pointLabel->setPosition(ccp(-520, -5));
	this->addChild(_pointLabel);
	char str[10];
	sprintf(str,"%d",g_point);
	_pointLabel->setString(str);
    
	return true;
}

void HpSprite::add(int num)
{
	_currentNum+=num;
	sprintf(keyname,"%d/%d",_currentNum,_maxNum);
	_label->setString(keyname);
	_hpBar->setScaleX(float(_currentNum)/_maxNum);
}

void HpSprite::addPoint(int num)
{
	g_point+=num;
	char str[10];
	sprintf(str,"%d",g_point);
	_pointLabel->setString(str);
}

bool HpSprite::isFull()
{
	if(_currentNum >= _maxNum)
		return true;
	else
		return false;
}