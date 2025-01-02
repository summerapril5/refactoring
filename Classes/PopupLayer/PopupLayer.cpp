#include "SimpleAudioEngine.h"
#include"..\PlayingScene\PlayingScene.h"
#include <string>
#include <utility>
#include"PopupLayer.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
using namespace ui; 

Label* costLabel[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
Label* reLabel;

extern pair<int, Hero*> heroCard[5];
extern pair<int, Hero*> prepare[9];
extern vector<vector<pair<int, Hero*>>> chessboard; //��������

extern int coinCount;
extern int populutionCount;

extern bool pop_open;

extern Button* shopbutton;
extern Button* upbutton;
extern Button* rebutton;

extern void updateButtonState(Button* button);
extern void shopLabelState();
extern void PoState();

EventListenerTouchOneByOne* listener; //����������������Ϊ��Ա������ȫ�ֱ���

//����ˢ�°�ť״̬
void reButtonState(Button* button)
{
    if (coinCount < 2) {
        button->setEnabled(false); // �����С������������ʱ���ð�ť
        rebutton->loadTextures("buttons/RefreshSelected.png", "buttons/RefreshSelected.png", "buttons/RefreshSelected.png");
        reLabel->setTextColor(Color4B::RED);
    }
    else {
        button->setEnabled(true); // �������ð�ť
        rebutton->loadTextures("buttons/RefreshNormal.png", "buttons/RefreshSelected.png", "buttons/RefreshSelected.png");
        reLabel->setTextColor(Color4B::WHITE);
    }
}
//�����ƿ�״̬
void CardsState() {
    for (int i = 0; i < 5; i++) {
        if (heroCard[i].first != -1) {
            if (heroCard[i].second->getCost() > coinCount)
                costLabel[i]->setTextColor(Color4B::RED);
            else
                costLabel[i]->setTextColor(Color4B::WHITE);
        }
    }
}
/* ��ʼ������ */
void PopupLayer::Cardsinit() {
    for (int i = 0; i < 5; i++)
        if (heroCard[i].first != -1) {
            /* �Ƴ�ԭ���Ŀ��� */
            if (heroCard[i].second != nullptr) {
                heroCard[i].second->removeFromParent(); 
                costLabel[i]->setString("");
            }

            switch (heroCard[i].first) {
                case 0:
                    heroCard[i].second = new HeroPhysicalTank(false, 1);
                    heroCard[i].second->setTexture("Hero/hero00.png");
                    break;
                case 1:
                    heroCard[i].second = new HeroMagicTank(false, 1);
                    heroCard[i].second->setTexture("Hero/hero10.png");
                    break;
                case 2:
                    heroCard[i].second = new HeroPhysicalWarrior(false, 1);
                    heroCard[i].second->setTexture("Hero/hero20.png");
                    break;
                case 3:
                    heroCard[i].second = new HeroMagicalWarrior(false, 1);
                    heroCard[i].second->setTexture("Hero/hero30.png");
                    break;
                case 4:
                    heroCard[i].second = new HeroMarksman(false, 1);
                    heroCard[i].second->setTexture("Hero/hero40.png");
                    break;
                case 5:
                    heroCard[i].second = new HeroMage(false, 1);
                    heroCard[i].second->setTexture("Hero/hero50.png");
                    break;
            }
            heroCard[i].second->setFlippedX(false);
            heroCard[i].second->setFlippedY(false);
            heroCard[i].second->setPosition(Vec2(156 + 200 * i, 696));
            heroCard[i].second->setOpacity(255);
            this->addChild(heroCard[i].second);
            costLabel[i]->setString("Cost:"+to_string(heroCard[i].second->getCost()));
        }

}
void StartUp(int number) {
    int num=0;
    bool first_hero = true;
    for (int start = 1; start < 3; start++) {
        num = 0;
        first_hero = true;
        for (int i = 0; i < 9; i++) {
            if (prepare[i].first == number && prepare[i].second->getLevel() == start)
                num++;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 6; j++) {
                if (chessboard[i][j].first == number && chessboard[i][j].second->getLevel() == start)
                    num++;
            }
        }

        if (num == 3) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 6; j++) {
                    if (chessboard[i][j].first == number && chessboard[i][j].second->getLevel() == start) {
                        if (first_hero) {
                            chessboard[i][j].second->upLevel();
                            chessboard[i][j].second->setScale(0.9 + 0.3 * chessboard[i][j].second->getLevel());
                            first_hero = false;
                        }
                        else {
                            chessboard[i][j].first = -1;
                            populutionCount--;
                            PoState();
                            chessboard[i][j].second->removeFromParent();
                            chessboard[i][j].second = nullptr;
                        }
                    }
                }
            }
            for (int i = 0; i < 9; i++) {
                if (prepare[i].first == number && prepare[i].second->getLevel() == start) {
                    if (first_hero) {
                        prepare[i].second->upLevel();
                        prepare[i].second->setScale(0.9 + 0.3 * prepare[i].second->getLevel());
                        first_hero = false;
                    }
                    else {
                        prepare[i].first = -1;
                        prepare[i].second->removeFromParent();
                        prepare[i].second = nullptr;
                    }
                }
            }
        }
    }
}
bool PopupLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Vec2 touchPos = touch->getLocation(); //��ȡ����λ��
    //showCoordinates(touchPos);
    /* �жϴ���λ���Ƿ��ڵ����ڲ� */
    if ((140 <= touchPos.x && touchPos.x <= 1140 && 643 <= touchPos.y && touchPos.y <= 893) ||
        (1026.25 <= touchPos.x && touchPos.x <= 1213.75 && 26.25 <= touchPos.y && touchPos.y <= 213.75)) {
        if ((140 <= touchPos.x && touchPos.x <= 1140 && 643 <= touchPos.y && touchPos.y <= 893)) {
            int i = (touchPos.x - 140) / 200;
            if (heroCard[i].first != -1 && heroCard[i].second->getCost() <= coinCount) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
                for (int j = 0; j < 9; j++)
                    if (prepare[j].first == -1) { //�������ƶ�����ս����
                        prepare[j].first = heroCard[i].first;
                        prepare[j].second = heroCard[i].second;
                        costLabel[i]->setString("");
                        heroCard[i].first = -1;
                        heroCard[i].second = nullptr;
                        switch (prepare[j].first) {
                        case 0:
                            prepare[j].second->setTexture("Hero/hero01.png");
                            break;
                        case 1:
                            prepare[j].second->setTexture("Hero/hero11.png");
                            break;
                        case 2:
                            prepare[j].second->setTexture("Hero/hero21.png");
                            break;
                        case 3:
                            prepare[j].second->setTexture("Hero/hero31.png");
                            break;
                        case 4:
                            prepare[j].second->setTexture("Hero/hero41.png");
                            break;
                        case 5:
                            prepare[j].second->setTexture("Hero/hero51.png");
                            break;
                        }
                        coinCount -= prepare[j].second->getCost();
                        updateButtonState(upbutton);
                        reButtonState(rebutton);
                        CardsState();
                        shopLabelState();
                        prepare[j].second->setScale(1.2F);
                        prepare[j].second->setPosition(Vec2(240 + 87.25 * j, 150));
                        StartUp(prepare[j].first);
                        return true;
                    }
            }
            //�����ڵ����ڲ������رյ������������ݴ����¼�
        }
    }
    else { //�����ڵ����ⲿ���رյ���
        pop_open = false;
        hide();
        }

    return false;
}

