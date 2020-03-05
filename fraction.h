#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED
#include "integer.h"

//�ṹ�����
//notation ��ʾ������������
//i ��ʾ���������ͷָ��
//numerator ��ʾ����
//denominator ��ʾ��ĸ
//next ����ָ��
typedef struct Fraction
{
    char notation;
    integer *i;
    long long int numerator;
    long long int denominator;
    struct Fraction *next;
}fraction;

//����ԭ��:readFraction
//��������:fraction ���͵�ָ�룬����:fraction������ͷָ��
//�����û�������ʽ�ӣ�ֻ��������ȷʱ��ʽ�Ӳ��ܱ�����
fraction *readFraction(fraction *head);

//����ԭ��:sortFraction
//��������:fraction ���͵�ָ�룬����:fraction������ͷָ��
//���������������Լ�ֻ���Ĳ���
fraction *sortFraction(fraction *head);

//����ԭ��:destroyFraction
//��������:void ������:fraction������ͷָ��
//�ݻ�fraction���������ڴ�
void destroyFraction(fraction *head);

//����ԭ��:displayFraction
//��������:void ������:fraction������ͷָ�룬fraction �ṹ�壨��������
//�����ӡfraction��������մ�
void displayFraction(fraction *head,fraction result);

//����ԭ��:compareFractions
//��������:int ������:����fraction �ṹ�� x ��y
//�Ƚ� x ��y �ľ���ֵ��С��x>=y����1����֮����0��
int compareFractions(fraction x,fraction y);

//����ԭ��:calculateFraction
//��������:fraction�Ľṹ�壬����:fraction������ͷָ��
//����fraction����õ�һ�����ս�����Խṹ�����ʽ����
fraction calculateFraction(fraction *head);

//����ԭ��:addf
//��������:fraction�Ľṹ�壬����:����fraction�Ľṹ��
//���������������õ��ͣ�����ṹ�岢����
fraction addf(fraction , fraction );

//����ԭ��:minusf
//��������:fraction�Ľṹ�壬����:����fraction�Ľṹ��
//���������������õ���ֵ�����ŵȣ�����ṹ�巵��
fraction minusf(fraction , fraction );

#endif // FRACTION_H_INCLUDED
