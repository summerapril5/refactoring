#ifndef  _HERO_H_
#define  _HERO_H_

#include "cocos2d.h"
#include <cstdlib> 
#include <ctime> 
USING_NS_CC;

/* Ӣ�۾����� */
class Hero :public Sprite {
protected:
    /* Ӣ������ */
    int attack; //��������ÿ�ι�����ɵ��˺���
    int defect; //��������Ӣ�۵����˺���������  

    int AP;       //��ǿ��Ӣ�۵ķ�������������  
    int APdefect; //�������Է����˺��ĵֿ�������      

    int HP;     //Ѫ��������ֵ��
    int FullHP; //��Ѫ�����������ֵ��

    int MP;     //��������ǰ�ķ���ֵ��      
    int FullMP; //�������������ֵ��    

    int cost; //���ã�Ӣ�۹���������������

    int attackDistance; //������Χ

    bool survival; //�Ƿ���

    bool red; //�Ƿ��ǵз���Ӫ

    double move_speed; //�ƶ��ٶ�
    int attack_speed;  //�����ٶ�

    int level; //�Ǽ���һ��/����/���ǣ�
    

public:  
    //Ѫ��
    Sprite* bloodbar;
    Sprite* bloodback;
    /* ���캯�� */
    Hero(bool red, int level) : red(red), level(level) {
        survival = true;
        move_speed = 1;
        attack_speed = 1;
    }

    /* ��ȡ������ */ 
    int getAttack() {
        return attack;
    }

    /* ��ȡ������ */
    int getDefect() {
        return defect;
    }

    /* ��ȡ��ǿ */
    int getAP() {
        return AP;
    }

    /* ��ȡ���� */
    int getAPdefect() {
        return APdefect;
    }

    /* ��ȡѪ�� */
    int getHP() {
        return HP;
    }
    void changeHP(int hurt) {
        HP -= hurt;
       
    }

    /* ��ȡ��Ѫ�� */
    int getFullHP() {
        return FullHP;
    }

    /* ��ȡ���� */
    int getMP() {
        return MP;
    }

    /* ��ȡ������ */
    int getFullMP() {
        return FullMP;
    }

    /* ��ȡ���� */
    int getCost() {
        return cost;
    }

    /* ��ȡ������Χ */
    int getAttackDistance() {
        return attackDistance;
    }

    /* ��ȡ�Ƿ��� */
    bool isSurvival() {
        return survival;
    }

    void dead() {
        survival = false;
    }

    /* ��ȡ�Ƿ��ǵз���Ӫ */
    bool isRed() {
        return red;
    }

    /* ��ȡ�ƶ��ٶ� */
    double getMoveSpeed() {
        return move_speed;
    }

    /* ��ȡ�����ٶ� */
    int getAttackSpeed() {
        return attack_speed;
    }

    /* ��ȡ�Ǽ� */
    int getLevel() {
        return level;
    }
    void upLevel() {
        level++;
    }

    virtual void useSkill() {

    }
    //�����߼�

    cocos2d::Sprite* blood;
};

/* ����̹��-0 */
class HeroPhysicalTank : public Hero {
public:
    /* ���캯�� */
    HeroPhysicalTank(bool red, int level) : Hero(red, level) {
        attack = 30;
        defect = 200;
        AP = 0;
        APdefect = 100;
        FullHP = HP = 500;
        MP = 20;
        FullMP = 50;
        cost = 1;
        attackDistance = 1;

        if (level == 2) { //����Ӣ��

        }
        else if (level == 3) { //����Ӣ��

        }
    }

    void useSkill() override {
        //�����߼�
    }
};

/* ħ��̹��-1 */
class HeroMagicTank : public Hero {
public:
    /* ���캯�� */
    HeroMagicTank(bool red, int level) : Hero(red, level) {
        attack = 20;
        defect = 100;
        AP = 40;
        APdefect = 200;
        FullHP = HP = 400;
        MP = 30;
        FullMP = 40;
        cost = 2;
        attackDistance = 100;

        if (level == 2) { //����Ӣ��

        }
        else if (level == 3) { //����Ӣ��

        }
    }

    void useSkill() override {
        //�����߼�
    }
};

/* ����սʿ-2 */
class HeroPhysicalWarrior : public Hero {
public:
    /* ���캯�� */
    HeroPhysicalWarrior(bool red, int level) : Hero(red, level) {
        attack = 70;
        defect = 100;
        AP = 30;
        APdefect = 100;
        FullHP = HP = 350;
        MP = 0;
        FullMP = 30;
        cost = 3;
        attackDistance = 150;

        if (level == 2) { //����Ӣ��

        }
        else if (level == 3) { //����Ӣ��

        }
    }

    void useSkill() override {
        //�����߼�
    }
};

/* ħ��սʿ-3 */
class HeroMagicalWarrior : public Hero {
public:
    /* ���캯�� */
    HeroMagicalWarrior(bool red, int level) : Hero(red, level) {
        attack = 30;
        defect = 100;
        AP = 60;
        APdefect = 100;
        FullHP = HP = 350;
        MP = 10;
        FullMP = 50;
        cost = 1;
        attackDistance = 150;

        if (level == 2) { //����Ӣ��

        }
        else if (level == 3) { //����Ӣ��

        }
    }

    void useSkill() override {
        //�����߼�
    }
};

/* ����-4 */
class HeroMarksman : public Hero {
public:
    /* ���캯�� */
    HeroMarksman(bool red, int level) : Hero(red, level) {
        attack = 80;
        defect = 50;
        AP = 30;
        APdefect = 50;
        FullHP = HP = 250;
        MP = 20;
        FullMP = 50;
        cost = 2;
        attackDistance = 400;

        if (level == 2) { //����Ӣ��

        }
        else if (level == 3) { //����Ӣ��

        }
    }

    void useSkill() override {
        //�����߼�
    }
};

/* ��ʦ-5 */
class HeroMage : public Hero {
public:
    /* ���캯�� */
    HeroMage(bool red, int level) : Hero(red, level) {
        attack = 0;
        defect = 50;
        AP = 100;
        APdefect = 50;
        FullHP = HP = 250;
        MP = 30;
        FullMP = 60;
        cost = 3;
        attackDistance = 400;

        if (level == 2) { //����Ӣ��

        }
        else if (level == 3) { //����Ӣ��

        }
    }

    void useSkill() override {
        //�����߼�
    }
};

#endif