/*#include "cocos2d.h"

using namespace cocos2d;

class cat: public CCNode, public CCTargetedTouchDelegate
{
public:
	CCSprite* lhand;
	CCSprite* rhand;
	CCPoint* offset;
	bool iscontrol;
	
	cat(void);
	virtual ~cat(void);

	void bullet();

	CCRect rect();

	virtual void onEnter();
	virtual void onExit();

	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual bool ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual bool ccTouchEnded(CCTouch* touch, CCEvent* event);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();
}*/