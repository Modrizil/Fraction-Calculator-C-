#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include "fraction.h"

//函数原型:readFile
//返回类型:fraction类型的指针，参数:字符指针（字符串）、判断因子
//读入参数中的文件名，判断是否读入成功，并输出头指针
fraction *readFile(const char *filename,int *judge);

//函数原型:writeIntoFile
//返回类型:void ，参数:fraction的链表头指针
//将链表中的信息写入文件中
void writeIntoFile(fraction *head);

#endif // FILE_H_INCLUDED
