#include "Robot.h"

USING_NS_CC;

Robot::Robot(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	mrRobot = Sprite::create("robot_sprite.png");
	mrRobot->setScale(1,1);
	mrRobot->setPosition(visibleSize.width/2,visibleSize.height/2);
	aLayer=layer;
	layer->addChild( mrRobot, 1 );
}

void Robot::changeWidth(int percentX, int percentY)
{
	mrRobot->setScale(0.1*(percentX),0.1*(percentY));
}

void Robot::changeHeight(int percentX, int percentY)
{
	mrRobot->setScale(0.1*(percentX),0.1*(percentY));
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
	log("%f %f",mrRobot->getPosition().x,mrRobot->getPosition().y);
}

cocos2d::Vec2 Robot::getPosition()
{
	return mrRobot->getPosition();
}

void Robot::rayOn()
{
	aRay=new RedRay(aLayer,mrRobot->getPosition(),rotation);
	aRay->rotateRay(mrRobot->getPosition(),rotation);
}

void Robot::makeRayRotation(int rotation)
{
	aRay->rotateRay(mrRobot->getPosition(),rotation);
}

void Robot::rayOff()
{
	aRay->removeRay();
}