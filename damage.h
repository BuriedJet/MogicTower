#ifndef __DAMAGE_H
#define __DAMAGE_H

/*
�˺�������һ���������ʿ��ɵ��˺�
����˵����
h_atk: ��ʿ����
h_def: ��ʿ����
h_mdef: ��ʿħ��
m_hp: ��������ֵ
m_atk: ���﹥��
m_def: �������
m_spe: ������Ч
����ֵ��
һ�������������˺�ֵ��
�����ʿ�޷��Թ�������˺�������999999999

������Ч˵����
0: ����Ч
1: ħ��������������ʿ�ķ�����
2: ��̣��������=��ʿ����-1��
3: �ȹ���ս��ǰ�������ȹ�����ʿһ�Σ�
4: 2������ÿ�غϹ������ʿ���Σ�
*/
int getDamage(int h_atk, int h_def, int h_mdef, int m_hp, int m_atk, int m_def, int m_spe);

int getDamage(const PlayerInfo& p, const Monster& m);

#endif

