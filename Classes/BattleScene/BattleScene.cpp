#include "SimpleAudioEngine.h"
#include "../PlayingScene/PlayingScene.h"
#include "../BattleScene/BattleScene.h"
#include "../SetMusic/SetMusicScene.h"
#include <vector>
#include <time.h>
#include <string>
#include <queue>
#include <utility>
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
using namespace ui;

const int numRows = 6; //��
const int numCols = 6; //��
const float tileSize = 90.0F; //���Ӵ�С

const int boardX_min = 261;
const int boardX_max = 974;
const int boardY_min = 294;
const int boardY_max = 722;
const int sizeX = 118.4;
const int sizeY = 71.2;

extern vector<vector<pair<int, Hero*>>> chessboard; //��������
extern vector<vector<pair<int, Hero*>>> AIchessboard; //AI��������

extern int coinCount;

extern PlayingScene* playscene;

vector<vector<pair<int, Hero*>>> chessboardBattle(numRows, vector<pair<int, Hero*>>(numCols, make_pair(-1, nullptr))); //��������

extern void updateButtonState(Button* button);
extern void shopLabelState();

extern Button* upbutton;

void findNearestHero(int i, int j, bool opponent, int& x, int& y);
pair<int, int> isWithinAttackRange(int x, int y, bool opponent);

/* ����һ��Scene���� */
Scene* BattleScene::createScene() {
    return BattleScene::create();
}

/* ����������Ч */
void BattleScene::menuSetMusicCallback(Ref* pSender) {

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/click.wav");
    auto newScene = SetMusicScene::create();
    Director::getInstance()->pushScene(newScene); //�л���������Ч���� ��ǰ�������볡��ջ��
}

void BattleScene::releaseScene() {
    //�ͷ����������е�Ӣ�۶���
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (chessboardBattle[i][j].second != nullptr) {
                delete chessboardBattle[i][j].second;
                chessboardBattle[i][j].second = nullptr;
            }
        }
    }
}

