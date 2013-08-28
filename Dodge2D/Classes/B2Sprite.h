//
//  B2Sprite.h
//  dodge
//
//  Created by 赵 立元 on 13-8-23.
//
//

#ifndef __dodge__B2Sprite__
#define __dodge__B2Sprite__

#include <iostream>

#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;
class B2Sprite :public cocos2d::CCSprite
{
public:
	static B2Sprite* spriteWithSpriteFrameName(const char* file);
    bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    
	b2Body *m_b2Body;
	void setB2Body(b2Body * body){
		m_b2Body = body;
	}
	b2Body * getB2Body(){
		return m_b2Body;
	}
    
    //CC_SYNTHESIZE(b2Body*, m_b2Body, B2Body);   //ŒÔ¿Ì ¿ΩÁµƒ°∞ŒÔÃÂ°±
    CC_SYNTHESIZE(bool, m_isDead, IsDead);      // «∑ÒÀ¿»•
    CC_SYNTHESIZE(bool, m_isAlive, IsAlive);    // «∑Ò¥ÊªÓ
    CC_SYNTHESIZE(const char*, _id, Id);
};

#endif /* defined(__dodge__B2Sprite__) */
