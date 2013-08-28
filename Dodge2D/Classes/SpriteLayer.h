//
//  SpriteLayer.h
//  dodge
//
//  Created by Justair on 13-7-31.
//
//

#ifndef __dodge__SpriteLayer__
#define __dodge__SpriteLayer__

#include <iostream>

#pragma once
//œ‡ª•“˝”√Œ Ã‚”√#ifndefΩ‚æˆ
#include "cocos2d.h"
#include "HpSprite.h"
#include "B2Sprite.h"
#include "Box2dHandler.h"
#include "BasePhyLayer.h"
#include "EnumType.h"
#include<time.h>
#include <set>
using namespace cocos2d;

class TouchLayerDelegate;
class SpriteLayer : public BasePhyLayer
{
private:
    float _speed;
    float _frame;
    float _scale;
    int _totalFlower;
    int _stage;
    B2Sprite* _myRole;//Tag = 0
    CCArray* _enemyArr;//tag = 1
    CCArray* _flowerArr;//tag = 10
    CCArray* _itemArr;//tag = 100;
    HpSprite* _hpBar;
    CCPoint _hpCcp;
    float _enemyDebuff;
    float _buff;
    CCLabelBMFont* _stageLabel;
    Box2dHandler* _box2d;
        
public:
    
    SpriteLayer();
    ~SpriteLayer(void);
    
    B2Sprite* createMovieClip(const char *picname);
    //void srand (unsigned int seed);
    void preStart();
    void createMyRole();
    void createFlower();
    void createEnemy();
    void createBubble();
    //常规碰撞测试
    //void hitTest();
    void addFlower();
    void addItem();
    void startGame(CCNode* sender);
    void showFlower(CCNode* sender);
    void showItem(CCNode* sender);
    void showCoin(CCPoint point);
    void showBomb(CCPoint point);
    void addRand(CCSprite* sprite);//º”»ÎÀÊª˙Œª÷√
    void randMove(CCSprite* role);
    void moveEnd(CCNode* sender);
    void removePs(CCNode* sender);
    void addHp(CCNode* sender);
    void addPoint(CCNode* sender);
    void removePoint(CCNode* sender);
    void revertSpeed(CCNode* sender);
    void endTime(CCNode* sender);
    void touchesEnd(CCPoint point);
    void touchesBegan(CCPoint point) ;
    CCAnimation * getMovieClip(const char *picname,float delay);
    CCSpawn * getMoveSpawn(CCSprite* sprite,CCPoint point,float speed);
    //÷ÿ–¥init
    virtual bool init();
    virtual void onCrash(B2Sprite *first,B2Sprite *sencand);
    
    //÷°≤ΩΩ¯
    void update(float dt);
    //◊‘∂®“Â∂® ±∆˜≤ΩΩ¯
    virtual void Step(CCTime dt);
    
    CREATE_FUNC(SpriteLayer);
};


#endif /* defined(__dodge__SpriteLayer__) */
