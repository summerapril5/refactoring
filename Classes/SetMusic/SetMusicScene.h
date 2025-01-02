#ifndef __SETMUSIC_SCENE_H__
#define __SETMUSIC_SCENE_H__

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
USING_NS_CC;

/* SetMusicScene�� */
class SetMusicScene : public Scene {
private:
    Sprite* switchMusic;  //���ſ�ʼ/��ͣ
    bool isMusicPlaying;  //���ֲ���״̬
    Label* volumeLabel;   //�������ٷֱ�

public:
    static Scene* createScene(); //����һ��Scene
    virtual bool init(); //��ʼ����������
    void menuCloseCallback(Ref* pSender);
    bool onSwitchMusicTouched(Touch* touch, Event* event);
    void volumeSliderCallback(Ref* sender, ui::Slider::EventType eventType);
    CREATE_FUNC(SetMusicScene); //�Զ�����һ��ʵ��
};

#endif