/* ��ʼ�������� */
bool PopupLayer::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0))) {
        return false;
    }

    /* ������������ */
    auto popupBg = Sprite::create("ChessBoard/Cards.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    popupBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 4 / 5));
    addChild(popupBg);

    /* ����ˢ�°�ť */
    rebutton = Button::create("buttons/RefreshNormal.png", "buttons/RefreshSelected.png");
    rebutton->setPosition(Vec2(0.875 * visibleSize.width, 0.415 * visibleSize.height));
    rebutton->addClickEventListener(CC_CALLBACK_1(PopupLayer::reonButtonClicked, this));
    addChild(rebutton);
    /*չʾˢ����Ҫ�������*/
    reLabel = Label::createWithTTF("2", "fonts/Marker Felt.ttf", 36);
    reLabel->setPosition(Vec2(0.888 * visibleSize.width, 0.430 * visibleSize.height));
    reButtonState(rebutton);
    this->addChild(reLabel);
    /*��ʼ�����ƻ���label*/
    for (int i = 0; i < 5; i++) {
        costLabel[i] = Label::createWithTTF("", "fonts/Marker Felt.ttf", 36);
        costLabel[i]->setPosition(Vec2(240 + 200 * i, 666));
        this->addChild(costLabel[i]);
    }
    Cardsinit(); //��ʼ������
    CardsState();
    /*�ƶ�Ӣ�۵����� */
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(PopupLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void PopupLayer::reonButtonClicked(Ref* sender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    //ˢ�¿���
    coinCount -= 2;
    PlayingScene::randCard();
    Cardsinit();
    updateButtonState(upbutton);
    reButtonState(rebutton);
    CardsState();
    shopLabelState();
}

void PopupLayer::hide() {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    Node* parent = getParent();
    for (int i = 0; i < 9; i++) {
        if (prepare[i].first != -1) {
            //����ս����Ŀ����ƻظ��ڵ�
            prepare[i].second->removeFromParent();
            parent->addChild(prepare[i].second);
        }
    }
    removeFromParent();
    shopbutton->setEnabled(true);
    shopbutton->loadTextures("buttons/ShopNormal.png", "buttons/ShopSelected.png", "buttons/ShopSelected.png");
}
