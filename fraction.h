#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED
#include "integer.h"

//结构体分数
//notation 表示分数的正负号
//i 表示整数链表的头指针
//numerator 表示分子
//denominator 表示分母
//next 向后的指针
typedef struct Fraction
{
    char notation;
    integer *i;
    long long int numerator;
    long long int denominator;
    struct Fraction *next;
}fraction;

//函数原型:readFraction
//返回类型:fraction 类型的指针，参数:fraction的链表头指针
//读入用户的输入式子，只有输入正确时，式子才能被保存
fraction *readFraction(fraction *head);

//函数原型:sortFraction
//返回类型:fraction 类型的指针，参数:fraction的链表头指针
//整理分数链表，进行约分化简的操作
fraction *sortFraction(fraction *head);

//函数原型:destroyFraction
//返回类型:void ，参数:fraction的链表头指针
//摧毁fraction链表，清理内存
void destroyFraction(fraction *head);

//函数原型:displayFraction
//返回类型:void ，参数:fraction的链表头指针，fraction 结构体（计算结果）
//对齐打印fraction链表和最终答案
void displayFraction(fraction *head,fraction result);

//函数原型:compareFractions
//返回类型:int ，参数:两个fraction 结构体 x ，y
//比较 x ，y 的绝对值大小（x>=y返回1，反之返回0）
int compareFractions(fraction x,fraction y);

//函数原型:calculateFraction
//返回类型:fraction的结构体，参数:fraction的链表头指针
//计算fraction链表得到一个最终结果并以结构体的形式返回
fraction calculateFraction(fraction *head);

//函数原型:addf
//返回类型:fraction的结构体，参数:两个fraction的结构体
//计算两个分数并得到和，存入结构体并返回
fraction addf(fraction , fraction );

//函数原型:minusf
//返回类型:fraction的结构体，参数:两个fraction的结构体
//计算两个分数并得到差值，符号等，存入结构体返回
fraction minusf(fraction , fraction );

#endif // FRACTION_H_INCLUDED
