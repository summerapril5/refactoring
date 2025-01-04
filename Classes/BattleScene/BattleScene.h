#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../PlayingScene/PlayingScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

// 观察者接口
class IBattleObserver {
public:
    virtual ~IBattleObserver() {}
    virtual void onHeroHealthChanged(int heroId, int oldHealth, int newHealth, bool isEnemy) = 0;
    virtual void onBattleStateChanged(const std::string& state) = 0;
};

// 音效管理器接口
class IAudioManager {
public:
    virtual ~IAudioManager() {}
    virtual void playBackgroundMusic(const std::string& file, bool loop) = 0;
    virtual void playEffect(const std::string& file) = 0;
    virtual void stopBackgroundMusic() = 0;
    virtual void setBackgroundMusicVolume(float volume) = 0;
};

// 具体的音效管理器实现
class BattleAudioManager : public IAudioManager {
public:
    virtual void playBackgroundMusic(const std::string& file, bool loop) override {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(file.c_str(), loop);
    }
    
    virtual void playEffect(const std::string& file) override {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(file.c_str());
    }
    
    virtual void stopBackgroundMusic() override {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    
    virtual void setBackgroundMusicVolume(float volume) override {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    }
};

// UI管理器接口
class IUIManager {
public:
    virtual ~IUIManager() {}
    virtual void createBackground(Scene* scene, const Size& visibleSize, const Vec2& origin) = 0;
    virtual void createMenuItems(Scene* scene, const Size& visibleSize, const Vec2& origin) = 0;
    virtual void updateHealthBar(float percentage, bool isEnemy) = 0;
};

// 具体的UI管理器实现
class BattleUIManager : public IUIManager {
private:
    CCSprite* m_pblood;
    CCSprite* m_penemyblood;
    
public:
    virtual void createBackground(Scene* scene, const Size& visibleSize, const Vec2& origin) override;
    virtual void createMenuItems(Scene* scene, const Size& visibleSize, const Vec2& origin) override;
    virtual void updateHealthBar(float percentage, bool isEnemy) override;
};

/* BattleScene类 */
class BattleScene : public Scene {
public:
    static Scene* createScene(); //创建一个Scene
    virtual bool init(); //初始化场景内容
    void menuSetMusicCallback(Ref* pSender);
    void releaseScene();
    void Battle();
    CREATE_FUNC(BattleScene);

    // 依赖注入相关方法
    void setAudioManager(IAudioManager* audioManager) { this->audioManager = audioManager; }
    void setUIManager(IUIManager* uiManager) { this->uiManager = uiManager; }
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void moveSpriteTo(Vec2 destination);
    bool onTouchBeganLITTLE(Touch* touch, Event* event);

    // 观察者模式相关方法
    void addObserver(IBattleObserver* observer);
    void removeObserver(IBattleObserver* observer);
    void notifyHealthChanged(int heroId, int oldHealth, int newHealth, bool isEnemy);
    void notifyBattleStateChanged(const std::string& state);

    EventListenerMouse* touchlistener;
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

private:
    std::vector<IBattleObserver*> observers;
    IAudioManager* audioManager;
    IUIManager* uiManager;
};

#endif