#include "game.h"
#include "menu.h"
#include "math.h"

CCScene* game::scene()
{
	CCScene* scene = CCScene::create();

	game* layer = game::create();

	scene->addChild(layer);

	return scene;
}

bool game::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//背景
	bg1 = CCSprite::create("bg.png");
	bg1->setAnchorPoint(ccp(0,0));
	bg1->setPosition(ccp(0,0));
	bg1->setScale(0.5);
	this->addChild(bg1,0,0);

	bg2 = CCSprite::create("bg.png");
	bg2->setAnchorPoint(ccp(0,0));
	bg2->setPosition(ccp(0,size.height));
	bg2->setScale(0.5);
	this->addChild(bg2,0,1);

	//返回菜单
	CCMenuItemImage* backItem = CCMenuItemImage::create("backA.png","backB.png",this,menu_selector(game::backCallback));
	backItem->setPosition(ccp(size.width-20,size.height-20));
	backItem->setScale(0.5);

	backMenu = CCMenu::create(backItem,NULL);
	backMenu->setPosition(ccp(0,0));
	this->addChild(backMenu,1,2);

	//生命值
	CCSpriteBatchNode* blood = CCSpriteBatchNode::create("cat.png");
	blood1 = CCSprite::create("cat.png");
	blood1->setPosition(ccp(20,20));
	blood1->setScale(0.2f);
	blood->addChild(blood1);
	blood2 = CCSprite::create("cat.png");
	blood2->setPosition(ccp(50,20));
	blood2->setScale(0.2f);
	blood->addChild(blood2);
	blood3 = CCSprite::create("cat.png");
	blood3->setPosition(ccp(80,20));
	blood3->setScale(0.2f);
	blood->addChild(blood3);
	this->addChild(blood,1,3);

	//分数
	mk = new mark();
	this->addChild(mk,1,4);

	//主角
	hero = new cat();
	hero->setPosition(ccp(size.width/2,-50));
	hero->setScale(0.5);
	hero->runAction(CCMoveBy::create(0.5,ccp(0,150)));
	this->addChild(hero,2,5);

	//敌人
	dogs = CCArray::createWithCapacity(3);
	for(int i = 0; i<3; i++)
	{
		int type = i+1;
		dog* enemy = new dog();
		enemy->setPosition(size.width/4*type,size.height+50);
		enemy->setScale(0.5);
		enemy->move();
		dogs->addObject(enemy);
		this->addChild(enemy,2,6);
	}
	dogs->retain();

	//鱼骨子弹
	fishbones = CCArray::createWithCapacity(5);
	for(int i = 0; i<5; i++)
	{
		fishbone* fb = new fishbone();
		fb->setScale(0.5);
		fb->setIsNotVisible();
		fishbones->addObject(fb);
		this->addChild(fb,3,7);
	}
	fishbones->retain();

	//试管子弹
	tubes = CCArray::createWithCapacity(10);
	for(int i = 0; i<10; i++)
	{
		tube* tb = new tube();
		tb->setScale(0.5);
		tb->setIsNotVisible();
		tubes->addObject(tb);
		this->addChild(tb,3,8);
	}
	tubes->retain();

	//结束提示与菜单
	over = CCSprite::create("gameover.png");
	over->setPosition(ccp(size.width/2,size.height/2+70));
	over->setScale(0.5);
	over->setVisible(false);
	this->addChild(over,4,9);

	CCMenuItemImage* back = CCMenuItemImage::create("back1.png","back2.png",this,menu_selector(game::backCallback));
	back->setPosition(ccp(size.width/2,size.height/2-30));
	back->setScale(0.5);
	
	Back = CCMenu::create(back,NULL);
	Back->setPosition(ccp(0,0));
	Back->setEnabled(false);
	Back->setVisible(false);
	this->addChild(Back,4,10);

	ishurt = false;
	isover = false;
	ispaused = false;
	life = 3;

	this->scheduleUpdate();

	return true;
}

