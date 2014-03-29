/*#include "cat.h"

void cat::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(85,90));
	
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);

	CCSprite*  mainSprite = CCSprite::create("catBody1.png");

	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("catBody1.png");
	animation->addSpriteFrameWithFileName("catBody2-4.png");
	animation->addSpriteFrameWithFileName("catBody3.png");
	animation->addSpriteFrameWithFileName("catBody2-4.png");
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);

	mainSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

	this->addChild(mainSprite);

	CCSprite* tail = CCSprite::create("catTail.png");
	tail->setAnchorPoint(ccp(0.5,1));
	tail->setPosition(ccp(-5,-29));
	tail->setScale(0.5);
	tail->setRotation(20);
	tail->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCRotateBy::create(0.5,-40),CCRotateBy::create(0.5,40),NULL)));
	this->addChild(tail);

	lhand = CCSprite::create("catHand1.png");
	lhand->setAnchorPoint(ccp(1,0.5));
	lhand->setPosition(ccp(-18.-20));
	this->addChild(lhand);
	rhand = CCSprite::create("catHand2.png");
	rhand->setAnchorPoint(ccp(0,0.5));
	rhand->setPosition(ccp(18-20));
	this->addChild(rhand);
	
	offset = ccp(0,0);
	iscontrol = false;

	schedule(schedule_selector(cat::bullet),1.0f);
}
*/