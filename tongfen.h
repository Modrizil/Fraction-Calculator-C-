#ifndef TONGFEN_H_INCLUDED
#define TONGFEN_H_INCLUDED
#include "integer.h"
#include "fraction.h"

//����ԭ��:CommonDivisor
//��������:long long int ������:����long long int ���͵�����
//�õ�a ��b�����Լ��
long long int CommonDivisor(long long int a,long long int b);

//����ԭ��:displayTongfen
//��������:void ������:fraction������ͷָ��
//��ӡ������ͨ�ֽ��
void displayTongfen(fraction *head);

#endif // TONGFEN_H_INCLUDED
