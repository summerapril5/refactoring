#ifndef ATTACKFUNCFACTORY_H
#define ATTACKFUNCFACTORY_H

#include "AttackFunc.h"

class AttackFuncFactory {
public:
    static AttackFunc* create(int id, bool is_far, const Vec2& attackerPosition, const Vec2& targetPosition);
};

#endif // ATTACKFUNCFACTORY_H 