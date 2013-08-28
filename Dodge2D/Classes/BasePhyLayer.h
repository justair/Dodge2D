//
//  BasePhyLayer.h
//  Dodge2D
//
//  Created by 赵 立元 on 13-8-26.
//
//

#ifndef __Dodge2D__BasePhyLayer__
#define __Dodge2D__BasePhyLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "B2Sprite.h"

class BasePhyLayer : public CCLayer
{
public:
    BasePhyLayer(){};
    
    virtual ~BasePhyLayer(){};
    
    virtual void onCrash(B2Sprite *first,B2Sprite *sencand){};
    
};

#endif /* defined(__Dodge2D__BasePhyLayer__) */
