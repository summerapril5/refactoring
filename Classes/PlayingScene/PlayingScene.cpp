#include "SimpleAudioEngine.h"
#include "../PlayingScene/PlayingScene.h"
#include "../StartGame/StartGame.h"
#include "../BattleScene/BattleScene.h"
#include "../SetMusic/SetMusicScene.h"
#include <vector>
#include <time.h>
#include <string>
#include <utility>
#include "../PopupLayer/PopupLayer.h"
#include "../AI/AI.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
using namespace ui;

int coinCount = 5;
int populutionCount = 0;
int my_level = 3;

bool pop_open = false;

extern void CardsState();
extern void reButtonState(Button* button);

Button* shopbutton;
Button* upbutton;
Button* rebutton;

PopupLayer* popupLayer;

PlayingScene* playscene;

Label* coinLabel;
Label* upLabel;
Label* poLabel;
Label* levelLabel;

const int boardX_min = 261;
const int boardX_max = 974;
const int boardY_min = 294;
const int boardY_max = 722;
const int sizeX = 118.4;
const int sizeY = 71.2;

Sprite* chooseground;

AI ai;

const int numRows = 6; //��
const int numCols = 6; //��
const float tileSize = 90.0F; //���Ӵ�С
int selectedHeroIndex = -1;

pair<int, Hero*> my_hero=make_pair(-1,nullptr);
pair<int, Hero*> heroCard[5] = { {-1, nullptr},{-1, nullptr}, {-1, nullptr}, {-1, nullptr}, {-1, nullptr} }; //����
pair<int, Hero*> prepare[9] = { {-1, nullptr},{-1, nullptr}, {-1, nullptr}, {-1, nullptr}, {-1, nullptr}, {-1, nullptr}, {-1, nullptr}, {-1, nullptr}, {-1, nullptr} }; //��ս

vector<vector<pair<int,Hero*>>> chessboard(numRows, vector<pair<int,Hero*>>(numCols,make_pair(-1, nullptr))); //��������

void puthero(Hero* h, int col, int row) {
    chessboard[col][row].first = 1;
    chessboard[col][row].second = h;

    float cardX = boardX_min + (col + 0.75) * sizeX;
    float cardY = boardY_min + (row + 1) * sizeY;
    chessboard[col][row].second->setPosition(cardX, cardY);
}

//����������ť״̬
void updateButtonState(Button* button)
{
    if (coinCount < 2 * my_level - 2) {
        button->setEnabled(false); // �����С������������ʱ���ð�ť
        upbutton->loadTextures("buttons/UpgradeSelected.png", "buttons/UpgradeSelected.png", "buttons/UpgradeSelected.png");
        upLabel->setTextColor(Color4B::RED);
    }
    else {
        button->setEnabled(true); // �������ð�ť
        upbutton->loadTextures("buttons/UpgradeNormal.png", "buttons/UpgradeSelected.png", "buttons/UpgradeSelected.png");
        upLabel->setTextColor(Color4B::WHITE);
    }
}
void shopLabelState() {
    coinLabel->setString(to_string(coinCount));
}
//�����˿�״̬
void PoState() {
    poLabel->setString(to_string(populutionCount) + " / " + to_string(my_level));
    if (populutionCount < my_level)
        poLabel->setTextColor(Color4B::WHITE);
    else
        poLabel->setTextColor(Color4B::RED);
}
/* ��������ƿ� ��ʼ������ */
void PlayingScene::randCard() {
    srand(time(0));

    for (int i = 0; i < 5; i++) 
        heroCard[i].first = rand() % 6; 
}

/* ����һ��Scene���� */
Scene* PlayingScene::createScene() {
    return PlayingScene::create();
}

/* ����󷵻������� */
void PlayingScene::menuCloseCallback(Ref* pSender) {
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    //����
    for (int i = 0; i < 5; i++)
        if (heroCard[i].second != nullptr) {
            heroCard[i].second->release(); //�ͷſ���
            heroCard[i] = { -1, nullptr };
        }
    //��ս
    for (int i = 0; i < 9; i++)
        if (prepare[i].second != nullptr) {
            prepare[i].second->release(); //�ͷſ���
            prepare[i] = { -1, nullptr };
        }
    my_level = 3;
    coinCount = 5;
    upLabel->setString(to_string(2 * my_level - 2));
    levelLabel->setString(to_string(my_level));
    PoState();
    updateButtonState(upbutton);
    shopLabelState();
    auto newScene = StartGameScene::create(); //������
    Director::getInstance()->replaceScene(newScene); //�л���������
}

