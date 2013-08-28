//
//  EndScene.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__EndScene__
#define __dodge__EndScene__

#include <iostream>

#endif /* defined(__dodge__EndScene__) */
#pragma once
#include "cocos2d.h"
class EndScene :
public cocos2d::CCScene
{
public:
	EndScene(void);
	~EndScene(void);
	virtual bool init(void);
	CREATE_FUNC(EndScene);
};



