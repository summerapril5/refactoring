#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

/* LoadingScene�� */
class LoadingScene : public Scene {
public:
    static Scene* createScene(); //����һ��Scene
    virtual bool init(); //��ʼ����������
    CREATE_FUNC(LoadingScene); //�Զ�����һ��ʵ��
};

#endif