/* ��ʼ��BattleScene�������� */
bool BattleScene::init() {
    if (!Scene::init()) //��ʼ��
        return false; //��ʼ��ʧ��
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

    /* ������Ч�˵��� */
    auto setMusic = MenuItemImage::create("Music/setting.png", "Music/setting.png",
        CC_CALLBACK_1(BattleScene::menuSetMusicCallback, this));
    setMusic->setScale(0.5);
    float x = origin.x + 11 * visibleSize.width / 12;
    float y = origin.y + 8 * visibleSize.height / 9;
    setMusic->setPosition(Vec2(x, y));

    /* �����˵� */
    auto menu = Menu::create(setMusic, nullptr); //��Ӳ˵���
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            if (i <= 2) {
                if (chessboard[i][j].first != -1) {
                    chessboardBattle[i][j].first = chessboard[i][j].first;
                    switch (chessboard[i][j].first) {
                    case 0:
                        chessboardBattle[i][j].second = new HeroPhysicalTank(chessboard[i][j].second->isRed(), chessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero01.png");
                        break;
                    case 1:
                        chessboardBattle[i][j].second = new HeroMagicTank(chessboard[i][j].second->isRed(), chessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero11.png");
                        break;
                    case 2:
                        chessboardBattle[i][j].second = new HeroPhysicalWarrior(chessboard[i][j].second->isRed(), chessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero21.png");
                        break;
                    case 3:
                        chessboardBattle[i][j].second = new HeroMagicalWarrior(chessboard[i][j].second->isRed(), chessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero31.png");
                        break;
                    case 4:
                        chessboardBattle[i][j].second = new HeroMarksman(chessboard[i][j].second->isRed(), chessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero41.png");
                        break;
                    case 5:
                        chessboardBattle[i][j].second = new HeroMage(chessboard[i][j].second->isRed(), chessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero51.png");
                        break;
                    }

                    //////////����Ӣ�� Ѫ����
                    chessboardBattle[i][j].second->setFlippedX(false);
                    chessboardBattle[i][j].second->setFlippedY(false);

                    //����Ѫ��
                    if (chessboardBattle[i][j].second->getLevel() == 1)
                    {
                        chessboardBattle[i][j].second->bloodbar = CCSprite::create("bloodbar/blood1.png");
                        chessboardBattle[i][j].second->bloodback = CCSprite::create("bloodbar/blood1back.png");
                    }
                    else if (chessboardBattle[i][j].second->getLevel() == 2)
                    {
                        chessboardBattle[i][j].second->bloodbar == CCSprite::create("bloodbar/blood2.png");
                        chessboardBattle[i][j].second->bloodback = CCSprite::create("bloodbar/blood1back.png");
                    }
                    else
                    {
                        chessboardBattle[i][j].second->bloodbar == CCSprite::create("bloodbar/blood3.png");
                        chessboardBattle[i][j].second->bloodback = CCSprite::create("bloodbar/blood1back.png");
                    }
                    chessboardBattle[i][j].second->bloodback->setAnchorPoint(Vec2(0.8F, 0.5F));  // ����ê��
                    chessboardBattle[i][j].second->bloodbar->setAnchorPoint(Vec2(0.2F, 0.5F));  // ����ê��
                    chessboardBattle[i][j].second->bloodback->setPosition(ccp(40, 70));
                    chessboardBattle[i][j].second->bloodback->setScale(0.1F);
                    chessboardBattle[i][j].second->bloodbar->setPosition(ccp(112, 107));

                    chessboardBattle[i][j].second->addChild(chessboardBattle[i][j].second->bloodback);
                    chessboardBattle[i][j].second->bloodback->addChild(chessboardBattle[i][j].second->bloodbar, 1);



                    chessboardBattle[i][j].second->setPosition(Vec2(290 + 118.4 * j, 295 + 71.2 * i));
                    chessboardBattle[i][j].second->setScale(0.9 + 0.3 * chessboardBattle[i][j].second->getLevel());
                    this->addChild(chessboardBattle[i][j].second, 0);
                    chessboardBattle[i][j].second->setOpacity(255);
                }
            }
            else {
                if (AIchessboard[i][j].first != -1) {
                    chessboardBattle[i][j].first = AIchessboard[i][j].first;
                    switch (AIchessboard[i][j].first) {
                    case 0:
                        chessboardBattle[i][j].second = new HeroPhysicalTank(AIchessboard[i][j].second->isRed(), AIchessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero01.png");
                        break;
                    case 1:
                        chessboardBattle[i][j].second = new HeroMagicTank(AIchessboard[i][j].second->isRed(), AIchessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero11.png");
                        break;
                    case 2:
                        chessboardBattle[i][j].second = new HeroPhysicalWarrior(AIchessboard[i][j].second->isRed(), AIchessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero21.png");
                        break;
                    case 3:
                        chessboardBattle[i][j].second = new HeroMagicalWarrior(AIchessboard[i][j].second->isRed(), AIchessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero31.png");
                        break;
                    case 4:
                        chessboardBattle[i][j].second = new HeroMarksman(AIchessboard[i][j].second->isRed(), AIchessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero41.png");
                        break;
                    case 5:
                        chessboardBattle[i][j].second = new HeroMage(AIchessboard[i][j].second->isRed(), AIchessboard[i][j].second->getLevel());
                        chessboardBattle[i][j].second->setTexture("Hero/hero51.png");
                        break;
                    }

                    //////////����Ӣ�� Ѫ����
                    chessboardBattle[i][j].second->setFlippedX(false);
                    chessboardBattle[i][j].second->setFlippedY(false);

                    //�з�Ѫ��

                    if (chessboardBattle[i][j].second->getLevel() == 1)
                    {
                        chessboardBattle[i][j].second->bloodbar = CCSprite::create("bloodbar/enemyblood1.png");
                        chessboardBattle[i][j].second->bloodback = CCSprite::create("bloodbar/blood1back.png");
                    }
                    else if (chessboardBattle[i][j].second->getLevel() == 2)
                    {
                        chessboardBattle[i][j].second->bloodbar == CCSprite::create("bloodbar/enemyblood2.png");
                        chessboardBattle[i][j].second->bloodback = CCSprite::create("bloodbar/blood1back.png");
                    }
                    else
                    {
                        chessboardBattle[i][j].second->bloodbar == CCSprite::create("bloodbar/enemyblood3.png");
                        chessboardBattle[i][j].second->bloodback = CCSprite::create("bloodbar/blood1back.png");
                    }
                    chessboardBattle[i][j].second->bloodback->setAnchorPoint(Vec2(0.8F, 0.5F));  // ����ê��
                    chessboardBattle[i][j].second->bloodbar->setAnchorPoint(Vec2(0.2F, 0.5F));  // ����ê��
                    chessboardBattle[i][j].second->bloodback->setPosition(ccp(40, 70));
                    chessboardBattle[i][j].second->bloodback->setScale(0.1F);
                    chessboardBattle[i][j].second->bloodbar->setPosition(ccp(112, 107));

                    chessboardBattle[i][j].second->addChild(chessboardBattle[i][j].second->bloodback);
                    chessboardBattle[i][j].second->bloodback->addChild(chessboardBattle[i][j].second->bloodbar, 1);
                    
                    


                    chessboardBattle[i][j].second->setPosition(Vec2(290 + 118.4 * j, 295 + 71.2 * i));
                    chessboardBattle[i][j].second->setScale(0.9 + 0.3 * chessboardBattle[i][j].second->getLevel());
                    this->addChild(chessboardBattle[i][j].second, 0);
                    chessboardBattle[i][j].second->setOpacity(255);
                }
            }
            
         
           //Battle(); //��ս

        }
    Battle(); //��ս

    return true;
}

/* Ӣ���ƶ�+��ս */
void BattleScene::Battle() {
    //�����Ļ����Ӣ���ƶ�
    auto touchlistener = EventListenerMouse::create();


    /* ����ССӢ��+Ѫ�� */
    m_pSprite = CCSprite::create("LittleHero/ikun.png");
    m_pblood = CCSprite::create("bloodbar/littleblood.png");
    m_pbloodback = CCSprite::create("bloodbar/littlebloodback.png");

    m_penemy = CCSprite::create("LittleHero/enemy.png");
    m_penemyblood = CCSprite::create("bloodbar/enemyblood.png");
    m_penemybloodback = CCSprite::create("bloodbar/littlebloodback.png");

    // ����ССӢ�� �ҷ�
    m_pSprite->setPosition(ccp(185, 276));
    m_pbloodback->setAnchorPoint(Vec2(0.8, 0.5));  // ����ê��
    m_pblood->setAnchorPoint(Vec2(0.2, 0.5));  // ����ê��
    m_pbloodback->setPosition(ccp(120, 160));
    m_pbloodback->setScale(0.4);
    m_pblood->setPosition(ccp(72, 80));

    m_pSprite->addChild(m_pbloodback);
    m_pbloodback->addChild(m_pblood);
    addChild(m_pSprite, 0);

    //�з�
    m_penemy->setPosition(ccp(1020, 800));
    m_penemybloodback->setAnchorPoint(Vec2(0.8, 0.5));  // ����ê��
    m_penemyblood->setAnchorPoint(Vec2(0.2, 0.5));  // ����ê��
    m_penemybloodback->setPosition(ccp(130, 140));
    m_penemybloodback->setScale(0.4);
    m_penemyblood->setPosition(ccp(72, 80));

    m_penemy->addChild(m_penemybloodback);
    m_penemybloodback->addChild(m_penemyblood);
    addChild(m_penemy, 0);

    //Ѫ����ʼ��
   // m_penemyblood->setScaleX(enemyhero_current_blood / enemyhero_max_blood);

    //// ����������¼�����
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBeganLITTLE, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    int myHero = 0; //�ҷ�Ӣ����
    int opHero = 0; //�Է�Ӣ����
    vector<Hero*>mHero, oHero;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (chessboardBattle[i][j].second != nullptr) {
                if (chessboardBattle[i][j].second->isRed()) {
                    oHero.push_back(chessboardBattle[i][j].second);
                    opHero++;
                }
                else {
                    mHero.push_back(chessboardBattle[i][j].second);
                    myHero++;
                }
            }
        }
    }

    while (opHero && myHero) {
        for (int i = 0; i < mHero.size(); i++) {
            if (mHero[i] == nullptr) {
                continue;
            }
            float mindistance = 999999;
            int min_no = -1;
            for (int j = 0; j < oHero.size(); j++) {
                if (oHero[j] == nullptr) {
                    continue;
                }
                float distance = mHero[i]->getPosition().distance(oHero[j]->getPosition());
                if (distance <= mindistance) {
                    mindistance = distance;
                    min_no = j;
                }
            }

            //if (mindistance <= mHero[i]->getAttackDistance()) {
            if (min_no != -1) {
                oHero[min_no]->changeHP((1 - oHero[min_no]->getDefect() / 200) * mHero[i]->getAttack() + (1 - oHero[min_no]->getAPdefect() / 200) * mHero[i]->getAP());
                oHero[min_no]->bloodbar->setScaleX(oHero[min_no]->getHP() / oHero[min_no]->getFullHP());
                if (oHero[min_no]->getHP() <= 0) {
                    opHero--;
                    oHero[min_no]->removeFromParent();
                    oHero[min_no]->release();
                    oHero[min_no] = nullptr;
                }

               
            }
            /* else {
                 float moveDistance = 100.0f; // �ƶ�����
                 Vec2 targetPosition = oHero[min_no]->getPosition(); // Ŀ��λ��Ϊ�뵱ǰ�ҷ�Ӣ������ĶԷ�Ӣ�۵�λ��
                 Vec2 direction = (targetPosition - mHero[i]->getPosition()).getNormalized(); // �ƶ���������

                 Vec2 destination = mHero[i]->getPosition() + direction * moveDistance; // ����Ŀ���ƶ�λ��

                 // ���� MoveTo ������ʹӢ����Ŀ��λ���ƶ�
                 auto moveTo = MoveTo::create(5.0f, destination);
                 mHero[i]->runAction(moveTo);

                 auto func = [i, targetPosition, destination, this, mHero](float dt) {
                     Vec2 currentPosition = mHero[i]->getPosition();
                     float distance = currentPosition.distance(destination);
                     if (distance <=5) {
                         mHero[i]->stopAllActions();
                         this->unschedule("check_distance");
                     }
                     };

                 this->schedule(func, "check_distance");
             }*/

             //else {
             //    
             //    auto moveTo = MoveTo::create(5.0f, Vec2(640,480)); // ���� MoveBy ������ʹ���������ƶ� 100 ����
             //    Vec2 orgin = mHero[i]->getPosition();
             //    mHero[i]->runAction(moveTo);
             //    auto func = std::bind([]( Vec2 orgin, Sprite* sprite) {
             //        auto currentPosition = sprite->getPosition();
             //        if (currentPosition.distance(orgin) >= 50) {
             //            sprite->stopAllActions();
             //        }
             //        }, orgin, mHero[i]);
             //    schedule(func, "check_distance");
             //}
        }

        for (int i = 0; i < oHero.size(); i++) {
            if (oHero[i] == nullptr) {
                continue;
            }
            float mindistance = 999999;
            int min_no = -1;
            for (int j = 0; j < mHero.size(); j++) {
                if (mHero[j] == nullptr) {
                    continue;
                }
                float distance = oHero[i]->getPosition().distance(mHero[j]->getPosition());
                if (distance <= mindistance) {
                    mindistance = distance;
                    min_no = j;
                }
            }
            //if (mindistance < oHero[i]->getAttackDistance()) {
            if (min_no != -1) {
                mHero[min_no]->changeHP((1 - mHero[min_no]->getDefect() / 200) * oHero[i]->getAttack() + (1 - mHero[min_no]->getAPdefect() / 200) * oHero[i]->getAP());
                
                if (mHero[min_no]->getHP() <= 0) {
                    myHero--;
                    mHero[min_no]->removeFromParent();
                    mHero[min_no]->release();
                    mHero[min_no] = nullptr;
                    mHero.erase(mHero.begin() + min_no);
                }

               
            }
            /* else {
                 float moveDistance = 100.0f; // �ƶ�����
                 Vec2 targetPosition = mHero[min_no]->getPosition(); // Ŀ��λ��Ϊ�뵱ǰ�ҷ�Ӣ������ĶԷ�Ӣ�۵�λ��
                 Vec2 direction = (targetPosition - oHero[i]->getPosition()).getNormalized(); // �ƶ���������

                 Vec2 destination = oHero[i]->getPosition() + direction * moveDistance; // ����Ŀ���ƶ�λ��

                 // ���� MoveTo ������ʹӢ����Ŀ��λ���ƶ�
                 auto moveTo = MoveTo::create(5.0f, destination);
                 oHero[i]->runAction(moveTo);

                 auto func = [i, targetPosition, destination, this, oHero](float dt) {
                     Vec2 currentPosition = oHero[i]->getPosition();
                     float distance = currentPosition.distance(destination);
                     if (distance <= 5) {
                         oHero[i]->stopAllActions();
                         this->unschedule("check_distance");
                     }
                     };

                 this->schedule(func, "check_distance");
             }*/
             /*else {
                 auto moveBy = MoveBy::create(1.0f, 100 * (mHero[min_no]->getPosition() - oHero[i]->getPosition()).getNormalized());
                 oHero[i]->runAction(moveBy);
             }*/
        }
    }
    auto visibleSize = Director::getInstance()->getVisibleSize(); //��Ļ�ɼ�����Ĵ�С
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); //ԭ������   

    auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 75); //������ǩ
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 2 * visibleSize.height / 3)); //��ǩλ��
    label->setTextColor(Color4B::BLACK); //������ɫ
    this->addChild(label, 1); //��ӵ�������

    if (myHero) { //ʤ��        
        label->setString("Win!");
        enemyhero_current_blood -= 20;
        //m_penemyblood->setScaleX(enemyhero_current_blood / enemyhero_max_blood);
    }
    else { //ʧ��
        label->setString("Lose.");
        littlehero_current_blood -= 20;
        //m_pblood->setScaleX(littlehero_current_blood / littlehero_max_blood);
    }

    this->scheduleOnce([&](float dt) {
        coinCount += 5;
        updateButtonState(upbutton);
        shopLabelState();
        // ���¿�ʼ����ʱ
        playscene->currentTime = playscene->totalTime;
        playscene->schedule(schedule_selector(PlayingScene::updateProgressBar), 0.01f);
        Director::getInstance()->popScene();
        }, 5.0f, "delayedCallback");
}

//ССӢ���ƶ�
void BattleScene::moveSpriteTo(Vec2 destination) {

    // ����Ŀ��λ���ڱ߽���
    if ((destination.x > 200 && destination.x < 1050) && (destination.y > 250 && destination.y < 800))
    {
        // �������飬������λ��
        auto click = CCSprite::create("SpecialEffect/click.png");
        click->setPosition(destination);
        // ��������ӵ�����
        addChild(click, 0);
        auto delay = DelayTime::create(0.25f);
        auto removeAction = CallFunc::create([this, click]() {
            // �Ƴ�����
            click->removeFromParent();
            });
        click->runAction(Sequence::create(delay, removeAction, nullptr));
        // ���㾫�鵱ǰλ�ú�Ŀ��λ�õľ���
        float distance = m_pSprite->getPosition().getDistance(destination);
        // �����ƶ���ʱ�䣬����ÿ���ƶ�300������
        float duration = distance / 300.0f;
        // ����һ���ƶ�����
        auto moveToAction = MoveTo::create(duration, destination);
        // �����ƶ�����
        m_pSprite->runAction(moveToAction);
    }
}



//ССӢ�۶������
bool BattleScene::onTouchBeganLITTLE(Touch* touch, Event* event)
{
    // ֹͣ��ǰ���ڽ��е��ƶ�����
    m_pSprite->stopAllActions();
    // ��ȡ�������λ��
    Vec2 touchLocation = touch->getLocation();
    // �����ƶ��������������ƶ����������λ��
    moveSpriteTo(touchLocation);
    return true;  // ����true��ʾ�����˸��¼�
}
