#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

/* PopupLayer�� */
/* ���������㣬��ʾ���ƺ�ˢ�°�ť�����������¼� */
class PopupLayer : public LayerColor {
public:
    CREATE_FUNC(PopupLayer); //ʵ����PopupLayer

    void Cardsinit(); //��ʼ������
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event); //�������¼�

    bool init(); //��ʼ�������� 

    void reonButtonClicked(Ref* sender);

    void hide(); //���ص�����
};

#endif