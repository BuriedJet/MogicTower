#include "mogic.h"
#include "mogicTower.h"
#include <vector>


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

typedef node* Status;

int eval(const Status& stat);
void trans(const Status& cur, const Status& target);
void restore();

int search(const Status& stat, int depth)
{
    if (depth == MAX_DEPTH)
        return eval(stat);

    size_t nodeCount = stat->next.size();
    for (size_t i = 0; i < nodeCount; ++i)
    {
        Status& cur = stat->next[i];
        trans(stat, cur);
        search(cur, depth + 1);
        restore();
    }


}