#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

//结构体整数
//n是每一位的数字，用整形变量存，不能用char存（理由实验报告具体阐释）
//next向后的指针，last向前的指针
typedef struct Integer
{
    int n;
    struct Integer *next;
    struct Integer *last;
}integer;

//函数原型:sortInteger
//返回类型:integer类型的指针，参数:整数链表的头指针
//用于整理整数，处理进位及退位的情况
integer *sortInteger(integer *ih);

//函数原型:displayInteger
//返回类型:void,参数:整数链表的头指针
//将整数部分的打印在一行
void displayInteger(integer *ih);

//函数原型:addIntegers
//返回类型:integer类型的指针,参数:两个整数链表的头指针
//将两个整数链表进行加法运算
integer *addIntegers(integer *ih1,integer *ih2);

//函数原型:minusIntegers
//返回类型:integer类型的指针,参数:两个整数链表的头指针
//将两个整数链表进行减法运算，ih1是被减数，ih2为减数，且要求ih1要大于ih2所代表的整数值
integer *minusIntegers(integer *ih1,integer *ih2);

//函数原型:getLen
//返回类型:int,参数:整数链表的头指针
//用于得到一个整数的长度
int getLen(integer *ih);

//函数原型:destroyInteger
//返回类型:void,参数:整数链表的头指针
//用于销毁一个整数链表
void destroyInteger(integer *ih);

#endif // INTEGER_H_INCLUDED
