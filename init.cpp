#include "helpers.h"
#include "init.h"
#include "graph.h"
#include <queue>
#include <cassert>

const Tower& readTower(Tower& mogicTower)
{
    if (freopen("input.txt", "r", stdin) == nullptr)
        cout << "��input.txtʧ�ܣ�����stdin�ж�ȡ����" << endl;

    int ign;
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

    return mogicTower;
}


Status getStatus(const Tower& mogicTower)
{
    Position curPos = mogicTower.initialPlayerInfo.getPos();

    int colorMap[MAP_LENGTH][MAP_WIDTH];
    memset(colorMap, 0, sizeof(colorMap));

    int colorCount = traverseMap(mogicTower, colorMap) + 1;

    Status stat;
    stat.nodeContainer.resize(colorCount);

    stat.cur = buildGraph(mogicTower, curPos, colorCount, colorMap, stat.nodeContainer);
    stat.player = mogicTower.initialPlayerInfo;

    /* ��ȡ������ڵ��������Ʒ�����Ϊ�� */
#ifdef DEBUG
    assert(stat.cur->getType() == safeBlock);
#endif

    stat.cur->empty = true;
    stat.blockCount += stat.cur->blockCount;
    stat.player.acquire(stat.cur->obj);

    return stat;
}
