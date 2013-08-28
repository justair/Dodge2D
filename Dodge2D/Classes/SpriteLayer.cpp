//
//  SpriteLayer.cpp
//  dodge
//
//  Created by Justair on 13-7-31.
//
//
#include "SpriteLayer.h"
#include "EndScene.h"
#include "NextScene.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
#include "EventType.h"
using namespace CocosDenshion;
USING_NS_CC;

SpriteLayer::SpriteLayer()
{
	//≥ı ºªØπÿø®
	_stage = g_stage;
    
	_totalFlower = 0;
	_frame = float(1)/30;
	_scale = g_scale;
	_speed = 5.0 * 60;
	_buff = 1.0;
	_enemyDebuff = 1.0;
    
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	_hpCcp = ccp(size.width - 275,size.height - 50);
    
    
	_flowerArr = CCArray::create();
	_flowerArr->retain();
    
	_enemyArr = CCArray::create();
	_enemyArr->retain();
    
	_itemArr = CCArray::create();
	_itemArr->retain();
}

SpriteLayer::~SpriteLayer(void)
{
	_box2d->removeAllChildren();
	_box2d->cleanup();
	_box2d->onExit();
	_flowerArr->release();
	_enemyArr->release();
    _itemArr->release();
}

bool SpriteLayer::init()
{
	bool b = false;
	do{
		_box2d = Box2dHandler::create();
		//_box2d->setSpriteLayer(&this);
		this->addChild(_box2d,20000);
        _box2d->setDelegate(this);
		
		_hpBar = HpSprite::create();
		_hpBar->setPosition(_hpCcp);
		this->addChild(_hpBar,9999);
        
		//ÀÊª˙÷÷◊”
		srand((unsigned)time(NULL));
		createMyRole();
		this->schedule(schedule_selector(SpriteLayer::update));
		//this->scheduleUpdate();
        
        //CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SpriteLayer::onCrash), CrashEvent,NULL);
        
		preStart();
        
		b = true;
	}while(0);
    
	return b;
}


void SpriteLayer::preStart()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    char stage[10];
    sprintf(stage,"STAGE:%d",g_stage);
    _stageLabel =  CCLabelBMFont::create(stage, "Abadi40.fnt");
    _stageLabel->setScale(1);
    _stageLabel->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(_stageLabel,5000);
    
    CCFadeIn* fadeIn = CCFadeIn::create(.5);
    CCDelayTime *time = CCDelayTime::create(1);
    CCFadeOut* fadeOut = CCFadeOut::create(.5);
    CCCallFuncN* startGame = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::startGame));
    CCAction* action = CCSequence::create(fadeIn,time,fadeOut,startGame,NULL);
    _stageLabel->runAction(action);
}


void SpriteLayer::startGame(CCNode *sender)
{
	CCLabelBMFont *label = dynamic_cast<CCLabelBMFont*>(sender);
	label->stopAllActions();
	this->removeChild(label);
    
	createFlower();
	createEnemy();
	createBubble();
}

void SpriteLayer::Step(CCTime dt)
{
	CCLog("Step");
}


//******************** ¥¥Ω®÷˜Ω« *************************
void SpriteLayer::createMyRole()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	_myRole = createMovieClip("spriteZheng");
	_myRole ->setPosition(ccp(size.width/2,size.height/2));
	float z = (1 - float(size.height/2)/size.height)*.3 + .7;
	_myRole ->setScale(_scale * z);
	
	this->addChild(_myRole, 800,1);
	_myRole ->setTag(SELF);
	_box2d->addSelfRole(_myRole);
	
}

//********************¥¥Ω®œ ª®***************************
void SpriteLayer::createFlower()
{
	for(int i = 0;i<3;i++){
		addFlower();
	}
}

void SpriteLayer::addFlower()
{
	CCDelayTime *time = CCDelayTime::create(0.2);
	CCCallFuncN* end = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::showFlower));
	CCAction* action = CCSequence::create(time,end,NULL);
	this->runAction(action);
}

