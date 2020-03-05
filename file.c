#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "fraction.h"

//函数原型:readFile
//返回类型:fraction类型的指针，参数:字符指针（字符串）、判断因子（*judge==-1时表示读入失败，*judge==1时表示读入成功）
//读入参数中的文件名，判断是否读入成功，并输出头指针
fraction *readFile(const char *filename,int *judge)
{
    FILE *fp;
    *judge=0;
    if((fp=fopen(filename,"r"))==NULL){//打开文件
        printf("\n\nFile can not be opened.\n");
        *judge=-1;
        return NULL;
    }

    fraction *head;//创立头指针
    head=NULL;
    char read;

    read=fgetc(fp);//一个一个字符读入
    while(read==' '||read=='\t'||read=='\n'){//跳过空格回车
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(!((read>='0'&&read<='9')||read=='+'||read=='-')){//有效输入
        *judge=-1;
        fclose(fp);
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        return head;
    }

    switch (read){
case '+'://第一个有效字符是加号的情况
    head=malloc(sizeof(fraction));
    head->next=NULL;
    head->i=NULL;
    head->notation='+';
    head->denominator=-1;
    head->numerator=-1;
    read=fgetc(fp);
    while(read==' '||read=='\t'||read=='\n'){
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(!(read>='0'&&read<='9')){
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }
    head->i=malloc(sizeof(integer));
    head->i->n=read-'0';
    head->i->last=NULL;
    head->i->next=NULL;
    break;
case '-'://第一个有效字符是减号的情况
    head=malloc(sizeof(fraction));
    head->next=NULL;
    head->i=NULL;
    head->notation='-';
    head->denominator=-1;
    head->numerator=-1;
    read=fgetc(fp);
    while(read==' '||read=='\t'||read=='\n'){
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(read!='('){
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }
    read=fgetc(fp);
    while(read==' '||read=='\t'||read=='\n'){
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(!(read>='0'&&read<='9')){
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }
    head->i=malloc(sizeof(integer));
    head->i->n=read-'0';
    head->i->last=NULL;
    head->i->next=NULL;
    break;
default://第一个有效字符是数字的情况
    head=malloc(sizeof(fraction));
    head->next=NULL;
    head->notation='+';
    head->denominator=-1;
    head->numerator=-1;
    head->i=malloc(sizeof(integer));
    head->i->n=read-'0';
    head->i->last=NULL;
    head->i->next=NULL;
    break;
    }//switch 结束

    integer *pre,*cur;
    pre=head->i;
    cur=NULL;

    read=fgetc(fp);
    while(read>='0'&&read<='9'){//读完剩下的整数部分
        cur=malloc(sizeof(integer));
        cur->n=read-'0';
        cur->next=NULL;
        cur->last=pre;
        pre->next=cur;
        pre=cur;
        read=fgetc(fp);
    }
    while(read==' '||read=='\t'||read=='\n'){
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(read!='+'){//整数与分数之间的加号运算符
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }

    fscanf(fp,"%lld",&head->numerator);//读入分子
    if(head->numerator<0){
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }
    read=fgetc(fp);
    while(read==' '||read=='\t'||read=='\n'){
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(read!='/'){//读入分子与分母之间的除法运算符
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }

    fscanf(fp,"%lld",&head->denominator);//读入分母
    if(head->denominator<=0){
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }
    read=fgetc(fp);
    while(read==' '||read=='\t'||read=='\n'){
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(head->notation=='-'){//若是负分数，则要加上反括号
        if(read!=')'){
            printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
            *judge=-1;
            fclose(fp);
            return head;
        }
        read=fgetc(fp);
        while(read==' '||read=='\t'||read=='\n'){
            read=fgetc(fp);
        }
        if(read==EOF){
            *judge=-1;
            fclose(fp);
            return head;
        }
    }

    if(read=='='){//如果是等号则结束输入
        *judge=1;
        fclose(fp);
        return head;
    }
    if(read!='+'&&read!='-'){
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }

    fraction *left,*right;//left 表示上一个，right 表示下一个
    left = head;
    right=NULL;
    while(1){//开始循环读入
        right=malloc(sizeof(fraction));
        right->next=NULL;
        right->i=NULL;
        right->notation=read;
        right->numerator=-1;
        right->denominator=-1;
        left->next=right;//将链表链接起来

        read=fgetc(fp);
        while(read==' '||read=='\t'||read=='\n'){
            read=fgetc(fp);
        }
        if(read==EOF){
            *judge=-1;
            fclose(fp);
            return head;
        }

        if(right->notation=='-'){
            if(read!='('){
                printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
                *judge=-1;
                fclose(fp);
                return head;
            }
            read=fgetc(fp);
            while(read==' '||read=='\t'||read=='\n'){
                read=fgetc(fp);
            }
            if(read==EOF){
                *judge=-1;
                fclose(fp);
                return head;
            }
        }

        if(!(read>='0'&&read<='9')){
            printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
            *judge=-1;
            fclose(fp);
            return head;
        }
        right->i=malloc(sizeof(integer));
        right->i->n=read-'0';
        right->i->last=NULL;
        right->i->next=NULL;
        pre=right->i;
        cur=NULL;

        read=fgetc(fp);
        while(read>='0'&&read<='9'){
            cur=malloc(sizeof(integer));
            cur->n=read-'0';
            cur->next=NULL;
            cur->last=pre;
            pre->next=cur;
            pre=cur;
            read=fgetc(fp);
        }
        while(read==' '||read=='\t'||read=='\n'){
            read=fgetc(fp);
        }
        if(read==EOF){
            *judge=-1;
            fclose(fp);
            return head;
        }

        if(read!='+'){
            printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
            *judge=-1;
            fclose(fp);
            return head;
        }

        fscanf(fp,"%lld",&right->numerator);
        if(right->numerator<0){
            printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
            *judge=-1;
            fclose(fp);
            return head;
        }
        read=fgetc(fp);
        while(read==' '||read=='\t'||read=='\n'){
            read=fgetc(fp);
        }
        if(read==EOF){
            *judge=-1;
            fclose(fp);
            return head;
        }

        if(read!='/'){
            printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
            *judge=-1;
            fclose(fp);
            return head;
        }

        fscanf(fp,"%lld",&right->denominator);
        if(right->denominator<=0){
            printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
            *judge=-1;
            fclose(fp);
            return head;
        }

        read=fgetc(fp);
        while(read==' '||read=='\t'||read=='\n'){
            read=fgetc(fp);
        }
        if(read==EOF){
            *judge=-1;
            fclose(fp);
            return head;
        }

        if(right->notation=='-'){
            if(read!=')'){
                printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
                *judge=-1;
                fclose(fp);
                return head;
            }
            read = fgetc(fp);
            while(read==' '||read=='\t'||read=='\n'){
                read=fgetc(fp);
            }
            if(read==EOF){
                *judge=-1;
                fclose(fp);
                return head;
            }
        }

        left=right;//指针的偏移
        if(read=='='){
            *judge=1;
            fclose(fp);
            return head;
        }

        if(read!='+'&&read!='-'){
            printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
            *judge=-1;
            fclose(fp);
            return head;
        }
    }
}

//函数原型:writeIntoFile
//返回类型:void ，参数:fraction的链表头指针
//将链表中的信息写入文件中
void writeIntoFile(fraction *head)
{
    char filename[50];

    printf("请输入你想存入的文件名:\n");
    scanf("%s",filename);//输入文件名

    FILE *fp;
    if((fp=fopen(filename,"w"))==NULL){
        printf("\n\nFile cannot be opened.\n");
        return;
    }

    fraction *right;
    right=head;
    while(right!=NULL){//循环写入文件
        if(right==head){//头指针的特殊情况
            fprintf(fp,"%c%c",head->notation=='-'?'-':' ',head->notation=='-'?'(':' ');
        }
        else{
            fprintf(fp,"%c%c",right->notation=='-'?'-':'+',right->notation=='-'?'(':' ');
        }

        if(right->i!=NULL){//整数部分的写入
            integer *cur;
            cur=right->i;
            while(cur!=NULL){
                fprintf(fp,"%d",cur->n);
                cur=cur->next;
            }
        }
        fprintf(fp," %c %lld / %lld%c\n",'+',right->numerator,right->denominator,right->notation=='-'?')':' ');//分子分母的写入
        right=right->next;
    }

    fprintf(fp,"%c",'=');//最后将等号输入文件
    fclose(fp);
    destroyFraction(head);//清理内存
    printf("\n数据已存入文件\"%s\"\n",filename);
    return;
}
