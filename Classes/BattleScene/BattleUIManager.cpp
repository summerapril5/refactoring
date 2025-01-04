#include "BattleScene.h"

void BattleUIManager::createBackground(Scene* scene, const Size& visibleSize, const Vec2& origin) {
    // 创建背景
    auto background = Sprite::create("ChessBoard/playing.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    scene->addChild(background, 0);
    
    // 创建血条
    m_pblood = CCSprite::create("bloodbar/littleblood.png");
    auto m_pbloodback = CCSprite::create("bloodbar/littlebloodback.png");
    
    m_penemyblood = CCSprite::create("bloodbar/enemyblood.png");
    auto m_penemybloodback = CCSprite::create("bloodbar/littlebloodback.png");
    
    // 设置血条属性
    m_pbloodback->setAnchorPoint(Vec2(0.8F, 0.5F));
    m_pblood->setAnchorPoint(Vec2(0.2F, 0.5F));
    m_pbloodback->setPosition(ccp(120, 160));
    m_pbloodback->setScale(0.4F);
    m_pblood->setPosition(ccp(72, 80));
    
    m_penemybloodback->setAnchorPoint(Vec2(0.8F, 0.5F));
    m_penemyblood->setAnchorPoint(Vec2(0.2F, 0.5F));
    m_penemybloodback->setPosition(ccp(130, 140));
    m_penemybloodback->setScale(0.4F);
    m_penemyblood->setPosition(ccp(72, 80));
    
    // 添加到场景
    scene->addChild(m_pbloodback);
    m_pbloodback->addChild(m_pblood, 1);
    scene->addChild(m_penemybloodback);
    m_penemybloodback->addChild(m_penemyblood, 1);
}

void BattleUIManager::createMenuItems(Scene* scene, const Size& visibleSize, const Vec2& origin) {
    // 创建设置按钮
    auto setMusic = MenuItemImage::create(
        "Music/setting.png",
        "Music/setting.png",
        [scene](Ref* sender) {
            dynamic_cast<BattleScene*>(scene)->menuSetMusicCallback(sender);
        }
    );
    setMusic->setScale(0.5F);
    float x = origin.x + 11 * visibleSize.width / 12;
    float y = origin.y + 8 * visibleSize.height / 9;
    setMusic->setPosition(Vec2(x, y));
    
    // 创建菜单
    auto menu = Menu::create(setMusic, nullptr);
    menu->setPosition(Vec2::ZERO);
    scene->addChild(menu, 1);
}

void BattleUIManager::updateHealthBar(float percentage, bool isEnemy) {
    if (isEnemy) {
        m_penemyblood->setScaleX(percentage);
    } else {
        m_pblood->setScaleX(percentage);
    }
} 