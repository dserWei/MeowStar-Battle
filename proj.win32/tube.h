#ifndef _GAME_TUBE_H
#define _GAME_TUBE_H

#include "cocos2d.h"
using namespace cocos2d;

class tube: public CCNode
{
public:
	tube(void);
	~tube(void);

	virtual void onEnter();
	virtual void onExit();

	bool getIsVisible();
	void setIsVisible();
	void setIsNotVisible();

private:
	bool isvisible;

};

#endif