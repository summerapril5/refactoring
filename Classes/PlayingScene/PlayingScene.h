#ifndef __PLAYING_SCENE_H__
#define __PLAYING_SCENE_H__

#include "cocos2d.h"
#include "../Hero/hero.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

/* PlayingScene�� */
class PlayingScene : public Scene {
public:
    static Scene* createScene(); //����һ��Scene
    virtual bool init(); //��ʼ����������
    cocos2d::ProgressTimer* timer; // ����������
    cocos2d::Sprite* progressBackground; // �������ײ�����
    cocos2d::Label* timeLabel; // ʣ��ʱ���ǩ
    float totalTime; // ��ʱ��
    float currentTime; // ��ǰʱ��
    bool isDragging;//����Ƿ������϶�
    cocos2d::Vec2 initialPosition;//��ʼλ��
    // ���½�������ʱ���ǩ
    void updateProgressBar(float dt);
    void menuCloseCallback(Ref* pSender);
    void menuSetMusicCallback(Ref* pSender);
    void shoponButtonClicked(Ref* sender);
    void uponButtonClicked(Ref* sender);
    void onMouseDown(EventMouse* event);
    void onMouseMove(EventMouse* event);
    void onMouseUp(EventMouse* event);
    CREATE_FUNC(PlayingScene); //�Զ�����һ��ʵ��

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    static void randCard();
    EventListenerMouse* touchlistener; // ����¼�������

    //���������Ƕ���һ������ָ��
    CCSprite* m_pSprite;
    CCSprite* m_penemy;
    CCSprite* m_pblood;
    CCSprite* m_pbloodback;
    CCSprite* m_penemyblood;
    CCSprite* m_penemybloodback;
    int littlehero_max_blood = 100;
    int littlehero_current_blood = 100;
};

#endif