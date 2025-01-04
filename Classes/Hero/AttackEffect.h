#ifndef ATTACKEFFECT_H
#define ATTACKEFFECT_H

#include <string>
#include <vector>
#include "cocos2d.h"

class AttackEffect {
public:
    virtual void init(const cocos2d::Vec2& attackerPosition, const cocos2d::Vec2& targetPosition) = 0;
    virtual ~AttackEffect() {}
};

#endif // ATTACKEFFECT_H 