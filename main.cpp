#define DEBUG

#include <iostream>
#include <vector>
#include "mogic.h"
#include "damage.h"

using namespace std;

Tower mogicTower;

const int HP_Multiple = 5;
const int ATK_Multiple = 4;
const int DEF_Multiple = 7;
const int MDEF_Multiple = 6;
int evalCurrentStatus(const node &status);

/* ħ���ع�ͼ�ڵ�ṹ */
struct node 
{
    bool valid;         /* ���ʸýڵ��valid��Ϊfalse */
    Position pos;       /* �ýڵ������ */
    MapObj type;        /* �ýڵ����ͣ��Ż��� */
	vector<node*> next; /* �ӽڵ��б� */
    vector<MapObj> obj; /* �ڵ���Ʒ�б� */
	Player *player;		/* ��ǰ�ڵ㴦�������״̬ */
    int blockCount;     /* �ýڵ����ӵ���ͨ����� */
};
node* head = nullptr;

void readTower()
{
    if (freopen("input.txt", "r", stdin) == nullptr)
        cout << "��input.txtʧ�ܣ�����stdin�ж�ȡ����" << endl;

    int ign;;
    cin >> ign >> ign >> ign;

    for (size_t i = 0; i < MAP_LENGTH; ++i)
        for (size_t j = 0; j < MAP_LENGTH; ++j)
            cin >> mogicTower.mapContent[i][j];

    for (size_t i = 0; i < 5; i++)
        cin >> mogicTower.buff[i];

    int monsterTypeCount;
    cin >> monsterTypeCount;
    while (monsterTypeCount--)
    {
        MapObj key;
        Monster tmpMon;
        cin >> key >> tmpMon;
        mogicTower.monsterInfo[key] = tmpMon;
    }

    cin >> mogicTower.initialPlayerInfo;
}

bool isMonster(int x, int y) {	//��ʱ����boss
	if (mogicTower.mapContent[x][y] >= 51 && mogicTower.mapContent[x][y] <= 70)
		return true;
	return false;
}
bool isDoor(int x, int y) {
	if (mogicTower.mapContent[x][y] >= 31 && mogicTower.mapContent[x][y] <= 33)
		return true;
	return false;
}
void makeTree(node* cur) {
	//if()
}

int main()
{
    readTower();
	head = new node();
    head->pos = mogicTower.initialPlayerInfo.getPos();
	makeTree(head);
    PAUSE;
}


int evalCurrentStatus(const node &status)
{
	int tmpRank = 0;
	tmpRank += status.player->getATK() * ATK_Multiple;
	tmpRank += status.player->getHP() * HP_Multiple;
	tmpRank += status.player->getDEF() * DEF_Multiple;
	tmpRank += status.player->getMDEF() * MDEF_Multiple;
	
	/*to do: ��player����λ����ͨ�Զ�Ȩֵ��Ӱ��*/
	return tmpRank;
}