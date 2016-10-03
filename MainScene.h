#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Robot.h"
#include "RedRay.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainScene);

    void widthSliderEvent(Ref *sender, ui::Slider::EventType type);
    void heightSliderEvent(Ref *sender, ui::Slider::EventType type);
    void rotationSliderEvent(Ref *sender, ui::Slider::EventType type);
    void stepSliderEvent(Ref *sender, ui::Slider::EventType type);
    void changeAngle(Ref *sender, ui::Slider::EventType type);
    void update(float delta);
    void START(cocos2d::Ref* pSender);
    void RAY(cocos2d::Ref* pSender);
private:
	Robot *mrRobot;
	cocos2d::Label* widthLabel;
    cocos2d::Label* heightLabel;
	cocos2d::Label* rotationLabel;
	cocos2d::Label* stepLabel;
    cocos2d::Label* angleLabel;
    cocos2d::Sprite *backGround;
	int robotWidth, robotHeight, robotRotation, robotStep, rotationAngle;
};

#endif // __MAIN_SCENE_H__
