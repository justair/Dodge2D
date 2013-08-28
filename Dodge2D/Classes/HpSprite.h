//
//  HpSprite.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__HpSprite__
#define __dodge__HpSprite__

#include <iostream>

#endif /* defined(__dodge__HpSprite__) */
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class HpSprite :
public cocos2d::CCSprite
{
private:
	int _maxNum;
	int _currentNum;
	CCSprite* _hpLogo;
	CCSprite* _hpBack;
	CCSprite* _hpBar;
	CCSprite* _hpEffectBar;
	CCLabelBMFont* _label;
	CCLabelBMFont* _pointLabel;
    
	char keyname[100];
    
public:
	HpSprite(void);
	~HpSprite(void);
    
	//÷ÿ–¥init
	virtual bool init();
	void add(int num);
	void addPoint(int num);
	bool isFull();
    
	CREATE_FUNC(HpSprite);
};

