#ifndef PHYSICALATTACKEFFECT_H
#define PHYSICALATTACKEFFECT_H

#include "AttackEffect.h"

class PhysicalAttackEffect : public AttackEffect {
public:
    void init(const cocos2d::Vec2& attackerPosition, const cocos2d::Vec2& targetPosition) override {
        // 物理攻击特效的初始化逻辑
    }
};

#endif // PHYSICALATTACKEFFECT_H 