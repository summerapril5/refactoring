#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../PlayingScene/PlayingScene.h"
USING_NS_CC;

/* BattleScene�� */
class BattleScene : public Scene {
public:
    static Scene* createScene(); //����һ��Scene
    virtual bool init(); //��ʼ����������
    void menuSetMusicCallback(Ref* pSender);
    void releaseScene();
    void Battle();
    CREATE_FUNC(BattleScene); //�Զ�����һ��ʵ��
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void moveSpriteTo(Vec2 destination);
    bool onTouchBeganLITTLE(Touch* touch, Event* event);
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
    int enemyhero_max_blood = 100;
    int enemyhero_current_blood = 100;
};

#endif