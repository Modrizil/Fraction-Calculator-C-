/*
 * File name:  main.c
 * Author:     Chen Haoran , U201713511@hust.edu.cn
 * Purpose:    to realize all the functions
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "integer.h"
#include "fraction.h"
#include "file.h"
#include "tongfen.h"

//����ԭ��:display
//��������:void ������:fraction������ͷָ��
//�ļ�������ʽ����չʾ���ʽ�Ķ������
void display(fraction *head);

int main()
{
    int choice,i;
//�˵�Ŀ¼
    printf("**************************************\n");
    printf("             ����������               \n");
    printf("**************************************\n");
    printf("\n������:%9c˵��:\n",' ');
    printf("%6d%10c%s\n",1,' ',"��������");
    printf("%6d%10c%s\n",2,' ',"��ȡ�ļ�");
    printf("%6d%10c%s\n",3,' ',"ͨ�ֲ���");
    printf("%6d%10c%s\n",4,' ',"�˳�����");
    printf("\n\n\n��ѡ�������:");

    scanf("%d",&choice);//�û���ѡ�����
    for(i=0;i<3;i++){
        if(choice>0&&choice<5){
            break;
        }
        printf("��������(��%d��)\n",i+1);
        printf("����������:");
        scanf("%d",&choice);
    }
    if(i==3&&!(choice>0&&choice<5)){//���������������ѡ�ֱ���˳�
        printf("����ǿ���˳���\n\n");
        return 0;
    }

    while(choice!=4){
        if(choice==1){
            printf("\n�����밴 xxx+xxx/xxx �ĸ�ʽ����\n");
            printf("**�������ʱ�����ڷ������߼������ţ�Ӣ�����뷨����**\n");
            printf("��������ʽ�����롰=���󣬰��س����ɣ�:\n");
            fraction *head,result;//result ���ڴ�Ž����head ���ڴ������ı��ʽ
            head=readFraction(head);//����
            head=sortFraction(head);//Լ�ֻ���
            if(head==NULL){
                printf("�������!�޷�����!\n");
            }
            else{
                result=calculateFraction(head);//������ʽ
                printf("\n------after sorting:------\n\n");
                displayFraction(head,result);//��ӡ���

                char option[5];
                printf("\n\n����Ҫ����������(yes/no)\n");
                scanf("%s",option);
                if(strcmp(option,"yes")==0){
                    writeIntoFile(head);//д���ļ�
                }
                else{
                    destroyFraction(head);//���������ͷ��ڴ�
                    printf("\n�����Ѷ�ʧ��\n");
                }
            }
        }

        if(choice==2){
            printf("�ļ��еı��ʽ������Ҫ���� xxx+xxx/xxx ��\n����︺����ʱ��Ҫ�ڷ������߼������ţ�Ӣ�����뷨��\n");
            printf("ֻ�ܶ����ļ��е�һ��ʽ�ӡ������ʽ����ʱ�����б�����Ϣ\n");
            printf("\n��������Ҫ��ȡ���ļ�����\n");
            char filename[50];
            int judge;//�����ж��ļ������Ƿ�ɹ�
            scanf("%s",filename);
            fraction *head,result;
            head=readFile(filename,&judge);//�����ļ�
            if(judge==-1){
                printf("���ʽ�����⣡\n\n");
                display(head);//չʾ�ļ�������һ��
                destroyFraction(head);//�����ڴ�
            }
            else{
                head=sortFraction(head);//����
                result=calculateFraction(head);//����
                printf("\n------after sorting:------\n\n");
                displayFraction(head,result);//չʾ
                destroyFraction(head);//�����ڴ�
            }
        }

        if(choice==3){
            printf("\n�����밴 xxx+xxx/xxx �ĸ�ʽ����\n");
            printf("**�������ʱ�����ڷ������߼������ţ�Ӣ�����뷨����\n");
            printf("������  ����  ���������롰=���󣬰��س����ɣ�:\n");
            fraction *head,*cur,result;
            int n=0;//��ʾ�ж��ٸ���������
            result.i=NULL;
            result.next=NULL;
            result.numerator=-2;//��ǣ��ں���displayFraction������������
            head=readFraction(head);
            for(cur=head;cur!=NULL;cur=cur->next)n++;
            if(n!=2){
                printf("\nPresentation error!\n");
                destroyFraction(head);//�����ڴ�
            }
            else{
                displayFraction(head,result);//չʾԭʼ�û�����
                head=sortFraction(head);
                displayFraction(head,result);//��һ�����������
                displayTongfen(head);//ͨ�ֹ���
                char option[5];
                printf("\n\n����Ҫ����������(yes/no)\n");
                scanf("%s",option);
                if(strcmp(option,"yes")==0){
                    writeIntoFile(head);//�����ļ�
                }
                else{
                    destroyFraction(head);//�����ڴ�
                    printf("\n�����Ѷ�ʧ��\n");
                }
            }
        }

        getchar();
        printf("\n��enter������...\n");
        getchar();
        system("cls");//����

        printf("**************************************\n");
        printf("             ����������               \n");
        printf("**************************************\n");
        printf("\n������:%9c˵��:\n",' ');
        printf("%6d%10c%s\n",1,' ',"��������");
        printf("%6d%10c%s\n",2,' ',"��ȡ�ļ�");
        printf("%6d%10c%s\n",3,' ',"ͨ�ֲ���");
        printf("%6d%10c%s\n",4,' ',"�˳�����");
        printf("\n\n\n��ѡ�������:");

        scanf("%d",&choice);
        for(i=0;i<3;i++){
            if(choice>0&&choice<5){
                break;
            }
            printf("��������(��%d��)\n",i+1);
            printf("����������:");
            scanf("%d",&choice);
        }
        if(i==3&&!(choice>0&&choice<5)){
            printf("����ǿ���˳���\n\n");
            return 0;
        }
    }
    getchar();
    printf("��л���Դ˳����ʹ�ã�\n");
    getchar();
    return 0;
}

//����ԭ��:display
//��������:void ������:fraction������ͷָ��
//�ļ�������ʽ����չʾ���ʽ�Ķ������
void display(fraction *head)
{
    if(head==NULL){
        printf("\nû�ж����ļ���\n");
        return;
    }

    printf("\n�ļ��Ķ������:\n");
    fraction *right;//right ���ڱ���
    int i,n;
    n=getLen(head->i);

    for(right=head->next;right!=NULL;right=right->next){
        if(n<getLen(right->i)){
            n=getLen(right->i);
        }
    }//�õ������������

    //�ж�ͷָ���Ƿ����
    printf("   %c %c",head->notation=='-'?'-':' ',head->notation=='-'?'(':' ');
    for(i=0;i<n-getLen(head->i);i++){
        printf(" ");
    }
    if(head->i==NULL){
        printf("�Ӵ˴���ʼ����\n");
        return;
    }
    displayInteger(head->i);

    if(head->numerator<0){
        printf("�Ӵ˴���ʼ����\n");
        return;
    }
    else if(head->numerator==0){
        printf("%c\n",head->notation=='-'?')':' ');
    }
    else{
        printf(" + ");
        printf("%20lld",head->numerator);
    }

    if(head->denominator==-1){
        printf("�Ӵ˴���ʼ����\n");
        return;
    }
    printf(" / ");
    if(head->denominator<=0){
        printf("�Ӵ˴���ʼ����\n");
        return;
    }
    printf("%20lld%c\n",head->denominator,head->notation=='-'?')':' ');

    for(right=head->next;right!=NULL;right=right->next){//ѭ����������Ĵ�����Ϣ
        printf("   %c %c",right->notation,right->notation=='-'?'-':' ');
        for(i=0;i<n-getLen(right->i);i++){
            printf(" ");
        }
        if(right->i==NULL){
            printf("�Ӵ˴���ʼ����\n");
            return;
        }
        displayInteger(right->i);
        if(right->numerator<0){
            printf("�Ӵ˴���ʼ����\n");
            return;
        }
        else if(head->numerator==0){
            printf("%c\n",right->notation=='-'?')':' ');
        }
        else{
            printf(" + ");
            printf("%20lld",right->numerator);
        }

        if(right->denominator==-1){
            printf("�Ӵ˴���ʼ����\n");
            return;
        }
        printf(" / ");
        if(right->denominator<0){
            printf("�Ӵ˴���ʼ����\n");
            return;
        }
        printf("%20lld%c\n",right->denominator,right->notation=='-'?')':' ');
    }
    if(right==NULL){
        printf("�Ӵ˴���ʼ����\n");
        return;
    }
}
