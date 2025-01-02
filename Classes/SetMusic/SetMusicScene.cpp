#include "SimpleAudioEngine.h"
#include "SetMusicScene.h"
#include "../StartGame/StartGame.h"
#include "../CreateRoomScene/CreateRoomScene.h"
#include "../PlayingScene/PlayingScene.h"
using namespace CocosDenshion;
USING_NS_CC;

/* ����һ��Scene���� */
Scene* SetMusicScene::createScene() {
    return SetMusicScene::create();
}

/* ����󷵻������� */
void SetMusicScene::menuCloseCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    Director::getInstance()->popScene();
}

/* ����/��ͣ�������� */
bool SetMusicScene::onSwitchMusicTouched(Touch* touch, Event* event) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    /* ���ڲ��� */
    if (isMusicPlaying) {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //��ͣ����
        switchMusic->setTexture("Music/pausingMusic.png"); //�л�Ϊֹͣ����ͼƬ
    }
    /* ��ͣ״̬ */
    else {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); //��������
        switchMusic->setTexture("Music/playingMusic.png"); //�л��ز���ͼƬ
    }
    isMusicPlaying = !isMusicPlaying; //�л����ֲ���״̬
    return true;
}

/* �����仯 */
void SetMusicScene::volumeSliderCallback(Ref* sender, ui::Slider::EventType eventType) {
    if (eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
        ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
        int volume = slider->getPercent(); //����ֵ

        volumeLabel->setString(std::to_string(volume)); //���»������ٷֱ��ı�
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume / 100.0f); //���ñ������ֵ�����
        //CCLOG("1111111111111: %f", SimpleAudioEngine::getInstance()->getBackgroundMusicVolume());
    }
}

/* ��ʼ��PlayingScene�������� */
bool SetMusicScene::init() {
    if (!Scene::init()) //��ʼ��
        return false; //��ʼ��ʧ��

    auto visibleSize = Director::getInstance()->getVisibleSize(); //��Ļ�ɼ�����Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); //ԭ������    

    /* �������� */
    auto background = Sprite::create("Music/setMusic.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    isMusicPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying(); //��ȡ����״̬

    /* ����/��ͣͼƬ */
    if (isMusicPlaying) //���ڲ���
        switchMusic = Sprite::create("Music/playingMusic.png");
    else //��ͣ����
        switchMusic = Sprite::create("Music/pausingMusic.png");
    switchMusic->setScale(1.5);
    switchMusic->setPosition(Vec2(visibleSize.width / 6 + origin.x, 2 * visibleSize.height / 3 + origin.y));
    this->addChild(switchMusic, 1);

    /* Label"Music" */
    auto label = Label::createWithTTF("Music", "fonts/Marker Felt.ttf", 45); //����Label
    label->setPosition(Vec2(switchMusic->getPositionX(), switchMusic->getPositionY() + switchMusic->getContentSize().height / 2 + label->getContentSize().height / 2 + 10)); //Labelλ����ͼƬ�Ϸ�
    this->addChild(label, 1);

    /* ����¼� */
    auto touchListener = EventListenerTouchOneByOne::create(); //���������¼�������
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode)) { //��ͼƬ�ڵ��ʱ�������߼�
            onSwitchMusicTouched(touch, event); //���ûص�����
            return true;
        }
        return false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, switchMusic); //���������󶨵�Sprite��

    /* �������ڻ����� */
    auto volumeSlider = ui::Slider::create(); //�����������ؼ�
    volumeSlider->loadBarTexture("Bar/sliderBar.png"); //�������ı���ͼƬ
    volumeSlider->loadSlidBallTextures("Music/sliderNormal.png", "Music/sliderNormal.png", ""); //Ĭ��״̬ͼƬ ������ʱ״̬ͼƬ
    volumeSlider->loadProgressBarTexture("Bar/sliderProgress.png"); //������ͼƬ
    volumeSlider->setPosition(Vec2(switchMusic->getPositionX() + 2.2 * switchMusic->getContentSize().width + volumeSlider->getContentSize().width / 2 + 10, switchMusic->getPositionY()));
    int volume = static_cast<int>(100 * SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()); //��ǰ����
    volumeSlider->setPercent(volume); //��ʼ�����ٷֱ�
    volumeSlider->setScale(1.5); //����������С����Ϊ1.5��
    volumeSlider->addEventListener(CC_CALLBACK_2(SetMusicScene::volumeSliderCallback, this)); //���������¼������� ָ���ص�����
    this->addChild(volumeSlider, 1);

    /* �������ٷֱ� */
    volumeLabel = Label::createWithTTF("60", "fonts/Marker Felt.ttf", 30);
    volumeLabel->setString(std::to_string(volume)); //������ʾ
    volumeLabel->setPosition(Vec2(7 * visibleSize.width / 8 + origin.x, 2 * visibleSize.height / 3 + origin.y)); //��ʼλ��
    this->addChild(volumeLabel, 1); //����ǩ��ӵ�������

    /* �˳���Ч���� */
    auto closeItem = MenuItemImage::create("Music/setReturn.png", "Music/setReturn.png",
        CC_CALLBACK_1(SetMusicScene::menuCloseCallback, this));
    float scale = 1.2F;
    closeItem->setScale(scale);
    float x = origin.x + closeItem->getContentSize().width * scale / 2;
    float y = origin.y + visibleSize.height - closeItem->getContentSize().height * scale / 2;
    closeItem->setPosition(Vec2(x, y)); //��ʾλ��

    /* �����˵� */
    auto menu = Menu::create(closeItem, nullptr); //��Ӳ˵���
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}