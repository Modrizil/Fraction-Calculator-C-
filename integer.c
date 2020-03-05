#include <stdio.h>
#include <stdlib.h>
#include "integer.h"

//����ԭ��:displayInteger
//��������:void,����:���������ͷָ��
//���������ֵĴ�ӡ��һ��
void displayInteger(integer *ih)
{
    if(ih==NULL){
        printf("\b0");//����������Ϊ�գ����ӡ��
        return;
    }
    integer *cur;

    for(cur=ih;cur!=NULL;cur=cur->next){
        printf("%1d",cur->n);
    }//ѭ����ӡ

    return;
}

//����ԭ��:sortInteger
//��������:integer���͵�ָ�룬����:���������ͷָ��
//�������������������λ����λ�����
integer *sortInteger(integer *ih)
{
    if(ih==NULL){
        return NULL;
    }

    integer *it,*cur;//it����IntegerTail��Ϊ���������β��
    for(it=ih;it->next!=NULL;it=it->next);

    for(cur=it;cur->last!=NULL;cur=cur->last){
        if(cur->n>=10){//��λ
            cur->last->n+=cur->n/10;
            cur->n%=10;
        }
        if(cur->n<0){//��λ
            cur->last->n--;
            cur->n+=10;
        }
    }

    integer *temp;
    while(ih->n>=10){//�������������ͷ������
        temp=malloc(sizeof(integer));
        temp->last=NULL;
        temp->n=ih->n/10;
        ih->n%=10;
        temp->next=ih;
        ih->last=temp;
        ih=temp;
    }

    while(ih!=NULL&&ih->n==0){//��ͷ������Ļ�������ɾ��
        temp=ih;
        ih=ih->next;
        free(temp);
    }

    return ih;
}

//����ԭ��:addIntegers
//��������:integer���͵�ָ��,����:�������������ͷָ�룬�ͽ����ͷָ��
//����������������мӷ�����
integer *addIntegers(integer *ih1,integer *ih2)
{
    integer *tail,*cur,*pre,*i1,*i2;
    cur=NULL;

    for(i1=ih1;i1->next!=NULL;i1=i1->next);//i1ѭ����ih1��β��
    for(i2=ih2;i2->next!=NULL;i2=i2->next);//i2ѭ����ih2��β��

    tail=malloc(sizeof(integer));//��β����ʼ���㣬�����µ���������
    tail->n=i1->n+i2->n;
    tail->next=NULL;
    tail->last=NULL;
    pre=tail;
    i1=i1->last;
    i2=i2->last;

    while(!(i1==NULL&&i2==NULL)){//ѭ������ֱ�������������
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
    for(head=tail;head->last!=NULL;head=head->last);//�õ�ͷָ��

    return head;
}

//����ԭ��:minusIntegers
//��������:integer���͵�ָ��,����:�������������ͷָ��
//����������������м������㣬ih1�Ǳ�������ih2Ϊ��������Ҫ��ih1Ҫ����ih2�����������ֵ
integer *minusIntegers(integer *ih1,integer *ih2)
{
    integer *tail,*cur,*pre,*i1,*i2;
    cur=NULL;

    for(i1=ih1;i1->next!=NULL;i1=i1->next);//i1ѭ����ih1��β��
    for(i2=ih2;i2->next!=NULL;i2=i2->next);//i2ѭ����ih2��β��

    tail=malloc(sizeof(integer));//��β����ʼ���㣬�����µ���������
    tail->last=NULL;
    tail->next=NULL;
    tail->n=i1->n-i2->n;
    pre=tail;
    i1=i1->last;
    i2=i2->last;

    while(!(i1==NULL&&i2==NULL)){//ѭ������ֱ��������������
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
    for(head=tail;head->last!=NULL;head=head->last);//�õ�ͷָ��

    return head;
}

//����ԭ��:getLen
//��������:int,����:���������ͷָ��
//���ڵõ�һ�������ĳ���
int getLen(integer *ih)
{
    integer *cur;
    int n=0;
    for(cur=ih;cur!=NULL;cur=cur->next){
        n++;
    }

    return n;
}

//����ԭ��:destroyInteger
//��������:void,����:���������ͷָ��
//��������һ����������
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
