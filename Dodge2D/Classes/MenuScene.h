//
//  MenuScene.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__MenuScene__
#define __dodge__MenuScene__

#include <iostream>

#endif /* defined(__dodge__MenuScene__) */
#pragma once
#include "cocos2d.h"
class MenuScene :
public cocos2d::CCScene
{
public:
	MenuScene(void);
	~MenuScene(void);
	virtual bool init(void);
	CREATE_FUNC(MenuScene);
};