void SpriteLayer::showFlower(CCNode* sender)
{
	B2Sprite* flower = createMovieClip("flower");
	_flowerArr->addObject(flower);
	addRand(flower);
	//flower->setScale(flower->getScale() * .8);
	_totalFlower++;
	this->addChild(flower,100,_totalFlower);
	flower ->setTag(FLOWER);
    /*char id[10];
    sprintf(id,"f_:%d",100);
    flower->setId(id);*/
	_box2d->addSprite(flower);
}

//**************************** ¥¥Ω®µ¿æﬂ *******************************
void SpriteLayer::addItem()
{
	CCDelayTime *time = CCDelayTime::create(0.2);
	CCCallFuncN* end = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::showItem));
	CCAction* action = CCSequence::create(time,end,NULL);
	this->runAction(action);
}

void SpriteLayer::showItem(CCNode* sender)
{
	B2Sprite* item = createMovieClip("mogu");
	
	_itemArr->addObject(item);
	addRand(item);
	this->addChild(item,500);
	item ->setTag(ITEM);
    _box2d->addSprite(item);
}

//*********************¥¥Ω®’¬”„**************************************
void SpriteLayer::createEnemy()
{
	for(int i = 0;i<_stage;i++){
		B2Sprite* enemy = createMovieClip("zhangyu");
		
		_enemyArr->addObject(enemy);
		addRand(enemy);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		if(i%2 == 0)
			enemy->setPositionX(0);
		else
			enemy->setPositionX(size.width);
		this->addChild(enemy,200,i);
		enemy ->setTag(ENEMY);
        
		randMove(enemy);
        
		_box2d->addSprite(enemy);
	}
}

//********************* ¥¥Ω®ÕÊº“∂Øª≠Ω«…´ **********************************
B2Sprite* SpriteLayer::createMovieClip(const char *picname)
{
	//_myRole=CCSprite::create("zhangyu.png",CCRectMake(0,0,103,146));
	char keyname[100];
	sprintf(keyname,"%s_0001.png",picname);
	B2Sprite *role = static_cast<B2Sprite*>(B2Sprite::createWithSpriteFrameName(keyname));
	//B2Sprite *role = static_cast<B2Sprite*>(B2Sprite::create());
    
	//º”»Î∂Øª≠
	CCAnimation *animation=getMovieClip(picname,_frame);
	//≤•∑≈“ª¥Œ
	//CCAnimate * animate = CCAnimate::create(animation);
	//—≠ª∑≤•∑≈
	CCRepeatForever *repeat=CCRepeatForever::create(CCAnimate::create(animation));
	role->runAction(repeat);
    
	return role;
}

CCAnimation *SpriteLayer::getMovieClip(const char *picname,float delay)
{
    char keyname[100];//∫Ø ˝∑µªÿ∫Û◊‘∂Ø Õ∑≈
    
    CCArray* animFrames = CCArray::create();
    //œ¬±Í¥”1ø™ º
    int i = 1;
    do {
        sprintf(keyname,"%s_%04d.png",picname,i);//√¸√˚∏Ò ΩŒ™xxx.1.png
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(keyname);
        if (frame) {
            animFrames->addObject(frame);
        }else {  //»Áπ˚ªÒ»°≤ªµΩ÷°æÕ÷§√˜∂Øª≠÷°Ω· ¯¡À
            break;
        }
    } while (++i);
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,delay);
    return animation;
}

//*************************** ¥¥Ω®“∆∂Ø∂Øª≠ **************************
CCSpawn * SpriteLayer::getMoveSpawn(CCSprite* sprite,CCPoint point,float speed){
	CCPoint spriteCcp = sprite->getPosition();
    
	//“∆∂Ø
	float distance = sqrt((point.x - spriteCcp.x)*(point.x - spriteCcp.x) + (point.y - spriteCcp.y)*(point.y - spriteCcp.y));
	float time = distance / speed;
	
	CCMoveTo * move =  CCMoveTo::create(time,
                                        ccp(point.x,point.y));
	CCEaseSineInOut* ease = CCEaseSineInOut::create(move);
	//_myRole->runAction(ease);
    
	//…Ó∂»øÿ÷∆
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int h = size.height;
	float z = (1 - float(point.y)/h)*.3 + .7;
	CCScaleTo *scale = CCScaleTo::create(time ,_scale * z  ,_scale * z);;
	
	CCSpawn * action = CCSpawn::create(ease,scale,NULL);
    
	return action;
}