void game::update(float time)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//背景移动
	bg1->setPosition(ccp(bg1->getPosition().x,bg1->getPosition().y - 3));
	bg2->setPosition(ccp(bg2->getPosition().x,bg2->getPosition().y - 3));

	if(bg2->getPosition().y < 0)
		bg1->setPosition(ccp(bg1->getPosition().x,bg2->getPosition().y + size.height));
	if(bg1->getPosition().y < 0)
		bg2->setPosition(ccp(bg2->getPosition().x,bg1->getPosition().y + size.height));

	//碰撞检测
	if(!isover)
	{
		CCPoint hp = hero->getPosition();

		for(int i = 0; i<3; i++)
		{
			dog* enemy = (dog*)dogs->objectAtIndex(i);
			CCPoint ep = enemy->getPosition();
		
			//猫与狗
			if(!ishurt && enemy->getlived() && isCollided(hp,ep,21,22.5,21,28))
			{
				enemy->die();
				hurt();
			}

			//鱼骨子弹与狗
			for(int j = 0; j<5; j++)
			{
				fishbone* fb = (fishbone*)fishbones->objectAtIndex(j);
				CCPoint fp = fb->getPosition();
				if(enemy->getlived() && fb->getIsVisible() && isCollided(fp,ep,5,13,21,28))
				{
					enemy->die();
					mk->addnum(CCRANDOM_0_1()*200);
					fb->stopAllActions();
					fb->setIsNotVisible();
					break;
				}
			}
		}

		//猫与试管子弹
		for(int k = 0; k<10; k++)
		{
			tube* tb = (tube*)tubes->objectAtIndex(k);
			CCPoint tp = tb->getPosition();
			if(!ishurt && tb->getIsVisible() && isCollided(hp,tp,21,22.5,5,13))
			{
				hurt();
				tb->stopAllActions();
				tb->setIsNotVisible();
				break;
			}
		}
	}

}

void game::onEnter()
{
	CCLayer::onEnter();
}

void game::onExit()
{
	CCLayer::onExit();
}

void game::backCallback(CCObject* sender)
{
	ispaused = true;

	CCDirector::sharedDirector()->pushScene(menu::scene());
}

bool game::getover()
{
	return isover;
}

void game::setover()
{
	isover = true;

	over->setVisible(true);
	over->setScale(0);
	over->runAction(CCScaleTo::create(0.5,0.5));

	Back->setVisible(true);
	Back->setEnabled(true);
	Back->setScale(0);
	Back->runAction(CCScaleTo::create(0.5,1));
	backMenu->setEnabled(false);
	backMenu->setVisible(false);
}

bool game::isCollided(CCPoint p1, CCPoint p2, int h1,int w1, int h2, int w2)
{
	return (abs(p1.x - p2.x)<(w1 + w2) && abs(p1.y - p2.y)<(h1 + h2));
}

void game::hurt()
{
	hero->stopAllActions();
	switch(life)
	{
	case 3:
		life--;
		blood3->setVisible(false);
		break;
	case 2:
		life--;
		blood2->setVisible(false);
		break;
	case 1:
		life--;
		blood1->setVisible(false);
		setover();
		break;
	}

	hero->runAction((CCActionInterval*)CCBlink::create(3,10));

	ishurt = true;

	this->schedule(schedule_selector(game::reset),3.0f);
}

void  game::reset(float sender)
{
	ishurt = false;
}

void game::releaseFishbone(int x, int y)
{
	for(int i = 0; i<5; i++)
	{
		fishbone* fb = (fishbone*)fishbones->objectAtIndex(i);
		if(!isover && !fb->getIsVisible())
		{
			fb->setIsVisible();
			fb->setPosition(x,y);
			fb->runAction(CCSequence::create(CCMoveTo::create((500-y)/150,ccp(x,500)),CCCallFunc::create(fb,callfunc_selector(fishbone::setIsNotVisible)),NULL));
			break;
		}
	}
}

void game::releaseTube(int x, int y)
{
	for(int i = 0; i<10; i++)
	{
		tube* tb = (tube*)tubes->objectAtIndex(i);
		if(!isover && !tb->getIsVisible())
		{
			tb->setIsVisible();
			tb->setPosition(x,y);
			tb->runAction(CCSequence::create(CCMoveTo::create((y+50)/150,ccp(x,-50)),CCCallFunc::create(tb,callfunc_selector(tube::setIsNotVisible)),NULL));
			break;
		}
	}
}