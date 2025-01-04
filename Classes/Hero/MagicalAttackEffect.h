#ifndef MAGICALATTACKEFFECT_H
#define MAGICALATTACKEFFECT_H

#include "AttackEffect.h"

class MagicalAttackEffect : public AttackEffect {
public:
    void init(const cocos2d::Vec2& attackerPosition, const cocos2d::Vec2& targetPosition) override {
        // 魔法攻击特效的初始化逻辑
    }
};

#endif // MAGICALATTACKEFFECT_H 