#include "SimpleAudioEngine.h"
#include "CreateRoomScene.h"
#include "../PlayingScene/PlayingScene.h"
#include "../StartGame/StartGame.h"
#include "../SetMusic/SetMusicScene.h"
USING_NS_CC;

/* ����һ��Scene���� */
Scene* CreateRoomScene::createScene() {
    return CreateRoomScene::create();
}
/* ����������Ч */
void CreateRoomScene::menuSetMusicCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    auto newScene = SetMusicScene::create();
    Director::getInstance()->pushScene(newScene); //�л���������Ч���� ��ǰ�������볡��ջ��
}

/* ����󷵻������� */
void CreateRoomScene::menuCloseCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    auto newScene = StartGameScene::create(); //������
    Director::getInstance()->replaceScene(newScene); //�л���������
}

/* ����������Ϸ���� */
void CreateRoomScene::menuStartGameCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    auto newScene = PlayingScene::create(); //��Ϸ����
    Director::getInstance()->replaceScene(newScene); //�л�����Ϸ����
}

/* ��ʼ��CreateRoomScene�������� */
bool CreateRoomScene::init() {
    if (!Scene::init()) //��ʼ��
        return false; //��ʼ��ʧ��

    auto visibleSize = Director::getInstance()->getVisibleSize(); //��Ļ�ɼ�����Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); //ԭ������    

    /* �������� */
    auto background = Sprite::create("Background/createRoom.jpg");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    /* �˳�����˵��� */
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
        CC_CALLBACK_1(CreateRoomScene::menuCloseCallback, this));
    float scale = 5.0;
    closeItem->setScale(4); //�Ŵ�4��
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width * scale / 2;
    float y = origin.y + closeItem->getContentSize().height * scale / 2;
    closeItem->setPosition(Vec2(x, y)); //������ʾλ��

    /* ��ʼ��Ϸ�˵��� */
    auto startItem = MenuItemImage::create("Buttons/Start.png", "Buttons/Start.png",
        CC_CALLBACK_1(CreateRoomScene::menuStartGameCallback, this));
    startItem->setScale(1.3F);
    x = origin.x + 2 * visibleSize.width / 3;
    y = origin.y + visibleSize.height / 5;
    startItem->setPosition(Vec2(x, y));

    /* ������Ч�˵��� */
    auto setMusic = MenuItemImage::create("Music/setting.png", "Music/setting.png",
        CC_CALLBACK_1(CreateRoomScene::menuSetMusicCallback, this));
    setMusic->setScale(0.5);
    x = origin.x + 11 * visibleSize.width / 12;
    y = origin.y + 8 * visibleSize.height / 9;
    setMusic->setPosition(Vec2(x, y));

    /* �����˵� */
    auto menu = Menu::create(closeItem, startItem, setMusic, nullptr); //���Ӳ˵���
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}