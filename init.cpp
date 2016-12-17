#include "mogicTower.h"
#include "helpers.h"
#include "init.h"
#include <queue>
#include <cassert>

const Tower& readTower()
{
    if (freopen("input.txt", "r", stdin) == nullptr)
        cout << "��input.txtʧ�ܣ�����stdin�ж�ȡ����" << endl;

    int ign;
    cin >> ign >> ign >> ign;

    static Tower mogicTower;

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

    return  mogicTower;
}


static void colorize(const Tower& mogicTower, int x, int y, const int color, int colorMap[MAP_LENGTH][MAP_WIDTH])
{
    if (colorMap[x][y] != 0)
        return;
    auto& map = mogicTower.mapContent;
    colorMap[x][y] = color;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!isInRange(nx, ny))
            continue;
        if (map[nx][ny] == wall)
            continue;
        if (isMonster(mogicTower, nx, ny))
            continue;
        if (isDoor(mogicTower, nx, ny))
            continue;
        colorize(mogicTower, nx, ny, color, colorMap);
    }
}

static int traverseMap(const Tower& mogicTower, int colorMap[MAP_LENGTH][MAP_WIDTH])
{
    int color = 0;
    auto& map = mogicTower.mapContent;
    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            if (colorMap[i][j] != 0)
                continue;
            if (isMonster(mogicTower, i, j) || isDoor(mogicTower, i, j))
            {
                colorMap[i][j] = ++color;
                continue;
            }
            colorize(mogicTower, i, j, ++color, colorMap);
        }
    return color;
}

static GraphNode *buildGraph(const Tower& mogicTower, const Position& headpos, int colorCount, int colorMap[MAP_LENGTH][MAP_WIDTH], GraphNode* nodeContainer)
{
    static vector<GraphNode *> nodes(colorCount);
    auto& map = mogicTower.mapContent;

    for (int i = 0; i < colorCount; ++i)
        nodes[i] = nullptr;

    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            if (nodes[colorMap[i][j]] == nullptr)
            { // ����ɫû�н����
                nodes[colorMap[i][j]] = nodeContainer + colorMap[i][j];
                nodes[colorMap[i][j]]->empty = false;
                nodes[colorMap[i][j]]->pos.x = i; nodes[colorMap[i][j]]->pos.y = j;
                nodes[colorMap[i][j]]->blockCount = 1;

                if (map[i][j] == road || isItem(mogicTower, i, j))
                    nodes[colorMap[i][j]]->type = safeblock; // road����Ʒ����safeblock
                else
                    nodes[colorMap[i][j]]->type = map[i][j]; // ��,����
            }
            else
                nodes[colorMap[i][j]]->blockCount++;

            if (isItem(mogicTower, i, j)) // ��¼��������Ʒ
                nodes[colorMap[i][j]]->obj.push_back(map[i][j]);
        }

    for (int i = 0; i < MAP_LENGTH; ++i)
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == wall)
                continue;
            for (int k = 0; k < 4; ++k)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (!isInRange(nx, ny))
                    continue;
                if (map[nx][ny] == wall)
                    continue;
                if (colorMap[i][j] != colorMap[nx][ny])
                    if (nodes[colorMap[i][j]]->next.find(nodes[colorMap[nx][ny]]) == nodes[colorMap[i][j]]->next.end())
                        nodes[colorMap[i][j]]->next.insert(nodes[colorMap[nx][ny]]);

            }
        }
    return nodes[colorMap[headpos.x][headpos.y]];
}


const Status& getInitialStatus(const Tower& mogicTower)
{
    Position headpos = mogicTower.initialPlayerInfo.getPos();

    static int colorMap[MAP_LENGTH][MAP_WIDTH];
    memset(colorMap, 0, sizeof(colorMap));

    int colorCount = traverseMap(mogicTower, colorMap) + 1;

    static Status stat;
    stat.nodeContainer = new GraphNode[colorCount];
    stat.nodeBackUp = new GraphNode[colorCount];

    stat.head = buildGraph(mogicTower, headpos, colorCount, colorMap, stat.nodeContainer);
    stat.player = mogicTower.initialPlayerInfo;

    /* ��ȡ������ڵ��������Ʒ�����Ϊ�� */
#ifdef DEBUG
    assert(stat.head->type == safeblock);
#endif

    stat.head->empty = true;
    stat.blockCount += stat.head->blockCount;
    stat.player.acquire(stat.head->obj);


    /* ���ݽڵ��ͼ�� */
    for (int i = 0; i < colorCount; ++i)
        stat.nodeBackUp[i] = stat.nodeContainer[i];

    return stat;
}
