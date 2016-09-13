#include "Robot.h"

USING_NS_CC;

Robot::Robot(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	mrRobot = Sprite::create("robot_sprite.png");
	mrRobot->setScale(1,1);
	mrRobot->setPosition(visibleSize.width/2,visibleSize.height/2);

	layer->addChild( mrRobot, 10 );
}

void Robot::changeSize(int percent)
{
	mrRobot->setScale(0.1*(percent),0.1*(percent));
}

void Robot::changeRotation(int percent)
{
	rotation=percent*3.6;
	mrRobot->setRotation(-rotation);
}

void Robot::changeStep(int percent)
{
	stepLength=percent;
}

void Robot::makeStep()
{
	mrRobot->setPosition(Vec2(mrRobot->getPosition().x+stepLength*cos(rotation*3.141592/180),mrRobot->getPosition().y+stepLength*sin(rotation*3.141592/180)));
}