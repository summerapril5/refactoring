#ifndef ATTACKFUNC_H
#define ATTACKFUNC_H

#include "cocos2d.h"
#include <string>
#include <vector>

class AttackFunc : public cocos2d::Sprite {
public:
    static AttackFunc* create(int id, bool is_far, const cocos2d::Vec2& attackerPosition, const cocos2d::Vec2& targetPosition);
    void init(int id, bool is_far, const cocos2d::Vec2& attackerPosition, const cocos2d::Vec2& targetPosition);
    void playAttackAnimation(const cocos2d::Vec2& attackerPosition, const cocos2d::Vec2& targetPosition);

private:
    std::string attackEffect; // 存储当前攻击特效
};

#endif // ATTACKFUNC_H