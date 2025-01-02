#pragma once
/*
*������Ч��
*���ݲ�ͬ��Ӣ��id�󶨲�ͬ�Ĺ�����Ч
*/
#ifndef  _ATTACK_EFFECT_H_
#define  _ATTACK_EFFECT_H_

#include "cocos2d.h"
USING_NS_CC;

//������Ч��
class AttackFunc :public Sprite
{
public:
	static AttackFunc* create(int id,bool is_far, const Vec2& attackerPosition, const Vec2& targetPosition);//����id����������Ч ������������Ϊ�����ߺͱ������ߵ�λ��
	void init(int id, bool is_far, const Vec2& attackerPosition, const Vec2& targetPosition);//������ЧͼƬ�ĳ�ʼ��

    // ���һ����������������������Ч���ƶ�����
    void playAttackAnimation(const Vec2& attackerPosition, const Vec2& targetPosition);

private:
    // �洢������Ч��Ŀ��λ��
    Vec2 targetPosition;
};

#endif