void PlayingScene::shoponButtonClicked(Ref* sender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    shopbutton->setEnabled(false);
    shopbutton->loadTextures("buttons/ShopSelected.png", "buttons/ShopSelected.png", "buttons/ShopSelected.png");
    pop_open = true;
    popupLayer = PopupLayer::create();
    this->addChild(popupLayer);
}
void PlayingScene::uponButtonClicked(Ref* sender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    coinCount -= (2 * my_level - 2);
    my_level++;
    upLabel->setString(to_string(2 * my_level - 2));
    levelLabel->setString(to_string(my_level));
    PoState();
    updateButtonState(upbutton);
    shopLabelState();
}
void PlayingScene::onMouseDown(EventMouse* event)
{
    Vec2 mousePos = event->getLocation();
    mousePos.y = Director::getInstance()->getWinSize().height - mousePos.y;

    //��ս��
    for (int i = 0; i < 9; i++) {
        if (mousePos.x >= 243.75 + 87.25 * i && mousePos.x <= 286.75 + 87.25 * i && mousePos.y >= 156 && mousePos.y <= 219&&prepare[i].first!=-1) {
            my_hero.first = prepare[i].first;
            my_hero.second = prepare[i].second;
            initialPosition = my_hero.second->getPosition();
            prepare[i].first = -1;
            prepare[i].second = nullptr;
            isDragging = true;
            chooseground->setVisible(true);
            break;
        }
    }
    //����
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            if (mousePos.x >= 274 + 118.4 * j && mousePos.x <= 364 + 118.4 * j && mousePos.y >= 305+71.2*i && mousePos.y <= 352+71.2*i && chessboard[i][j].first != -1) {
                my_hero.first = chessboard[i][j].first;
                my_hero.second = chessboard[i][j].second;
                initialPosition = my_hero.second->getPosition();
                chessboard[i][j].first = -1;
                chessboard[i][j].second = nullptr;
                isDragging = true;
                chooseground->setVisible(true);
                populutionCount--;
            }
        }
    }
}

void PlayingScene::onMouseMove(EventMouse* event)
{
    if (isDragging)
    {
        Vec2 mousePos = event->getLocation();
        mousePos.y = Director::getInstance()->getWinSize().height - mousePos.y;
        my_hero.second->setPosition(Vec2(mousePos.x-30, mousePos.y - 35));
        PoState();
    }
}

