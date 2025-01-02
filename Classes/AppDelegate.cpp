#include "AppDelegate.h"
#include"LoadingScene/LoadingScene.h"
USING_NS_CC;

static Size designResolutionSize = Size(1280, 960); //�ֱ���
static Size smallResolutionSize = Size(480, 320);
static Size mediumResolutionSize = Size(1024, 768);
static Size largeResolutionSize = Size(2048, 1536);

#define USE_SIMPLE_AUDIO_ENGINE 1 //��Ƶ����
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

/* ���캯�� */
AppDelegate::AppDelegate() {

}

/* �������� */
AppDelegate::~AppDelegate() {
    SimpleAudioEngine::end(); //������Ƶ�����ʹ��
}

/* ����OpenGL�����ĵ����� */
void AppDelegate::initGLContextAttrs() {
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0}; 
    //����GLContextAttrs�ṹ�� �������Ա��ֵ������OpenGL�����ĵ�����
    //���ԣ�red green blue alpha depth stencil multisamplesCount
    GLView::setGLContextAttrs(glContextAttrs);
    //������õ�����Ӧ�õ�OpenGL��ͼ��
}

/* ע�����еİ���packages��*/
static int register_all_packages() {
    return 0; //����������package manager���ı�־ֵ
}

/* ��ʼ��Director�ͳ��� */
bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance(); //��ʼ��Director
    auto glview = director->getOpenGLView(); //��ȡ��ǰOpenGL��ͼ

    if(!glview) { //��ǰû��OpenGL��ͼ
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) //Windows Mac Linux
        glview = GLViewImpl::createWithRect("Jinchanchan", Rect(0, 0, designResolutionSize.width, designResolutionSize.height)); //����һ��OpenGL��ͼ
#else
        glview = GLViewImpl::create("Jinchanchan");
#endif
        director->setOpenGLView(glview); //��������OpenGL��ΪDirector�ĵ�ǰOpenGL��ͼ
    }

    //director->setDisplayStats(true); //����ʾ֡�ʵ�����
    director->setAnimationInterval(1.0f / 60); //ÿ��60֡

    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER); //���÷ֱ���
    auto frameSize = glview->getFrameSize(); //��ȡ��ǰOpenGL��ͼ��С
   
    if (frameSize.height > mediumResolutionSize.height)
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    else if (frameSize.height > smallResolutionSize.height) 
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    else //��
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    
    register_all_packages(); //ע������packages

    auto loading = LoadingScene::createScene(); //����һ��LoadingScene����
    director->runWithScene(loading); //����Director ��scene��Ϊ��ǰ���г���

    return true;
}

/* ��������̨ʱ���� */
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation(); //ֹͣ������Ⱦ ����ͣ��Ϸ����ĸ���

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //��ͣ��������
    SimpleAudioEngine::getInstance()->pauseAllEffects(); //��ͣ������Ч
}

/* �������½���ǰ̨ʱ���� */
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation(); //��ʼ������Ⱦ ���ָ���Ϸ����ĸ���

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); //�ָ��������ֵĲ���
    SimpleAudioEngine::getInstance()->resumeAllEffects(); //�ָ�������Ч�Ĳ���
}