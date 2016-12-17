#ifndef __INIT_H
#define __INIT_H

#include "mogicTower.h"

const Tower& readTower();

//����cur����������ڷ������
void searchArea(const Tower& mogicTower, GraphNode* cur, int been[MAP_LENGTH][MAP_WIDTH]);

const Status& getInitialStatus(const Tower& mogicTower);

#endif