void PlayingScene::onMouseUp(EventMouse* event)
{
    if (isDragging)
    {
        isDragging = false;

        Vec2 mousePos = event->getLocation();
        mousePos.y = Director::getInstance()->getWinSize().height - mousePos.y;
        //������
        if (mousePos.x >= 0.050 * 1280 && mousePos.x <= 0.150 * 1280 && 0.450 * 960 <= mousePos.y && 0.550 * 960 >= mousePos.y) {
            coinCount += (my_hero.second->getCost()*pow(3,my_hero.second->getLevel()-1));
            my_hero.first = -1;
            my_hero.second->removeFromParent();
            my_hero.second = nullptr;
            updateButtonState(upbutton);
            shopLabelState();
            return;
        }

        //��ս��
        for (int i = 0; i < 9; i++) {
            if (mousePos.x >= 243.75 + 87.25 * i && mousePos.x <= 286.75 + 87.25 * i && mousePos.y >= 156 && mousePos.y <= 219 && prepare[i].first == -1) {
                prepare[i].first = my_hero.first;
                prepare[i].second= my_hero.second;
                prepare[i].second->setPosition(Vec2(240 + 87.25 * i, 150));
                my_hero.first = -1;
                my_hero.second = nullptr;
                PoState();
                chooseground->setVisible(false);
                break;
            }
        }
        if (my_hero.first == -1)
            return;
        //����
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 6; j++) {
                if (mousePos.x >= 274 + 118.4 * j && mousePos.x <= 364 + 118.4 * j && mousePos.y >= 305 + 71.2 * i && mousePos.y <= 352 + 71.2 * i && chessboard[i][j].first == -1 && populutionCount < my_level) {
                    chessboard[i][j].first = my_hero.first;
                    chessboard[i][j].second = my_hero.second;
                    chessboard[i][j].second->setPosition(Vec2(290 + 118.4 * j, 295 + 71.2 * i));
                    my_hero.first = -1;
                    my_hero.second = nullptr;
                    populutionCount++;
                    PoState();
                    chooseground->setVisible(false);
                    break;
                }
            }
        }
        //��ս��
        if (my_hero.first == -1)
            return;
        for (int i = 0; i < 9; i++) {
            if (initialPosition==Vec2(240 + 87.25 * i, 150)) {
                prepare[i].first = my_hero.first;
                prepare[i].second = my_hero.second;
                prepare[i].second->setPosition(initialPosition);
                my_hero.first = -1;
                my_hero.second = nullptr;
                PoState();
                chooseground->setVisible(false);
                break;
            }
        }
        if (my_hero.first == -1)
            return;
        //����
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 6; j++) {
                if (initialPosition==Vec2(290+118.4*j,295+71.2*i)){
                    chessboard[i][j].first = my_hero.first;
                    chessboard[i][j].second = my_hero.second;
                    chessboard[i][j].second->setPosition(Vec2(initialPosition.x,initialPosition.y));
                    my_hero.first = -1;
                    my_hero.second = nullptr;
                    populutionCount++;
                    PoState();
                    chooseground->setVisible(false);
                    break;
                }
            }
        }
    }
}
/*����ʱ*/
void PlayingScene::updateProgressBar(float dt) {
    //����ʣ��ʱ��
    currentTime -= dt;
    if (currentTime < 0) {
        currentTime = 0;
    }

    //���½�����
    float progress = currentTime / totalTime;
    timer->setPercentage(progress * 100);

    //����ʱ���ǩ
    int remainingTime = static_cast<int>(ceil(currentTime));
    timeLabel->setString(std::to_string(remainingTime));

    //����Ƿ�ʱ���Ѿ�����
    if (currentTime <= 0) {
        unschedule(schedule_selector(PlayingScene::updateProgressBar));
        if (pop_open) {
            popupLayer->hide();
        }
        if (isDragging) {
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            auto mouseEvent = EventMouse::MouseEventType::MOUSE_UP;

            // ģ���������ɿ��¼�
            EventMouse event(mouseEvent);
            event.setMouseButton(EventMouse::MouseButton::BUTTON_LEFT);
            event.setCursorPosition(0, 0);
            dispatcher->dispatchEvent(&event);
        }
        ai.AIbettle();
        playscene = dynamic_cast<PlayingScene*>(Director::getInstance()->getRunningScene());
        auto newScene = BattleScene::create();
        Director::getInstance()->pushScene(newScene);
    }
}

/* ����������Ч */
void PlayingScene::menuSetMusicCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    auto newScene = SetMusicScene::create();
    Director::getInstance()->pushScene(newScene); //�л���������Ч���� ��ǰ�������볡��ջ��
}

