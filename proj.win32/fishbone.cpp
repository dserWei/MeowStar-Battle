#include "fishbone.h"
#include "menu.h"

fishbone::fishbone()
{
}

fishbone::~fishbone()
{
}

void fishbone::onEnter()
{
	CCNode::onEnter();
	if(!ispaused)
	{
		this->setContentSize(CCSizeMake(21,52));

		CCSprite* body = CCSprite::create("YuGuZD.png");
		this->addChild(body);
	}
}

void fishbone::onExit()
{
	CCNode::onExit();
}

bool fishbone::getIsVisible()
{
	return isvisible;
}

void fishbone::setIsVisible()
{
	isvisible = true;
	this->setVisible(isvisible);
}

void fishbone::setIsNotVisible()
{
	isvisible = false;
	this->setVisible(isvisible);
}