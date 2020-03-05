#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

//�ṹ������
//n��ÿһλ�����֣������α����棬������char�棨����ʵ�鱨�������ͣ�
//next����ָ�룬last��ǰ��ָ��
typedef struct Integer
{
    int n;
    struct Integer *next;
    struct Integer *last;
}integer;

//����ԭ��:sortInteger
//��������:integer���͵�ָ�룬����:���������ͷָ��
//�������������������λ����λ�����
integer *sortInteger(integer *ih);

//����ԭ��:displayInteger
//��������:void,����:���������ͷָ��
//���������ֵĴ�ӡ��һ��
void displayInteger(integer *ih);

//����ԭ��:addIntegers
//��������:integer���͵�ָ��,����:�������������ͷָ��
//����������������мӷ�����
integer *addIntegers(integer *ih1,integer *ih2);

//����ԭ��:minusIntegers
//��������:integer���͵�ָ��,����:�������������ͷָ��
//����������������м������㣬ih1�Ǳ�������ih2Ϊ��������Ҫ��ih1Ҫ����ih2�����������ֵ
integer *minusIntegers(integer *ih1,integer *ih2);

//����ԭ��:getLen
//��������:int,����:���������ͷָ��
//���ڵõ�һ�������ĳ���
int getLen(integer *ih);

//����ԭ��:destroyInteger
//��������:void,����:���������ͷָ��
//��������һ����������
void destroyInteger(integer *ih);

#endif // INTEGER_H_INCLUDED