/* ��ʼ��PlayingScene�������� */
bool PlayingScene::init() {
    if (!Scene::init()) //��ʼ��
        return false; //��ʼ��ʧ��

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            if (chessboard[i][j].second != nullptr) {
                chessboard[i][j].second->release(); //�ͷſ���
                chessboard[i][j].first = -1;
                chessboard[i][j].second = nullptr;
            }

    auto visibleSize = Director::getInstance()->getVisibleSize(); //��Ļ�ɼ�����Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); //ԭ������   

    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/playingBGM.mp3", true); //���ű�������
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.6F); //���ñ������ֵ�����

    /* �������� */
    auto background = Sprite::create("ChessBoard/playing.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    chooseground = Sprite::create("ChessBoard/choose.png");
    chooseground->setContentSize(Size(visibleSize.width, visibleSize.height));
    chooseground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //�˿ڱ�ǩ
    poLabel = Label::createWithTTF(to_string(populutionCount)+" / "+to_string(my_level), "fonts/Marker Felt.ttf", 88);
    poLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 3 / 4 + origin.y));
    chooseground->addChild(poLabel);
    this->addChild(chooseground, 0);
    //������
    auto sale = Sprite::create("ChessBoard/garbage.png");
    sale->setContentSize(Size(visibleSize.width, visibleSize.height));
    sale->setScale(0.25);
    sale->setPosition(Vec2(0.100 * visibleSize.width, 0.500 * visibleSize.height));
    chooseground->addChild(sale);
    this->addChild(chooseground, 0);
    chooseground->setVisible(false);
    randCard(); //��ʼ������

    /* �˳�������Ϸ�˵��� */
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
        CC_CALLBACK_1(PlayingScene::menuCloseCallback, this));
    float scale = 5.0;
    closeItem->setScale(4); //�Ŵ�4��
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width * scale / 2;
    float y = origin.y + closeItem->getContentSize().height * scale / 2;
    closeItem->setPosition(Vec2(x, y)); //������ʾλ��

    /* ������Ч�˵��� */
    auto setMusic = MenuItemImage::create("Music/setting.png", "Music/setting.png",
        CC_CALLBACK_1(PlayingScene::menuSetMusicCallback, this));
    setMusic->setScale(0.5);
    x = origin.x + 11 * visibleSize.width / 12;
    y = origin.y + 8 * visibleSize.height / 9;
    setMusic->setPosition(Vec2(x, y));

    /* �����˵� */
    auto menu = Menu::create(closeItem, setMusic, nullptr); //��Ӳ˵���
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /* ������ť */ 
    shopbutton = Button::create("buttons/ShopNormal.png", "buttons/ShopSelected.png");
    shopbutton->setPosition(Vec2(0.875 * visibleSize.width, 0.125 * visibleSize.height));
    shopbutton->addClickEventListener(CC_CALLBACK_1(PlayingScene::shoponButtonClicked, this));
    addChild(shopbutton);
    /*չʾ���*/
    coinLabel = Label::createWithTTF(to_string(coinCount), "fonts/Marker Felt.ttf", 36);
    coinLabel->setPosition(Vec2(0.888 * visibleSize.width, 0.125 * visibleSize.height));
    this->addChild(coinLabel);

    /* ������ť */ 
    upbutton = Button::create("buttons/UpgradeNormal.png", "buttons/UpgradeSelected.png");
    upbutton->setPosition(Vec2(0.100 * visibleSize.width, 0.130 * visibleSize.height));
    upbutton->addClickEventListener(CC_CALLBACK_1(PlayingScene::uponButtonClicked, this));
    addChild(upbutton);
    /*չʾ����ȼ�������*/
    upLabel = Label::createWithTTF(to_string(2 * my_level - 2), "fonts/Marker Felt.ttf", 36);
    upLabel->setPosition(Vec2(0.100 * visibleSize.width, 0.140 * visibleSize.height));
    this->addChild(upLabel);
    /*չʾ�ȼ�*/
    levelLabel = Label::createWithTTF(to_string(my_level), "fonts/Marker Felt.ttf", 36);
    levelLabel->setPosition(Vec2(0.155 * visibleSize.width, 0.055 * visibleSize.height));
    this->addChild(levelLabel);
    updateButtonState(upbutton);

    /* ����ССӢ��+Ѫ�� */
    m_pSprite = CCSprite::create("LittleHero/ikun.png");
    m_pblood = CCSprite::create("bloodbar/littleblood.png");
    m_pbloodback = CCSprite::create("bloodbar/littlebloodback.png");
    //���þ��� �ҷ�
    m_pSprite->setPosition(ccp(185, 276));
    m_pbloodback->setAnchorPoint(Vec2(0.8F, 0.5F));  // ����ê��
    m_pblood->setAnchorPoint(Vec2(0.2F, 0.5F));  // ����ê��
    m_pbloodback->setPosition(ccp(120, 160));
    m_pbloodback->setScale(0.4F);
    m_pblood->setPosition(ccp(72, 80));

    m_pSprite->addChild(m_pbloodback);
    m_pbloodback->addChild(m_pblood, 1);
    addChild(m_pSprite, 0);

    /* ����ʱ */

    //����������
    progressBackground = cocos2d::Sprite::create("Bar/countdownP.png");
    progressBackground->setPosition(visibleSize.width / 2, visibleSize.height / 40 * 39);
    addChild(progressBackground);

    //����������
    timer = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("Bar/countdown.png"));
    timer->setType(cocos2d::ProgressTimer::Type::BAR);
    timer->setMidpoint(cocos2d::Vec2(0, 0.5));
    timer->setBarChangeRate(cocos2d::Vec2(1, 0));
    timer->setPosition(visibleSize.width / 2, visibleSize.height / 40 * 39);
    addChild(timer);

    //����ʱ���ǩ
    timeLabel = cocos2d::Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    timeLabel->setPosition(visibleSize.width * 0.325, visibleSize.height / 40 * 39);
    addChild(timeLabel);

    //��ʼ��ʱ��
    totalTime = 20.0f;
    currentTime = totalTime;

    //������ʱ��
    schedule(schedule_selector(PlayingScene::updateProgressBar), 0.01f);

    //�����Ļ����Ӣ���ƶ�
    touchlistener = EventListenerMouse::create();
    touchlistener->onMouseDown = CC_CALLBACK_1(PlayingScene::onMouseDown, this);
    touchlistener->onMouseMove = CC_CALLBACK_1(PlayingScene::onMouseMove, this);
    touchlistener->onMouseUp = CC_CALLBACK_1(PlayingScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

    return true;
}