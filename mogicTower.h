#ifndef __MOGIC_TOWER_H
#define __MOGIC_TOWER_H

#include "mogic.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

/* ��¼��ͼ��Ϣ��ö�ٽṹ */
enum MapObj
{
	safeblock = 0,

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

    Position(int _x = 0, int _y = 0): x(_x), y(_y) {}
};

/* ��¼�����Ϣ�����ݽṹ */
class PlayerInfo
{
private:
    int hp;         /* Ѫ�� */
    int atk;        /* ���� */
    int def;        /* ���� */
    int mdef;       /* ħ�� */

    int keys[3];    /* ��Կ����Ŀ */

    Position pos;   /* λ�� */

public:
    PlayerInfo() { hp = atk = def = mdef = keys[0] = keys[1] = keys[2] = pos.x = pos.y = 0; }
    friend istream& operator >> (istream& in, PlayerInfo& m)
    {
        in >> m.hp >> m.atk >> m.def >> m.mdef >> m.pos.x >> m.pos.y;
        return in;
    }

	int getATK() const { return atk; }
	int getDEF() const { return def; }
	int getMDEF() const { return mdef; }
	int getHP() const { return hp; }
	int getY_KEY() const { return keys[0]; }
	int getB_KEY() const { return keys[1]; }
	int getR_KEY() const { return keys[2]; }
	const Position& getPos() const { return pos; }
    void acquire(vector<MapObj>& objList);
    bool fight(MapObj monsterType);
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
    PlayerInfo initialPlayerInfo;
};

/* ħ���ع�ͼ�ڵ�ṹ */
struct GraphNode
{
    int index;              /* �ýڵ�����ֵ�������Ⱦ����ɫ�� */
    bool empty;             /* ���ʸýڵ��empty��Ϊtrue */
    Position pos;           /* �ýڵ������ */
    MapObj type;            /* �ýڵ����� */
    set<GraphNode*> next;   /* �ڽӽڵ��б� */
    vector<MapObj> obj;     /* �ڵ���Ʒ�б� */
    int blockCount;         /* �ýڵ����ӵ���ͨ����� */
};

/* ״̬ת�ƽṹ */
struct Status
{
    GraphNode* head;
    PlayerInfo player;
    int blockCount;

    GraphNode* nodeContainer;
    GraphNode* nodeBackUp;
};


#endif