//********************************ÀÊª˙Œª÷√********************************
void SpriteLayer::addRand(CCSprite* sprite)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int w = size.width;
	int h = size.height;
	int x = rand()%w;
	int y = rand()%h;
	float z = (1 - float(y)/h)*.3+.7;
	sprite->setPosition(ccp(x,y));
    
	sprite->setScale(.01);
	CCScaleTo *scale = CCScaleTo::create(.5,_scale * z,_scale * z);
	sprite->runAction(scale);
}

//***************************** ÀÊª˙“∆∂Ø **********************************8
void SpriteLayer::randMove(CCSprite* sprite)
{
	//sprite->stopAllActions();
    
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int w = size.width;
	int h = size.height;
    
	CCPoint point = ccp(rand()%w,rand()%h);
    
	sprite->setScaleX(abs(sprite->getScaleX()));
	CCSpawn * move = getMoveSpawn(sprite,point,_speed * g_enemySpeedAddition * _enemyDebuff);
    
	CCCallFuncN* end = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::moveEnd));
    
	CCAction* action = CCSequence::create(move,end,NULL);
    
	sprite->runAction(action);
}

void SpriteLayer::moveEnd(CCNode* sender)
{
	this->randMove(dynamic_cast<CCSprite*>(sender));
}

//¥¥Ω®∆¯≈›
void SpriteLayer::createBubble()
{
	CCParticleSystem * particle = CCParticleSnow::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("pao_0001.png"));
	particle->setStartSize(20);
	particle->setGravity(ccp(20,50));
	particle->setPosition(-10,-10);
	particle->setLife(5);
	particle->setEmissionRate(2);
	this->addChild(particle,10000);
    
	CCParticleSystem * particle2 = CCParticleSnow::create();
	particle2->setTexture(CCTextureCache::sharedTextureCache()->addImage("pao_0001.png"));
	particle2->setStartSize(15);
	particle2->setGravity(ccp(10,25));
	particle2->setPosition(-10,-10);
	particle2->setLife(5);
	particle2->setEmissionRate(2);
	this->addChild(particle2,0);
}

//********************** ÷°ºÏ≤‚ *****************************
void SpriteLayer::update(float dt)
{
	//CCLog("update");
	//hitTest();
	if(_hpBar->isFull()){
		//π˝πÿ
		NextScene* next = NextScene::create();
		CCDirector::sharedDirector()->replaceScene(next);
	}
}

/*void SpriteLayer::hitTest()
{
	CCRect myRect =  _myRole->boundingBox();
	//≈–∂œÃıº˛…æ≥˝ ±,◊Ó∫√ƒ‹πªƒÊœÚ±È¿˙…æ≥˝,’‚—˘≤ªª·¬©µÙ»Œ∫Œ‘™Àÿ
	for (int i = _flowerArr->count()-1; i>=0 ; --i)
	{
		CCSprite* flower=(CCSprite*)_flowerArr->objectAtIndex(i);
		
		bool isHit = myRect.intersectsRect(flower->boundingBox());
		if (isHit)
		{
            showCoin(flower->getPosition());
            _flowerArr->removeObject(flower);
            this->removeChild(flower);
            // flower->release();
            addFlower();
            //“ª∂®∏≈¬ µÙ¬‰ºıÀŸµ¿æﬂ
            if(rand()%100 < g_dropRate){
                addItem();
            }
		}
	}
    
	for (int i = _enemyArr->count()-1; i>=0 ; --i)
	{
		CCSprite* enemy=(CCSprite*)_enemyArr->objectAtIndex(i);
		
		bool isHit = myRect.intersectsRect(enemy->boundingBox());
		if (isHit)
		{
			EndScene* end = EndScene::create();
			CCDirector::sharedDirector()->replaceScene(end);
		}
	}
    
	for (int i = _itemArr->count()-1; i>=0 ; --i)
	{
		CCSprite* item=(CCSprite*)_itemArr->objectAtIndex(i);
		
		bool isHit = myRect.intersectsRect(item->boundingBox());
		if (isHit)
		{
            showBomb(item->getPosition());
            _itemArr->removeObject(item);
            this->removeChild(item);
            _enemyDebuff = _enemyDebuff * .5;
            
			CCDelayTime *revertTime = CCDelayTime::create(5);
			CCCallFuncN* revertSpeed = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::revertSpeed));
			CCAction* revertAction = CCSequence::create(revertTime,revertSpeed,NULL);
			this->runAction(revertAction);
		}
	}
}*/

