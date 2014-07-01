#include "dog.h"
#include "tube.h"
#include "game.h"
#include "menu.h"

dog::dog()
{
}

dog::~dog()
{
}

void dog::onEnter()
{
	CCNode::onEnter();
	if(!ispaused)
	{
		this->setContentSize(CCSizeMake(99,111));

		body = CCSprite::create("DrDog1.png");
		this->addChild(body);

		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("DrDog1.png");
		animation->addSpriteFrameWithFileName("DrDog2.png");
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);
		body->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	
		boom = CCSprite::create("Boom1.png");
		boom->setVisible(false);
		this->addChild(boom);

		islived = true;
	}
}

void dog::onExit()
{
	CCNode::onExit();
}

void dog::die()
{
	islived = false;
	this->stopAllActions();
	body->setVisible(false);
	boom->setVisible(true);

	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("Boom1.png");
	animation->addSpriteFrameWithFileName("Boom2.png");
	animation->addSpriteFrameWithFileName("Boom3.png");
	animation->addSpriteFrameWithFileName("Boom4.png");
	animation->addSpriteFrameWithFileName("Boom5.png");
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	boom->runAction(CCSequence::create(CCAnimate::create(animation),CCCallFunc::create(this,callfunc_selector(dog::restart)),NULL));
}

void dog::restart()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	islived = true;
	boom->setVisible(false);
	body->setVisible(true);

	if(type == 0)
		this->setPosition(ccp(50, size.height+50));
	else
		this->setPosition(ccp(size.width/4 * type, size.height+50));

	this->move();
}

void dog::move()
{
	type = CCRANDOM_0_1()*4;

	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = CCPointMake(this->getPosition().x-400,330);
	bezier1.controlPoint_2 = CCPointMake(this->getPosition().x+400,280);
	bezier1.endPosition = CCPointMake(this->getPosition().x,-70);
	
	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = CCPointMake(this->getPosition().x+400,330);
	bezier2.controlPoint_2 = CCPointMake(this->getPosition().x-400,280);
	bezier2.endPosition = CCPointMake(this->getPosition().x,-70);

	switch(type)
	{
	case 0:
		this->setPosition(ccp(-50, 96*CCRANDOM_0_1()*5+60));
		this->runAction(CCSequence::create(CCMoveBy::create(2.0,ccp(400,0)),CCCallFunc::create(this,callfunc_selector(dog::restart)),NULL));
		break;
	case 1:
		this->runAction(CCSequence::create(CCBezierTo::create(6.0,bezier1),CCCallFunc::create(this,callfunc_selector(dog::restart)),NULL));
		break;
	case 2:
		this->runAction(CCSequence::create(CCBezierTo::create(6.0,bezier2),CCCallFunc::create(this,callfunc_selector(dog::restart)),NULL));
		break;
	case 3:
		this->runAction(CCSequence::create(CCMoveBy::create(3.0,ccp(0,-600)),CCCallFunc::create(this,callfunc_selector(dog::restart)),NULL));
		break;
	}
	this->schedule(schedule_selector(dog::bullet),0.6f);
}

void dog::bullet(float sender)
{
	CCPoint dp = this->getPosition();
	if(dp.y<CCDirector::sharedDirector()->getWinSize().height && islived)
	{
		game* g = (game*)this->getParent();
		g->releaseTube(dp.x, dp.y-30);
	}
}

bool dog::getlived()
{
	return islived;
}