#include <stdio.h>
#include <stdlib.h>
#include "integer.h"

//函数原型:displayInteger
//返回类型:void,参数:整数链表的头指针
//将整数部分的打印在一行
void displayInteger(integer *ih)
{
    if(ih==NULL){
        printf("\b0");//整数部分若为空，则打印零
        return;
    }
    integer *cur;

    for(cur=ih;cur!=NULL;cur=cur->next){
        printf("%1d",cur->n);
    }//循环打印

    return;
}

//函数原型:sortInteger
//返回类型:integer类型的指针，参数:整数链表的头指针
//用于整理整数，处理进位及退位的情况
integer *sortInteger(integer *ih)
{
    if(ih==NULL){
        return NULL;
    }

    integer *it,*cur;//it代表IntegerTail，为整数链表的尾端
    for(it=ih;it->next!=NULL;it=it->next);

    for(cur=it;cur->last!=NULL;cur=cur->last){
        if(cur->n>=10){//进位
            cur->last->n+=cur->n/10;
            cur->n%=10;
        }
        if(cur->n<0){//退位
            cur->last->n--;
            cur->n+=10;
        }
    }

    integer *temp;
    while(ih->n>=10){//整理整形链表的头部数字
        temp=malloc(sizeof(integer));
        temp->last=NULL;
        temp->n=ih->n/10;
        ih->n%=10;
        temp->next=ih;
        ih->last=temp;
        ih=temp;
    }

    while(ih!=NULL&&ih->n==0){//当头部是零的话，进行删除
        temp=ih;
        ih=ih->next;
        free(temp);
    }

    return ih;
}

//函数原型:addIntegers
//返回类型:integer类型的指针,参数:两个整数链表的头指针，和结果的头指针
//将两个整数链表进行加法运算
integer *addIntegers(integer *ih1,integer *ih2)
{
    integer *tail,*cur,*pre,*i1,*i2;
    cur=NULL;

    for(i1=ih1;i1->next!=NULL;i1=i1->next);//i1循环至ih1的尾部
    for(i2=ih2;i2->next!=NULL;i2=i2->next);//i2循环至ih2的尾部

    tail=malloc(sizeof(integer));//从尾部开始计算，创立新的整数链表
    tail->n=i1->n+i2->n;
    tail->next=NULL;
    tail->last=NULL;
    pre=tail;
    i1=i1->last;
    i2=i2->last;

    while(!(i1==NULL&&i2==NULL)){//循环运算直到把两链表加完
        if(i1==NULL&&i2!=NULL){
            cur=malloc(sizeof(integer));
            cur->n=i2->n;
            cur->last=NULL;
            cur->next=pre;
            pre->last=cur;
            pre=cur;
            i2=i2->last;
        }
        if(i2==NULL&&i1!=NULL){
            cur=malloc(sizeof(integer));
            cur->n=i1->n;
            cur->last=NULL;
            cur->next=pre;
            pre->last=cur;
            pre=cur;
            i1=i1->last;
        }
        if(i1!=NULL&&i2!=NULL){
            cur=malloc(sizeof(integer));
            cur->n=i1->n+i2->n;
            cur->last=NULL;
            cur->next=pre;
            pre->last=cur;
            pre=cur;
            i1=i1->last;
            i2=i2->last;
        }
    }

    integer *head;
    for(head=tail;head->last!=NULL;head=head->last);//得到头指针

    return head;
}

//函数原型:minusIntegers
//返回类型:integer类型的指针,参数:两个整数链表的头指针
//将两个整数链表进行减法运算，ih1是被减数，ih2为减数，且要求ih1要大于ih2所代表的整数值
integer *minusIntegers(integer *ih1,integer *ih2)
{
    integer *tail,*cur,*pre,*i1,*i2;
    cur=NULL;

    for(i1=ih1;i1->next!=NULL;i1=i1->next);//i1循环至ih1的尾部
    for(i2=ih2;i2->next!=NULL;i2=i2->next);//i2循环至ih2的尾部

    tail=malloc(sizeof(integer));//从尾部开始计算，创立新的整数链表
    tail->last=NULL;
    tail->next=NULL;
    tail->n=i1->n-i2->n;
    pre=tail;
    i1=i1->last;
    i2=i2->last;

    while(!(i1==NULL&&i2==NULL)){//循环减，直到两链表都遍历完
        if(i2==NULL&&i1!=NULL){
            cur=malloc(sizeof(integer));
            cur->n=i1->n;
            cur->last=NULL;
            cur->next=pre;
            pre->last=cur;
            pre=cur;
            i1=i1->last;
        }
        if(i1!=NULL&&i2!=NULL){
            cur=malloc(sizeof(integer));
            cur->n=i1->n-i2->n;
            cur->last=NULL;
            cur->next=pre;
            pre->last=cur;
            pre=cur;
            i1=i1->last;
            i2=i2->last;
        }
    }

    integer *head;
    for(head=tail;head->last!=NULL;head=head->last);//得到头指针

    return head;
}

//函数原型:getLen
//返回类型:int,参数:整数链表的头指针
//用于得到一个整数的长度
int getLen(integer *ih)
{
    integer *cur;
    int n=0;
    for(cur=ih;cur!=NULL;cur=cur->next){
        n++;
    }

    return n;
}

//函数原型:destroyInteger
//返回类型:void,参数:整数链表的头指针
//用于销毁一个整数链表
void destroyInteger(integer *ih)
{
    if(ih==NULL){
        return;
    }

    integer *temp;

    while(ih!=NULL){
        temp=ih;
        ih=ih->next;
        free(temp);
    }

    return;
}