//************************** µ√∑÷–ßπ˚ **************************
void SpriteLayer::showCoin(CCPoint point)
{
    
	CCParticleSystem * particle = CCParticleSun::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("pao_0001.png"));
	particle->setGravity(ccp(0,0));
	particle->setLife(.8);
	particle->setStartSize(20);
	particle->setEndSize(60);
	particle->setEmissionRate(60);
	particle->setPosition(point);
	this->addChild(particle,10000);
    
	CCMoveTo *move = CCMoveTo::create(1.2,ccp(_hpCcp.x+18,_hpCcp.y+18));
	CCEaseSineIn* ease = CCEaseSineIn::create(move);
    
	CCDelayTime *time = CCDelayTime::create(.8);
	CCScaleTo* scale = CCScaleTo::create(.5,.1,.1);
	CCCallFuncN* addHp = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::addHp));
	CCCallFuncN* endPs = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::removePs));
    
	CCAction* action = CCSequence::create(ease,time,scale,addHp,endPs,NULL);
    
	particle->runAction(action);
    
	char keyname[100];
	CCLabelBMFont* label = CCLabelBMFont::create("the string", "Abadi40.fnt");
	label->setScale(.6);
	sprintf(keyname,"+%d",(int)(100*_buff));
	label->setString(keyname);
	label->setPosition(point);
	this->addChild(label,10000);
	CCMoveTo *pointMove = CCMoveTo::create(1,ccp(point.x,point.y+50));
	CCFadeOut *pointOut = CCFadeOut::create(.5);
	CCCallFuncN* addPoint = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::addPoint));
	CCCallFuncN* endPoint = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::removePoint));
    
	CCAction* pointAction = CCSequence::create(addPoint,pointMove,pointOut,endPoint,NULL);
    
	label->runAction(pointAction);
	SimpleAudioEngine::sharedEngine()->playEffect("pick.mp3");
}

void SpriteLayer::addHp(CCNode * sender)
{
	_hpBar->add(1);
}

void SpriteLayer::removePs(CCNode * sender)
{
	CCParticleSystem *particle = dynamic_cast<CCParticleSystem*>(sender);
	particle->stopAllActions();
	this->removeChild(particle);
}

void SpriteLayer::addPoint(CCNode * sender)
{
	_buff *= 2;
	CCDelayTime* timeDown = CCDelayTime::create(5);
	CCCallFuncN* endTimeFun = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::endTime));
	CCSequence *resetBuffAction = CCSequence::create(timeDown,endTimeFun,NULL);
	this->runAction(resetBuffAction);
	
	_hpBar->addPoint((int)(100 * _buff));
}

void SpriteLayer::removePoint(CCNode * sender)
{
	CCLabelBMFont *label = dynamic_cast<CCLabelBMFont*>(sender);
	label->stopAllActions();
	this->removeChild(label);
}

void SpriteLayer::endTime(CCNode * sender)
{
	_buff = _buff/2;
	CCLog("%f",_buff);
}

void SpriteLayer::revertSpeed(CCNode * sender)
{
	_enemyDebuff = _enemyDebuff*2;
}

