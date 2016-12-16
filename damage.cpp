#include "mogic.h"

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
int getDamage(int h_atk, int h_def, int h_mdef, int m_hp, int m_atk, int m_def, int m_spe)
{
    if (m_spe == 1) // ħ��
        h_def = 0;
    if (m_spe == 2) // ���
        m_def = h_atk - 1;

    if (h_atk <= m_def) // �޷�ս��
        return 999999999;
    if (h_def >= m_atk) // �޷�����˺�
        return 0;

    int damage = 0;
    if (m_spe == 3) // �ȹ�
        damage += m_atk - h_def;

    int m_times = 1;
    if (m_spe == 4) // 2����
        m_times = 2;

    damage += (m_hp - 1) / (h_atk - m_def)*(m_atk - h_def)*m_times; // �����˺����㹫ʽ
    damage -= h_mdef;

    return damage <= 0 ? 0 : damage;
}

int getDamage(const PlayerInfo& p, const Monster& m)
{
    return getDamage(p.getATK(), p.getDEF(), p.getMDEF(), m.getHP(), m.getATK(), m.getDEF(), m.getSPE());
}