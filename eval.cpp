#include "eval.h"
#include "helpers.h"
#include "damage.h"
extern Tower globalMogicTower;
/*Ӧ��ûɶ�á�����Ϊ�Ǿ�̬�ģ�����Ҫ��̬��*/
/*struct door_key	
{
    int ykey, bkey, rkey;
    int ydoor, bdoor, rdoor;
    door_key()
    {
        ykey = bkey = rkey = 0;
        ydoor = bdoor = rdoor = 0;
        auto map = globalMogicTower.mapContent;
        for (int i = 0; i < MAP_LENGTH; i++)
            for (int j = 0; j < MAP_WIDTH; j++)
                switch (map[i][j])
                {
                    case yellowDoor:
                        ++ydoor; break;
                    case blueDoor:
                        ++bdoor; break;
                    case redDoor:
                        ++rdoor; break;
                    case yellowKey:
                        ++ykey; break;
                    case blueKey:
                        ++bkey; break;
                    case redKey:
                        ++rkey; break;
                    default:
                        break;
                }
    }
};*/

inline long long cmpMonster(const Status& stat) {	//��ǰ״̬��������й��ｻս���˺��ܺͣ�������������û�����
	auto map = globalMogicTower.mapContent;
	long long sumDamage = 0;
	for (int i = 0; i < MAP_LENGTH; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (isMonster(map[i][j])) {
				int temp = getDamage(stat.player, globalMogicTower.monsterInfo[map[i][j]]);
				if (temp == 999999999)
					temp = 1000;
				sumDamage += temp;
			}
		}
	}
	return sumDamage;
}

int eval(const Status& stat)
{
	int result = 0;
	/* ָ��˼�룺ħ��>���>�﹥>Կ��>HP */
	int blood = stat.player.getHP();
	int attack = stat.player.getATK();
	int defend = stat.player.getDEF();
	int defend_m = stat.player.getMDEF();
	int yellow_key = stat.player.getKeyCount(yellowKey);
	int blue_key = stat.player.getKeyCount(blueKey);
	int red_key = stat.player.getKeyCount(redKey);
	//int yellow_door =
	/*δ��ɵ��ⲿ����ʣ�µ���������Կ�׵Ĳ�ֵ����������ֵҲ�ǲ���*/
	/*������ܶ�̬ά����ʣ�����ŵ�����£�*/
	result -= cmpMonster(stat) * 100 / blood;	//û�в��ԣ����ڲ�֪��������ǲ����ȶ���һ�������ϣ��ٵ�
	result += defend_m * 500;
	result += defend * 300;
	result += attack * 250;
	/*��ʱд���⣬����������Ϊ����Կ����ʣ�µ���֮��ı��ʻ����Ȩ��*/
	return result;
}