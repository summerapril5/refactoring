#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include"..\StartGame\StartGame.h"
using namespace CocosDenshion;
USING_NS_CC;

/* ����һ��Scene���� */
Scene* LoadingScene::createScene() {
    return LoadingScene::create();
}

/* ��ʼ��loading�������� */
bool LoadingScene::init() {
    if (!Scene::init()) //��ʼ��
        return false; //��ʼ��ʧ��

    auto visibleSize = Director::getInstance()->getVisibleSize(); //��Ļ�ɼ�����Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); //ԭ������    

    /* ��ӭ��ǩ */
    auto label = Label::createWithTTF("Welcome to the game!\n        Loading ......", "fonts/Marker Felt.ttf", 75); //������ǩ
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 2 * visibleSize.height / 3)); //��ǩλ��
    label->setTextColor(Color4B::BLACK); //������ɫ
    this->addChild(label, 1); //��ӵ�������

    /* �������� */
    auto background = Sprite::create("Background/loading.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    /* ���������� */
    auto loadingBar2 = Sprite::create("Bar/loadingbar2.png");
    loadingBar2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    loadingBar2->setScale(2);
    this->addChild(loadingBar2, 0);

    /* ��ЧԤ���� */
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/backgrondmusic.mp3");//��������
    //SimpleAudioEngine::getInstance()->preloadEffect(".");//��Ч

    /* ���������� */
    auto loadingBar1 = ProgressTimer::create(Sprite::create("Bar/loadingbar1.png")); //����������
    loadingBar1->setType(ProgressTimer::Type::BAR); //��Ϊ����
    loadingBar1->setScale(2); //�Ŵ�2��
    loadingBar1->setMidpoint(Vec2(0, 0)); //�����������λ��
    loadingBar1->setBarChangeRate(Vec2(1, 0)); //�������ı仯��
    loadingBar1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)); //��������λ��
    this->addChild(loadingBar1, 0); //����������ӵ�������

    loadingBar1->setPercentage(0); //��ʼ�ٷֱ�Ϊ0
    double duration = 1.0; //����ʱ��2s
    /* ������ʱ�� ÿ֡�����ӽ��� */
    this->schedule([=](double deltaTime) {
        double currentPercent = loadingBar1->getPercentage(); //��ǰ�ٷֱ�
        double increment = (100 / duration) * deltaTime; //ÿ֡���ӵİٷֱ�
        double newPercent = currentPercent + increment; //�����µİٷֱ�
        loadingBar1->setPercentage(newPercent); //���½������İٷֱ�

        if (newPercent >= 100) { //�������
            this->unschedule("loading");

            /* �л�����ʼ��Ϸ������ */
            auto newScene = StartGameScene::create(); //������ʼ��Ϸ��������
            Director::getInstance()->replaceScene(newScene); //�л�����
            SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/backgrondmusic.mp3", true); //���ű�������
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.6F); //���ñ������ֵ�����
        }
        }, "loading");

    return true;
}