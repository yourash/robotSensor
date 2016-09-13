#include "MainScene.h"
#include "SimpleAudioEngine.h"
#define SCORE_FONT_SIZE 0.04

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //MENU
        //SIZE
    {
        ui::Slider *sizeSlider=ui::Slider::create();
        sizeSlider->loadBarTexture("bar.png");
        sizeSlider->loadSlidBallTextureNormal("slider.png");
        sizeSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.9));
        this->addChild(sizeSlider);

        sizeSlider->addEventListener(CC_CALLBACK_2(MainScene::sizeSliderEvent, this));
        
        sizeLabel = Label::createWithTTF( "Size: 0", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        sizeLabel->setColor(Color3B::WHITE);
        sizeLabel->setPosition(Point(visibleSize.width*0.9, visibleSize.height * 0.9));

        this->addChild(sizeLabel);
    }
        //ROTATION
    {
        ui::Slider *rotationSlider=ui::Slider::create();
        rotationSlider->loadBarTexture("bar.png");
        rotationSlider->loadSlidBallTextureNormal("slider.png");
        rotationSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.8));
        this->addChild(rotationSlider);

        rotationSlider->addEventListener(CC_CALLBACK_2(MainScene::rotationSliderEvent, this));

        rotationLabel = Label::createWithTTF( "Rotation:  0'", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        rotationLabel->setColor(Color3B::WHITE );
        rotationLabel->setPosition(Point(visibleSize.width*0.9, visibleSize.height * 0.8));
        
        this->addChild(rotationLabel);
    }

        //STEP
    {
        ui::Slider *stepSlider=ui::Slider::create();
        stepSlider->loadBarTexture("bar.png");
        stepSlider->loadSlidBallTextureNormal("slider.png");
        stepSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.7));
        this->addChild(stepSlider);

        stepSlider->addEventListener(CC_CALLBACK_2(MainScene::stepSliderEvent, this));

        stepLabel = Label::createWithTTF( "Step:  0", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        stepLabel->setColor(Color3B::WHITE );
        stepLabel->setPosition(Point(visibleSize.width*0.9, visibleSize.height * 0.7));
        
        this->addChild(stepLabel);
    }

        //START

    {
        auto startItem = MenuItemImage::create("startbutton.png","startbutton.png",CC_CALLBACK_1(MainScene::START, this));
    
        startItem->setPosition(Vec2(visibleSize.width*0.9,visibleSize.height*0.15));

        auto startButton = Menu::create(startItem, NULL);
        startButton->setPosition(Vec2::ZERO);
        this->addChild(startButton, 1);
    }
    //OBJECT_INIT

    mrRobot=new Robot(this);
    
    return true;
}


void MainScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainScene::sizeSliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        mrRobot->changeSize(percent);
        robotSize=percent;
        sizeLabel->setString("Size: "+(std::to_string(robotSize)));
    }
}

void MainScene::rotationSliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        mrRobot->changeRotation(percent);
        robotRotation=percent*3.6;
        rotationLabel->setString("Rotation: "+(std::to_string(robotRotation))+"'");
    }
}

void MainScene::stepSliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        mrRobot->changeStep(percent);
        robotStep=percent;
        stepLabel->setString("Step: "+(std::to_string(robotStep)));
    }
}

void MainScene::START(cocos2d::Ref* pSender)
{
    mrRobot->makeStep();
}