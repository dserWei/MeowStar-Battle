#include "cat.h"
#include "fishbone.h"
#include "game.h"
#include "menu.h"

cat::cat()
{
}

cat::~cat()
{
}

void cat::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	if(!ispaused)
	{
		this->setContentSize(CCSizeMake(85,90));

		CCSprite* body = CCSprite::create("catBody1.png");
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("catBody1.png");
		animation->addSpriteFrameWithFileName("catBody2-4.png");
		animation->addSpriteFrameWithFileName("catBody3.png");
		animation->addSpriteFrameWithFileName("catBody2-4.png");
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);
		body->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
		this->addChild(body);

		CCSprite* tail = CCSprite::create("catTail.png");
		tail->setAnchorPoint(ccp(0.5,1));
		tail->setPosition(ccp(-5,-29));
		tail->setScale(0.5);
		tail->setRotation(20);
		tail->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCRotateBy::create(0.5,-40),CCRotateBy::create(0.5,40),NULL)));
		this->addChild(tail);

		lhand = CCSprite::create("catHand1.png");
		lhand->setAnchorPoint(ccp(1,0.5));
		lhand->setPosition(ccp(-18,-20));
		this->addChild(lhand);

		rhand = CCSprite::create("catHand2.png");
		rhand->setAnchorPoint(ccp(0,0.5));
		rhand->setPosition(ccp(18,-20));
		this->addChild(rhand);

		offset = ccp(0,0);

		iscontrol = false;

		this->schedule(schedule_selector(cat::bullet),0.5f);
	}
}

void cat::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

void cat::touchDelegateRetain()
{
	this->retain();
}

void cat::touchDelegateRelease()
{
	this->release();
}

bool cat::ccTouchBegan(CCTouch* touch, CCEvent* et)
{
	if(((game*)this->getParent())->getover())return false;
	if(!containsTouchLocation(touch))return false;
	else
	{
		iscontrol = true;
		CCPoint tPoint = touch->getLocationInView();
		tPoint = CCDirector::sharedDirector()->convertToGL(tPoint);

		offset.x = tPoint.x - this->getPosition().x;
		offset.y = tPoint.y - this->getPosition().y;

		return true;
	}
}

void cat::ccTouchMoved(CCTouch* touch, CCEvent* et)
{
	CCPoint tPoint = touch->getLocationInView();
	tPoint = CCDirector::sharedDirector()->convertToGL(tPoint);

	float curX = tPoint.x - offset.x;
	float curY = tPoint.y - offset.y;

	if(curX<this->getPosition().x)
	{
		lhand->setFlipY(true);
		rhand->setFlipY(false);
	}
	else
	{
		lhand->setFlipY(false);
		rhand->setFlipY(true);
	}

	this->setPosition(curX,curY);
}

void cat::ccTouchEnded(CCTouch* touch, CCEvent* et)
{
	if(iscontrol)iscontrol = false;
	lhand->setFlipY(false);
	rhand->setFlipY(false);
}

void cat::bullet(float sender)
{
	if(iscontrol)
	{
		CCPoint cp = this->getPosition();
		game* g = (game*)this->getParent();
		g->releaseFishbone(cp.x, cp.y+30);
	}
}

bool cat::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(this->convertTouchToNodeSpaceAR(touch));
}

CCRect cat::rect()
{
	return CCRectMake(-85/2,-90/2,85,90);
}