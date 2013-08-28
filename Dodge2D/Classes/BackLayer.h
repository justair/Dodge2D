//
//  BackLayer.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__BackLayer__
#define __dodge__BackLayer__

#include <iostream>

#endif /* defined(__dodge__BackLayer__) */
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class BackLayer :
public cocos2d::CCLayer
{
public:
	BackLayer(void);
	~BackLayer(void);
	virtual bool init();
    
	CREATE_FUNC(BackLayer);
};

