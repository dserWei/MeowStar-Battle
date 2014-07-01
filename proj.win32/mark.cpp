#include "mark.h"
#include "menu.h"

mark::mark()
{
}

mark::~mark()
{
}

void mark::onEnter()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCNode::onEnter();
	if(!ispaused)
	{
		this->setContentSize(size);

		bits = CCArray::createWithCapacity(5);

		CCSprite* body = CCSprite::create("score.png");
		body->setPosition(ccp(40,size.height-15));
		body->setScale(0.5);
		this->addChild(body);

		for(int i =0; i<5; i++)
		{
			CCSprite* num = CCSprite::create("shu.png");
			num->setPosition(ccp(size.width/2-(i+1)*15,size.height-15));
			num->setScale(0.5);
			num->setTextureRect(CCRectMake(234,0,26,31));
			bits->addObject(num);
			this->addChild(num);
		}
		bits->retain();
		score = 0;
	}
}

void mark::onExit()
{
	CCNode::onExit();
}

void mark::addnum(int num)
{
	score += num;

	CCSprite* origin = CCSprite::create("shu.png");
	CCTexture2D* tex = origin->getTexture();

	int tmp = score % 10;
	if(tmp>0)
	{
		((CCSprite*)bits->objectAtIndex(0))->setTexture(tex);
		((CCSprite*)bits->objectAtIndex(0))->setTextureRect(CCRectMake((tmp-1)*26,0,26,31));
	}

	tmp = (score % 100) / 10;
	if(tmp>0)
	{
		((CCSprite*)bits->objectAtIndex(1))->setTexture(tex);
		((CCSprite*)bits->objectAtIndex(1))->setTextureRect(CCRectMake((tmp-1)*26,0,26,31));
	}

	tmp = (score % 1000) / 100;
	if(tmp>0)
	{
		((CCSprite*)bits->objectAtIndex(2))->setTexture(tex);
		((CCSprite*)bits->objectAtIndex(2))->setTextureRect(CCRectMake((tmp-1)*26,0,26,31));
	}

	tmp = (score % 10000) / 1000;
	if(tmp>0)
	{
		((CCSprite*)bits->objectAtIndex(3))->setTexture(tex);
		((CCSprite*)bits->objectAtIndex(3))->setTextureRect(CCRectMake((tmp-1)*26,0,26,31));
	}

	tmp = (score % 100000) /10000;
	if(tmp>0)
	{
		((CCSprite*)bits->objectAtIndex(4))->setTexture(tex);
		((CCSprite*)bits->objectAtIndex(4))->setTextureRect(CCRectMake((tmp-1)*26,0,26,31));
	}

}