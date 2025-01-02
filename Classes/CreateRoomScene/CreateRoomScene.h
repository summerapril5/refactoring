#ifndef __CREATEROOM_SCENE_H__
#define __CREATEROOM_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

/* CreateRoomScene�� */
class CreateRoomScene : public Scene {
public:
    static Scene* createScene(); //����һ��Scene
    virtual bool init(); //��ʼ����������
    void menuCloseCallback(Ref* pSender);
    void menuStartGameCallback(Ref* pSender);
    void menuSetMusicCallback(Ref* pSender);
    CREATE_FUNC(CreateRoomScene); //�Զ�����һ��ʵ��
};

#endif