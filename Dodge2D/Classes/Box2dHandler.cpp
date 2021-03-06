//
//  Box2dHandler.cpp
//  dodge
//
//  Created by 赵 立元 on 13-8-23.
//
//

#include "Box2dHandler.h"
#include "EventType.h"

#define PTM_RATIO 32
bool Box2dHandler::init()
{
    
	initBox2D();
    
	//initDebugDraw();
	
	this->scheduleUpdate();
    
	return true;
}

void Box2dHandler::initDebugDraw()
{
	m_debugDraw = new GLESDebugDraw( PTM_RATIO );
    m_world->SetDebugDraw(m_debugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //flags += b2Draw::e_jointBit;
    //flags += b2Draw::e_aabbBit;
    //flags += b2Draw::e_pairBit;
    //flags += b2Draw::e_centerOfMassBit;
    
	m_debugDraw->SetFlags(flags);
}

bool Box2dHandler::initBox2D()
{
	b2Vec2 gravity;
	gravity.Set(0.0f,0.0f);
	m_world = new b2World( gravity );
    
    m_world->SetAllowSleeping(true);
    m_world->SetContinuousPhysics(true);
    m_world->SetContactListener(this);
    return true;
}

void Box2dHandler::addFixtureForSprite(B2Sprite* sprite, double density)
{
    
    b2FixtureDef spriteShapeDef;
    CCSize size = sprite->getContentSize();
    
    b2PolygonShape spriteShape;
    if(sprite->getTag() == FLOWER){
        int num = 7;
        b2Vec2 verts[] = {
            b2Vec2(0.0f / PTM_RATIO, 31.6f / PTM_RATIO),
            b2Vec2(-27.5f / PTM_RATIO, 17.0f / PTM_RATIO),
            b2Vec2(-25.3f / PTM_RATIO, -18.7f / PTM_RATIO),
            b2Vec2(1.6f / PTM_RATIO, -30.8f / PTM_RATIO),
            b2Vec2(30.4f / PTM_RATIO, -11.5f / PTM_RATIO),
            b2Vec2(25.2f / PTM_RATIO, 19.1f / PTM_RATIO),
            b2Vec2(-1.0f / PTM_RATIO, 31.0f / PTM_RATIO)
        };
        spriteShape.Set(verts, num);
    }else if(sprite->getTag() == ITEM){
        int num = 4;
        b2Vec2 verts[] = {
            b2Vec2(3.6f / PTM_RATIO, 24.9f / PTM_RATIO),
            b2Vec2(-9.1f / PTM_RATIO, 24.4f / PTM_RATIO),
            b2Vec2(-34.6f / PTM_RATIO, -21.3f / PTM_RATIO),
            b2Vec2(34.9f / PTM_RATIO, -21.9f / PTM_RATIO)
        };        spriteShape.Set(verts, num);
    }else if(sprite->getTag() == ENEMY){
        int num = 7;
        b2Vec2 verts[] = {
            b2Vec2(20.4f / PTM_RATIO, 46.5f / PTM_RATIO),
            b2Vec2(-18.3f / PTM_RATIO, 44.0f / PTM_RATIO),
            b2Vec2(-31.6f / PTM_RATIO, 28.0f / PTM_RATIO),
            b2Vec2(-27.1f / PTM_RATIO, -41.4f / PTM_RATIO),
            b2Vec2(22.1f / PTM_RATIO, -42.7f / PTM_RATIO),
            b2Vec2(32.9f / PTM_RATIO, -27.0f / PTM_RATIO),
            b2Vec2(30.4f / PTM_RATIO, 32.3f / PTM_RATIO)
        };
      spriteShape.Set(verts, num);
    }else if(sprite->getTag() == SELF){
        int num = 8;
        b2Vec2 verts[] = {
            b2Vec2(30.7f / PTM_RATIO, 51.2f / PTM_RATIO),
            b2Vec2(-32.5f / PTM_RATIO, 38.9f / PTM_RATIO),
            b2Vec2(-44.2f / PTM_RATIO, 2.0f / PTM_RATIO),
            b2Vec2(-23.2f / PTM_RATIO, -19.0f / PTM_RATIO),
            b2Vec2(-5.0f / PTM_RATIO, -56.8f / PTM_RATIO),
            b2Vec2(1.4f / PTM_RATIO, -55.3f / PTM_RATIO),
            b2Vec2(17.0f / PTM_RATIO, -18.6f / PTM_RATIO),
            b2Vec2(44.6f / PTM_RATIO, 8.8f / PTM_RATIO)
        };
        spriteShape.Set(verts, num);
    }
    else{
        spriteShape.SetAsBox(size.width / PTM_RATIO/2, size.height / PTM_RATIO/2);
    }
    
    
    spriteShapeDef.shape = &spriteShape;
    
    //b2CircleShape dynamicBox;
    //dynamicBox.m_radius = 36.0f/PTM_RATIO;
    //spriteShapeDef.shape = &dynamicBox;
    
    spriteShapeDef.density = density;
    //有碰撞检测无碰撞反应
    spriteShapeDef.isSensor =true;
    
    b2Body * spriteBody = sprite->getB2Body();
    spriteBody->CreateFixture(&spriteShapeDef);
}

void Box2dHandler::addBodyForSprite(B2Sprite* sprite, double density)
{
    b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_dynamicBody;
    spriteBodyDef.position.Set(sprite->getPosition().x / PTM_RATIO,
                               sprite->getPosition().y / PTM_RATIO);
    spriteBodyDef.userData = sprite;
    
    
    b2Body *spriteBody = m_world->CreateBody(&spriteBodyDef);
    sprite->setB2Body(spriteBody);
    
    this->addFixtureForSprite(sprite,density);
}

void Box2dHandler::update(float dt)
{
    m_world->Step(dt, 8, 8);

    for(b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetUserData() != NULL) {
            B2Sprite* sprite = static_cast<B2Sprite*>(b->GetUserData());
            
            //Àı∑≈¥¶¿Ì
            /*b2PolygonShape shape = b->GetFixtureList()->GetShape();
             for each( var vec:b2Vec2 in shape->GetVertices()) {
             vec.Multiply(0.9);
             }*/
            
            if(sprite->getTag() == SELF || sprite->getTag() == ENEMY) {
                //ÕÊº“Ω«…´
			    b2Vec2 b2Position = b2Vec2(sprite->getPosition().x / PTM_RATIO,
                                           sprite->getPosition().y / PTM_RATIO);
                float32 b2Angle = -CC_DEGREES_TO_RADIANS(sprite->getRotation());
                b->SetTransform(b2Position, b2Angle);
            }
            else {
                
               // b2Vec2 pos = b->GetPosition();
                float rotation = - b->GetAngle() / 0.01745329252f ;
                //float rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
                //Õ£÷π◊‘∂Ø“∆∂Ø¬∑œﬂ
                sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
                sprite->setRotation(rotation);
            }
        }
    }
    this->dealCollisions();
}

