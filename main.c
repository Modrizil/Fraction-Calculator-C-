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

//函数原型:display
//返回类型:void ，参数:fraction的链表头指针
//文件输入表达式错误，展示表达式的读入情况
void display(fraction *head);

int main()
{
    int choice,i;
//菜单目录
    printf("**************************************\n");
    printf("             分数计算器               \n");
    printf("**************************************\n");
    printf("\n操作数:%9c说明:\n",' ');
    printf("%6d%10c%s\n",1,' ',"键盘输入");
    printf("%6d%10c%s\n",2,' ',"读取文件");
    printf("%6d%10c%s\n",3,' ',"通分操作");
    printf("%6d%10c%s\n",4,' ',"退出程序");
    printf("\n\n\n请选择操作数:");

    scanf("%d",&choice);//用户的选项操作
    for(i=0;i<3;i++){
        if(choice>0&&choice<5){
            break;
        }
        printf("操作错误(第%d次)\n",i+1);
        printf("请重新输入:");
        scanf("%d",&choice);
    }
    if(i==3&&!(choice>0&&choice<5)){//避免无限输入错误选项，直接退出
        printf("程序强制退出！\n\n");
        return 0;
    }

    while(choice!=4){
        if(choice==1){
            printf("\n分数请按 xxx+xxx/xxx 的格式输入\n");
            printf("**输入减号时，请在分数两边加上括号（英文输入法）！**\n");
            printf("请输入表达式（输入“=”后，按回车即可）:\n");
            fraction *head,result;//result 用于存放结果，head 用于存放输入的表达式
            head=readFraction(head);//读入
            head=sortFraction(head);//约分化简
            if(head==NULL){
                printf("输入错误!无法保存!\n");
            }
            else{
                result=calculateFraction(head);//计算表达式
                printf("\n------after sorting:------\n\n");
                displayFraction(head,result);//打印结果

                char option[5];
                printf("\n\n你需要保存数据吗？(yes/no)\n");
                scanf("%s",option);
                if(strcmp(option,"yes")==0){
                    writeIntoFile(head);//写入文件
                }
                else{
                    destroyFraction(head);//清理链表释放内存
                    printf("\n数据已丢失！\n");
                }
            }
        }

        if(choice==2){
            printf("文件中的表达式，分数要形如 xxx+xxx/xxx ，\n当表达负分数时，要在分数两边加上括号（英文输入法）\n");
            printf("只能读入文件中的一个式子。当表达式出错时，会有报错信息\n");
            printf("\n请输入你要读取的文件名：\n");
            char filename[50];
            int judge;//用于判断文件读入是否成功
            scanf("%s",filename);
            fraction *head,result;
            head=readFile(filename,&judge);//读入文件
            if(judge==-1){
                printf("表达式有问题！\n\n");
                display(head);//展示文件读到哪一步
                destroyFraction(head);//清理内存
            }
            else{
                head=sortFraction(head);//整理
                result=calculateFraction(head);//计算
                printf("\n------after sorting:------\n\n");
                displayFraction(head,result);//展示
                destroyFraction(head);//清理内存
            }
        }

        if(choice==3){
            printf("\n分数请按 xxx+xxx/xxx 的格式输入\n");
            printf("**输入减号时，请在分数两边加上括号（英文输入法）！\n");
            printf("请输入  两个  分数（输入“=”后，按回车即可）:\n");
            fraction *head,*cur,result;
            int n=0;//表示有多少个分数输入
            result.i=NULL;
            result.next=NULL;
            result.numerator=-2;//标记，在函数displayFraction跳过结果的输出
            head=readFraction(head);
            for(cur=head;cur!=NULL;cur=cur->next)n++;
            if(n!=2){
                printf("\nPresentation error!\n");
                destroyFraction(head);//清理内存
            }
            else{
                displayFraction(head,result);//展示原始用户输入
                head=sortFraction(head);
                displayFraction(head,result);//第一步整理后的输出
                displayTongfen(head);//通分过程
                char option[5];
                printf("\n\n你需要保存数据吗？(yes/no)\n");
                scanf("%s",option);
                if(strcmp(option,"yes")==0){
                    writeIntoFile(head);//存入文件
                }
                else{
                    destroyFraction(head);//清理内存
                    printf("\n数据已丢失！\n");
                }
            }
        }

        getchar();
        printf("\n按enter键继续...\n");
        getchar();
        system("cls");//清屏

        printf("**************************************\n");
        printf("             分数计算器               \n");
        printf("**************************************\n");
        printf("\n操作数:%9c说明:\n",' ');
        printf("%6d%10c%s\n",1,' ',"键盘输入");
        printf("%6d%10c%s\n",2,' ',"读取文件");
        printf("%6d%10c%s\n",3,' ',"通分操作");
        printf("%6d%10c%s\n",4,' ',"退出程序");
        printf("\n\n\n请选择操作数:");

        scanf("%d",&choice);
        for(i=0;i<3;i++){
            if(choice>0&&choice<5){
                break;
            }
            printf("操作错误(第%d次)\n",i+1);
            printf("请重新输入:");
            scanf("%d",&choice);
        }
        if(i==3&&!(choice>0&&choice<5)){
            printf("程序强制退出！\n\n");
            return 0;
        }
    }
    getchar();
    printf("感谢您对此程序的使用！\n");
    getchar();
    return 0;
}

//函数原型:display
//返回类型:void ，参数:fraction的链表头指针
//文件输入表达式错误，展示表达式的读入情况
void display(fraction *head)
{
    if(head==NULL){
        printf("\n没有读入文件！\n");
        return;
    }

    printf("\n文件的读入情况:\n");
    fraction *right;//right 用于遍历
    int i,n;
    n=getLen(head->i);

    for(right=head->next;right!=NULL;right=right->next){
        if(n<getLen(right->i)){
            n=getLen(right->i);
        }
    }//得到最长的整数部分

    //判断头指针是否错误
    printf("   %c %c",head->notation=='-'?'-':' ',head->notation=='-'?'(':' ');
    for(i=0;i<n-getLen(head->i);i++){
        printf(" ");
    }
    if(head->i==NULL){
        printf("从此处开始错误！\n");
        return;
    }
    displayInteger(head->i);

    if(head->numerator<0){
        printf("从此处开始错误！\n");
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
        printf("从此处开始错误！\n");
        return;
    }
    printf(" / ");
    if(head->denominator<=0){
        printf("从此处开始错误！\n");
        return;
    }
    printf("%20lld%c\n",head->denominator,head->notation=='-'?')':' ');

    for(right=head->next;right!=NULL;right=right->next){//循环遍历后面的错误信息
        printf("   %c %c",right->notation,right->notation=='-'?'-':' ');
        for(i=0;i<n-getLen(right->i);i++){
            printf(" ");
        }
        if(right->i==NULL){
            printf("从此处开始错误！\n");
            return;
        }
        displayInteger(right->i);
        if(right->numerator<0){
            printf("从此处开始错误！\n");
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
            printf("从此处开始错误！\n");
            return;
        }
        printf(" / ");
        if(right->denominator<0){
            printf("从此处开始错误！\n");
            return;
        }
        printf("%20lld%c\n",right->denominator,right->notation=='-'?')':' ');
    }
    if(right==NULL){
        printf("从此处开始错误！\n");
        return;
    }
}
