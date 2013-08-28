//
//  BaseControl.h
//  Dodge2D
//
//  Created by 赵 立元 on 13-8-26.
//
//

#ifndef __Dodge2D__BaseControl__
#define __Dodge2D__BaseControl__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "BasePhyLayer.h"

class BaseControl
{
public:
    BaseControl(){};
    
    ~BaseControl(){};
    
    virtual void setDelegate(BasePhyLayer* delegate){_delegate = delegate;};
    
    BasePhyLayer* _delegate;
};
#endif /* defined(__Dodge2D__BaseControl__) */
