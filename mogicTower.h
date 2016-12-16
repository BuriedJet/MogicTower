#ifndef __MOGIC_TOWER_H
#define __MOGIC_TOWER_H

#include "mogic.h"
#include <iostream>
#include <map>

/* ��¼��ͼ��Ϣ��ö�ٽṹ */
enum MapObj
{
    road = 10,
    wall,

    yellowKey = 21,
    blueKey,
    redKey,
    redDiamond,
    blueDiamond,
    greenDiamond,
    smallBottle,
    largeBottle,

    yellowDoor = 31,
    blueDoor,
    redDoor,

    monster51 = 51,
    monster52,
    monster53,
    monster54,
    monster55,
    monster56,
    monster57,
    monster58,
    monster59,
    monster60,
    monster61,
    monster62,
    monster63,
    monster64, 
    monster65,
    monster66,
    monster67,
    monster68,
    monster69,
    monster70,

    boss = 99
};

/* ����ֱ�Ӷ���ö��ֵ�ĺ��� */
inline istream& operator >> (istream& in, MapObj& m)
{
    int tmp;
    in >> tmp;
    m = MapObj(tmp);
    return in;
}

struct Position
{
    int x, y;
};

/* ��¼�����Ϣ�����ݽṹ */
class Player
{
private:
    int hp;         /* Ѫ�� */
    int atk;        /* ���� */
    int def;        /* ���� */
    int mdef;       /* ħ�� */
    Position pos;   /* λ�� */

public:
    Player() {}
    Player(int _hp, int _atk, int _def, int _mdef)
    {
        hp = _hp, atk = _atk, def = _def, mdef = _mdef;
    }
    friend istream& operator >> (istream& in, Player& m)
    {
        in >> m.hp >> m.atk >> m.def >> m.mdef >> m.pos.x >> m.pos.y;
        return in;
    }

	int getATK() const { return atk; }
	int getDEF() const { return def; }
	int getMDEF() const { return mdef; }
	int getHP() const { return hp; }
};

/* ��¼������Ϣ�����ݽṹ */
class Monster
{
private:
    int hp;     /* Ѫ�� */
    int atk;    /* ������ */
    int def;    /* ������ */
    int spe;    /* ��Ч */

public:
    Monster() {}
    Monster(int _hp, int _atk, int _def, int _spe)
    {
        hp = _hp, atk = _atk, def = _def, spe = _spe;
    }

    friend istream& operator >> (istream& in, Monster& m)
    {
        in >> m.hp >> m.atk >> m.def >> m.spe;
        return in;
    }

	int getATK() const { return atk; }
	int getDEF() const { return def; }
	int getSPE() const { return spe; }
	int getHP() const { return hp; }
};

/*ȫ�ּ�¼����Ϣ�����ݽṹ */
struct Tower
{
    /* ¥���ͼ��С��¥��������ǰ�̶�Ϊ1 * 13 * 13 */
    //int height;
    //int len, wid;

    /* ��ö�ټ�¼��ͼ���� */
    MapObj mapContent[MAP_LENGTH][MAP_WIDTH];

    /* ��¼���ӳ�ֵ */
    int buff[5];

    /* ��¼�������� */
    map<MapObj, Monster> monsterInfo;

    /* ��¼��ʼ������� */
    Player initialPlayerInfo;
};


#endif