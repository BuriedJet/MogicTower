#ifndef __GRAPH_H
#define __GRAPH_H

#include "mogicTower.h"

//����ͼ��Ⱦɫ
int traverseMap(Tower& mogicTower);

//����ͼת����ͼ����ӽڵ�ı�Ҫ��Ϣ
int buildGraph(const Tower& mogicTower, const Position& curPos, int colorCount,
                      Status* statp);


#endif

