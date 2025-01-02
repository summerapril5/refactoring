#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/* AppDelegate�� */
class AppDelegate : private cocos2d::Application { //cocos2d::Application��˽��������
public:
    AppDelegate(); //���캯��
    virtual ~AppDelegate(); //��������

    virtual void initGLContextAttrs(); //��ʼ��OpenGL����
    virtual bool applicationDidFinishLaunching(); //��ʼ��Director�ͳ���

    virtual void applicationDidEnterBackground();  //��������̨ʱ����
    virtual void applicationWillEnterForeground(); //�������½���ǰ̨ʱ����
};

#endif 