#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include "fraction.h"

//����ԭ��:readFile
//��������:fraction���͵�ָ�룬����:�ַ�ָ�루�ַ��������ж�����
//��������е��ļ������ж��Ƿ����ɹ��������ͷָ��
fraction *readFile(const char *filename,int *judge);

//����ԭ��:writeIntoFile
//��������:void ������:fraction������ͷָ��
//�������е���Ϣд���ļ���
void writeIntoFile(fraction *head);

#endif // FILE_H_INCLUDED
