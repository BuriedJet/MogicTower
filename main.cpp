#define DEBUG

#include <iostream>
#include <fstream>
#include "mogic.h"
#include "damage.h"

using namespace std;

/*ȫ�ּ�¼����Ϣ�����ݽṹ*/
struct
{
    /*¥���ͼ��С��¥��������ǰ�̶�Ϊ1 * 13 * 13 */
    //int height;
    //int len, wid;
    MapObj floorMap[MAP_LENGTH][MAP_WIDTH];

}mogicTower;


int main()
{
    

    PAUSE;
}

void readTower()
{
    ifstream fin("input.txt");
    if (!fin)
    {
        

    }
}
