#include "AttackFuncFactory.h"

AttackFunc* AttackFuncFactory::create(int id, bool is_far, const Vec2& attackerPosition, const Vec2& targetPosition) {
    AttackFunc* effect = new AttackFunc();
    effect->init(id, is_far, attackerPosition, targetPosition);
    effect->autorelease(); // 将对象加入到自动释放池中，避免手动管理内存
    return effect;
} 