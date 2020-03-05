#ifndef TONGFEN_H_INCLUDED
#define TONGFEN_H_INCLUDED
#include "integer.h"
#include "fraction.h"

//函数原型:CommonDivisor
//返回类型:long long int ，参数:两个long long int 类型的整数
//得到a ，b的最大公约数
long long int CommonDivisor(long long int a,long long int b);

//函数原型:displayTongfen
//返回类型:void ，参数:fraction的链表头指针
//打印分数的通分结果
void displayTongfen(fraction *head);

#endif // TONGFEN_H_INCLUDED
