#ifndef _GAME_FISHBONE_H
#define _GAME_FISHBONE_H

#include "cocos2d.h"
using namespace cocos2d;

class fishbone: public CCNode
{
public:
	fishbone(void);
	~fishbone(void);

	virtual void onEnter();
	virtual void onExit();

	bool getIsVisible();
	void setIsVisible();
	void setIsNotVisible();

private:
	bool isvisible;
};

#endif