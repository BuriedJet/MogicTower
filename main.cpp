#define DEBUG

#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <queue>
#include "mogic.h"
#include "damage.h"

using namespace std;

Tower mogicTower;

const int HP_Multiple = 5;
const int ATK_Multiple = 4;
const int DEF_Multiple = 7;
const int MDEF_Multiple = 6;

/* 0123:�������� */
const int dx[4] = { -1,1,0,0 };
const int dy[4] = { 0,0,-1,1 };
/* ħ���ع�ͼ�ڵ�ṹ */
struct node 
{
    bool valid;         /* ���ʸýڵ��valid��Ϊfalse */
    Position pos;       /* �ýڵ������ */
    MapObj type;        /* �ýڵ����ͣ��Ż��� */
	vector<node*> next; /* �ӽڵ��б� */
    vector<MapObj> obj; /* �ڵ���Ʒ�б� */
    int blockCount;     /* �ýڵ����ӵ���ͨ����� */
};
node* head = nullptr;

int evalCurrentStatus(const node &status);

int been[MAP_LENGTH][MAP_WIDTH];
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
bool isMonster(int x, int y) {
	if ((mogicTower.mapContent[x][y] >= 51 && mogicTower.mapContent[x][y] <= 70) || mogicTower.mapContent[x][y] == boss)
		return true;
	return false;
}
bool isDoor(int x, int y) {
	if (mogicTower.mapContent[x][y] >= 31 && mogicTower.mapContent[x][y] <= 33)
		return true;
	return false;
}
bool isItem(int x, int y) {
	if (mogicTower.mapContent[x][y] >= 21 && mogicTower.mapContent[x][y] <= 28)
		return true;
	return false;
}
void searchArea(node* cur) {	//����cur����������ڷ������
	int x, y;
	cur->blockCount = 0;
	auto& map = mogicTower.mapContent;
	queue<Position> q;
	q.push(cur->pos);
	cur->type = map[cur->pos.x][cur->pos.y];
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		for (int i = 0; i < 4; i++) {
			if (been[x + dx[i]][y + dy[i]])	//ȥ����
				continue;
			if (map[x + dx[i]][y + dy[i]] == wall)	//ǽ
				continue;
			if (isMonster(x + dx[i], y + dy[i]) || isDoor(x + dx[i], y + dy[i])) {	//�������
				node* temp = new node();
				temp->pos.x = x + dx[i];
				temp->pos.y = y + dy[i];
				cur->next.push_back(temp);
				been[x + dx[i]][y + dy[i]] = 1;
				continue;
			}
			if (isItem(x + dx[i], y + dy[i])) {	//��Ʒ
				cur->obj.push_back(mogicTower.mapContent[x + dx[i]][y + dy[i]]);
				been[x + dx[i]][y + dy[i]] = 1;
				Position temp;
				temp.x = x + dx[i];
				temp.y = y + dy[i];
				q.push(temp);
				cur->blockCount++;
				continue;
			}
			if (map[x + dx[i]][y + dy[i]] == road) {	//��·
				been[x + dx[i]][y + dy[i]] = 1;
				Position temp;
				temp.x = x + dx[i];
				temp.y = y + dy[i];
				q.push(temp);
				cur->blockCount++;
				continue;
			}
			cout << "Error" << endl;
			PAUSE;
		}
		q.pop();
	}
	for (int i = 0; i < (int)cur->next.size(); i++)
		searchArea(cur->next[i]);
}
int main()
{
    readTower();
	head = new node();
    head->pos = mogicTower.initialPlayerInfo.getPos();
	memset(been, 0, sizeof(been));
	been[head->pos.x][head->pos.y] = 1;
	searchArea(head);
	head->type = player;
    PAUSE;
}


int evalCurrentStatus(const node &status)
{
	int tmpRank = 0;
	tmpRank += status.player->getATK() * ATK_Multiple;
	tmpRank += status.player->getHP() * HP_Multiple;
	tmpRank += status.player->getDEF() * DEF_Multiple;
	tmpRank += status.player->getMDEF() * MDEF_Multiple;
	
	/* TODO: ��player����λ����ͨ�Զ�Ȩֵ��Ӱ�� */
	return tmpRank;
}