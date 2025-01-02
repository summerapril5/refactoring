#include "SimpleAudioEngine.h"
#include"StartGame.h"
#include"..\CreateRoomScene\CreateRoomScene.h"
#include "..\SetMusic\SetMusicScene.h"
using namespace ui;
using namespace CocosDenshion;
USING_NS_CC;

/* ����һ��Scene���� */
Scene* StartGameScene::createScene() {
    return StartGameScene::create();
}

/* ������˳���Ϸ */
void StartGameScene::menuCloseCallback(Ref* pSender) {
    //SimpleAudioEngine::sharedEngine()->end(); //�ͷ�����������Դ
    Director::getInstance()->end(); //������Ϸѭ��

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0); //iOS�˳�
#endif
}

/* ����󴴽����� */
void StartGameScene::menuCreateRoomCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    auto newScene = CreateRoomScene::create(); //������Ϸ����
    Director::getInstance()->replaceScene(newScene); //�л����������䳡��
}

/* ����������Ч */
void StartGameScene::menuSetMusicCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    auto newScene = SetMusicScene::create();
    Director::getInstance()->pushScene(newScene); //�л���������Ч���� ��ǰ�������볡��ջ��
}

/* ��ʼ��StartGameScene�������� */
bool StartGameScene::init() {
    if (!Scene::init()) //��ʼ��
        return false; //��ʼ��ʧ��

    auto visibleSize = Director::getInstance()->getVisibleSize(); //��Ļ�ɼ�����Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); //ԭ������    

    /* �������� */
    auto background = Sprite::create("Background/startgame.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    /* �˳�����˵��� */
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
        CC_CALLBACK_1(StartGameScene::menuCloseCallback, this));
    float scale = 5.0;
    closeItem->setScale(4); //�Ŵ�4��
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width * scale / 2;
    float y = origin.y + closeItem->getContentSize().height * scale / 2;
    closeItem->setPosition(Vec2(x, y)); //������ʾλ��

    /* ��ʼ��Ϸ�˵��� */
    auto startItem = MenuItemImage::create("Buttons/Start.png", "Buttons/Start.png",
        CC_CALLBACK_1(StartGameScene::menuCreateRoomCallback, this));
    startItem->setScale(1.3F);
    x = origin.x + visibleSize.width / 6;
    y = origin.y + visibleSize.height / 5;
    startItem->setPosition(Vec2(x, y));

    /* ������Ч�˵��� */
    auto setMusic = MenuItemImage::create("Music/setting.png", "Music/setting.png",
        CC_CALLBACK_1(StartGameScene::menuSetMusicCallback, this));
    setMusic->setScale(0.5);
    x = origin.x + 11 * visibleSize.width / 12;
    y = origin.y + 8 * visibleSize.height / 9;
    setMusic->setPosition(Vec2(x, y));

    /* �����˵� */
    auto menu = Menu::create(closeItem, startItem, setMusic, nullptr); //��Ӳ˵���
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    return true;
}
class PopupLayer : public cocos2d::Layer {
public:
    virtual bool init() override;
    CREATE_FUNC(PopupLayer);

    void show();
    void hide();

private:
    void onBackgroundClicked(cocos2d::Ref* sender);
    void onButtonClicked(cocos2d::Ref* sender);

    cocos2d::Menu* buttonMenu;
};