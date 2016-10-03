#include "RedRay.h"

USING_NS_CC;

RedRay::RedRay()
{
	ray = DrawNode::create();
    ray->drawLine(Point(0, 0), Point(100, 100), Color4F::RED);   
}

RedRay::RedRay(cocos2d::Layer* layer,cocos2d::Vec2 robotPos,float angle)
{
	ray = DrawNode::create();

    ray->drawLine(Point(robotPos.x, robotPos.y), Point(100, 100), Color4F::RED);
    layer->addChild(ray,1);
    aLayer=layer;
}

RedRay::~RedRay()
{
	
}

void RedRay::rotateRay(cocos2d::Vec2 robotPos,float rotation)
{
	ray->clear();
	ray->drawLine(Point(robotPos.x, robotPos.y), Point(robotPos.x+900*cos(rotation*3.141592/180),robotPos.y+900*sin(rotation*3.141592/180)), Color4F::RED);
}

void RedRay::removeRay()
{
	ray->clear();
}