#include "tube.h"
#include "menu.h"

tube::tube()
{
}

tube::~tube()
{
}

void tube::onEnter()
{
	CCNode::onEnter();
	if(!ispaused)
	{
		this->setContentSize(CCSizeMake(21,52));

		CCSprite* body = CCSprite::create("DrDogZD.png");
		body->runAction(CCRepeatForever::create(CCRotateBy::create(1.0,360.0)));
		this->addChild(body,0,0);
	}
}

void tube::onExit()
{
	CCNode::onExit();
}

bool tube::getIsVisible()
{
	return isvisible;
}

void tube::setIsVisible()
{
	isvisible = true;
	this->setVisible(isvisible);
}

void tube::setIsNotVisible()
{
	isvisible = false;
	this->setVisible(isvisible);
}