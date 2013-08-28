//
//  SpriteScene.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__SpriteScene__
#define __dodge__SpriteScene__

#include <iostream>

#endif /* defined(__dodge__SpriteScene__) */
#pragma once
#include "cocos2d.h"
class SpriteScene :
public cocos2d::CCScene
{
public:
	SpriteScene(void);
	~SpriteScene(void);
	virtual bool init(void);
	CREATE_FUNC(SpriteScene);
};