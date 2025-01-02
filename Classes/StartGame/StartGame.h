#ifndef __STARTGAME_SCENE_H__
#define __STARTGAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

/* StartGameScene�� */
class StartGameScene : public Scene {
public:
    static Scene* createScene(); //����һ��Scene
    virtual bool init(); //��ʼ����������
    void menuCloseCallback(Ref* pSender);
    void menuCreateRoomCallback(Ref* pSender);
    void menuSetMusicCallback(Ref* pSender);
    CREATE_FUNC(StartGameScene); //�Զ�����һ��ʵ��
};

#endif