#ifndef _GAME_CAT_H_
#define _GAME_CAT_H_

#include "cocos2d.h"

using namespace cocos2d;

class cat: public CCNode, public CCTargetedTouchDelegate
{
public:	
	cat(void);
	~cat(void);

	void bullet(float sender);

	CCRect rect();

	virtual void onEnter();
	virtual void onExit();

	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* et);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* et);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* et);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

private:
	CCSprite* lhand;
	CCSprite* rhand;
	CCPoint offset;
	bool iscontrol;

};

#endif