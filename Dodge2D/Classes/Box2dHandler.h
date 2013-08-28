//
//  Box2dHandler.h
//  dodge
//
//  Created by 赵 立元 on 13-8-23.
//
//

#ifndef __dodge__Box2dHandler__
#define __dodge__Box2dHandler__

#include <iostream>

#include "Box2D/Box2D.h"
#include "B2Sprite.h"
#include "cocos2d.h"
#include "EnumType.h"
#include <time.h>
#include <set>
#include <algorithm>
#include "BaseControl.h"
#include "GLES-Render.h"
using namespace cocos2d;
USING_NS_CC;
class Box2dHandler : public CCNode, public b2ContactListener,public BaseControl
{
private:
	GLESDebugDraw* m_debugDraw;
    
    typedef pair<b2Fixture*, b2Fixture*> MyContact;
    set<MyContact> _contacts;
    
    bool initBox2D();
    void addBodyForSprite(B2Sprite* sprite, double density = 10.0);
    void addFixtureForSprite(B2Sprite* sprite, double density=10.0);
	void initDebugDraw();
    void dealCollisions();

public:
    
	virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    //virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    //virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    //static Box2dHandler* hander();
    bool init();
    void draw();
    void update(float dt);
    void addSelfRole(B2Sprite* self);
	void addSprite(B2Sprite* enemy);
    void removeSprite(B2Sprite* enemy);
    //  void addEnemy(B2Sprite* ememy, CCPoint direction);
    // void removeSprite(B2Sprite* node);
    // CC_SYNTHESIZE(Box2dHandlerDelegate*, m_delegate,Delegate);
	b2World *m_world;
    
	CREATE_FUNC(Box2dHandler);
};

#endif /* defined(__dodge__Box2dHandler__) */
