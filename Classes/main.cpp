#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC; //cocos2d�����ռ�

/* _tWinMain���� ��WindowsӦ�ó�����ں��� �����׼main���� */
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    /* �������뾯�� */
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    AppDelegate app; //����AppDelegate���� ���������Ϸ���������ڡ�ƽ̨�����Ե�����
    return Application::getInstance()->run(); //����Ӧ�ó��� ������Ϸ����ѭ��
}