void Box2dHandler::draw()
{
    CCNode::draw();
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    
    /*kmGLPushMatrix();  //OpenGL±£¥Ê◊¥Ã¨
    m_world->DrawDebugData();    //ªÊ÷∆µ˜ ‘Õº–Œ
    kmGLPopMatrix();*/  //OpenGLª÷∏¥◊¥Ã¨
}

void Box2dHandler::addSelfRole(B2Sprite * self){
    this->addBodyForSprite(self,1000);
    
	//  b2Body* body = self->getB2Body();
    //    b2Vec2 b2Position = b2Vec2(self->getPosition().x / PTM_RATIO,
    //      self->getPosition().y / PTM_RATIO);
    //  float32 b2Angle = -CC_DEGREES_TO_RADIANS(self->getRotation());
    
    // body->SetTransform(b2Position, b2Angle);
    //body->SetLinearVelocity(b2Vec2(self->getPosition().x * 100, self->getPosition().y * 100));
}

void Box2dHandler::addSprite(B2Sprite * sprite){
    this->addBodyForSprite(sprite,1000);
}

void Box2dHandler::removeSprite(B2Sprite * sprite){
    m_world->DestroyBody(sprite->getB2Body());
}

void Box2dHandler::BeginContact(b2Contact* contact)
{
    
    B2Sprite* spa = static_cast<B2Sprite*>(contact->GetFixtureA()
                                           ->GetBody()->GetUserData());
    B2Sprite* spb = static_cast<B2Sprite*>(contact->GetFixtureB()
                                           ->GetBody()->GetUserData());
	int ta = spa->getTag();
    int tb = spb->getTag();
    
    if(ta == tb)
        return;
    
	//只记录玩家的碰撞
    MyContact myContact;
	if(ta == 0){
         MyContact myContact(contact->GetFixtureA(), contact->GetFixtureB());
        _contacts.insert(myContact);
        //CCNotificationCenter::sharedNotificationCenter()->postNotification(CrashEvent, spb);
	}else if(tb == 0){
         MyContact myContact(contact->GetFixtureB(), contact->GetFixtureA());
        _contacts.insert(myContact);
       // CCNotificationCenter::sharedNotificationCenter()->postNotification(CrashEvent, spa);
	}
    
}

void Box2dHandler::EndContact(b2Contact* contact)
{

}

void Box2dHandler::dealCollisions(){
    set<MyContact>::iterator it;
  //  CCLog("%d",std::count(_contacts.begin(),_contacts.end(),NULL));
    for(it = _contacts.begin();it != _contacts.end();it++){
        //CCNotificationCenter::sharedNotificationCenter()->postNotification(CrashEvent,crushS;et);
        B2Sprite *myRole = static_cast<B2Sprite*>(it->first->GetBody()->GetUserData());
        B2Sprite *other = static_cast<B2Sprite*>(it->second->GetBody()->GetUserData());
        _delegate->onCrash(myRole, other);
    }
     _contacts.clear();
}
