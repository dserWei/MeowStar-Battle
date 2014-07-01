#ifndef _GAME_MARK_H
#define _GAME_MARK_H

#include "cocos2d.h"
using namespace cocos2d;

class mark: public CCNode
{
public:
	mark(void);
	~mark(void);

	virtual void onEnter();
	virtual void onExit();

	void addnum(int num);

private:
	CCArray* bits;
	int score;
	
 };

#endif