//
//  NextScene.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__NextScene__
#define __dodge__NextScene__

#include <iostream>

#endif /* defined(__dodge__NextScene__) */
#pragma once
#include "cocos2d.h"
class NextScene :
public cocos2d::CCScene
{
public:
	NextScene(void);
	~NextScene(void);
	virtual bool init(void);
	CREATE_FUNC(NextScene);
};