void SpriteLayer::showBomb(CCPoint point)
{
	CCParticleSystem * particle = CCParticleGalaxy::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("pao_0001.png"));
	//particle->setLife(.1);
	particle->setStartSize(40);
	particle->setEndSize(20);
	particle->setEmissionRate(60);
	particle->setPosition(point);
	this->addChild(particle,10000);
    
	CCDelayTime *time = CCDelayTime::create(5);
	CCScaleTo* scale = CCScaleTo::create(.5,.1,.1);
	CCCallFuncN* endPs = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::removePs));
    
	CCAction* action = CCSequence::create(time,scale,endPs,NULL);
    
	particle->runAction(action);
	SimpleAudioEngine::sharedEngine()->playEffect("jiansu.mp3");
    
}



//玩家角色碰撞处理
void SpriteLayer::onCrash(B2Sprite *first,B2Sprite *sencand)
{
    CCLog("---%d",sencand->getTag());
    
    
    switch (sencand->getTag()) {
        case FLOWER:
            showCoin(sencand->getPosition());
            addFlower();
            if(rand()%100 < g_dropRate){
                addItem();
            }
            _flowerArr->removeObject(sencand);
            _box2d->removeSprite(sencand);
            this->removeChild(sencand);
            break;
        
        case ITEM:
            showBomb(sencand->getPosition());
            _itemArr->removeObject(sencand);
            _box2d->removeSprite(sencand);
            this->removeChild(sencand);
            _enemyDebuff = _enemyDebuff * .5;
            CCDelayTime *revertTime = CCDelayTime::create(5);
            CCCallFuncN* revertSpeed = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::revertSpeed));
            CCAction* revertAction = CCSequence::create(revertTime,revertSpeed,NULL);
            this->runAction(revertAction);
            break;
            
        case ENEMY:
            EndScene* end = EndScene::create();
            CCDirector::sharedDirector()->replaceScene(end);
            break;
            
        default:
            break;
    }
    
    /*if (sencand->getTag() == FLOWER) {
        showCoin(sencand->getPosition());
        addFlower();
        if(rand()%100 < g_dropRate){
            addItem();
        }
        _flowerArr->removeObject(sencand);
        _box2d->removeSprite(sencand);
        this->removeChild(sencand);
    }else if (sencand->getTag() == ITEM) {
        showBomb(sencand->getPosition());
        _itemArr->removeObject(sencand);
        _box2d->removeSprite(sencand);
        this->removeChild(sencand);
        _enemyDebuff = _enemyDebuff * .5;
        CCDelayTime *revertTime = CCDelayTime::create(5);
        CCCallFuncN* revertSpeed = CCCallFuncN::create(this,callfuncN_selector(SpriteLayer::revertSpeed));
        CCAction* revertAction = CCSequence::create(revertTime,revertSpeed,NULL);
        this->runAction(revertAction);
    }else if(sencand->getTag() == ENEMY) {
        EndScene* end = EndScene::create();
        CCDirector::sharedDirector()->replaceScene(end);
    }*/
}


// ¬º˛¥˙¿Ì
class TouchLayerDelegate
{
public:
    virtual void touchesEnd(CCPoint point) = 0;
    virtual void touchesBegan(CCPoint point) = 0;
};
void SpriteLayer::touchesEnd(CCPoint point)
{
    // CCLog("%f %f", point.x, point.y);
    //this->fire(point);
}
void SpriteLayer::touchesBegan(CCPoint point)
{
	_myRole->stopAllActions();
    
	CCPoint myCcp = _myRole->getPosition();
	
	CCAnimation *movieClip;
	if(point.y > myCcp.y)
		movieClip = getMovieClip("spriteFan",_frame);
	else
		movieClip = getMovieClip("spriteZheng",_frame);
    
	//—≠ª∑≤•∑≈∂Øª≠
	CCRepeatForever *repeatMovie=CCRepeatForever::create(CCAnimate::create(movieClip));
	//_myRole->stopActionByTag(2);
	_myRole->runAction(repeatMovie);
    
	CCFlipX* flipX=CCFlipX::create(true);
	if(point.x > myCcp.x)
		flipX=CCFlipX::create(true);
	else
		flipX=CCFlipX::create(false);
	_myRole->runAction(flipX);
    
	CCSpawn * move = getMoveSpawn(_myRole,point,_speed * g_selfSpeedAddition);
	_myRole->runAction(move);
}
