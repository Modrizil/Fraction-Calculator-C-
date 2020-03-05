#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "fraction.h"

//����ԭ��:readFile
//��������:fraction���͵�ָ�룬����:�ַ�ָ�루�ַ��������ж����ӣ�*judge==-1ʱ��ʾ����ʧ�ܣ�*judge==1ʱ��ʾ����ɹ���
//��������е��ļ������ж��Ƿ����ɹ��������ͷָ��
fraction *readFile(const char *filename,int *judge)
{
    FILE *fp;
    *judge=0;
    if((fp=fopen(filename,"r"))==NULL){//���ļ�
        printf("\n\nFile can not be opened.\n");
        *judge=-1;
        return NULL;
    }

    fraction *head;//����ͷָ��
    head=NULL;
    char read;

    read=fgetc(fp);//һ��һ���ַ�����
    while(read==' '||read=='\t'||read=='\n'){//�����ո�س�
        read=fgetc(fp);
    }
    if(read==EOF){
        *judge=-1;
        fclose(fp);
        return head;
    }

    if(!((read>='0'&&read<='9')||read=='+'||read=='-')){//��Ч����
        *judge=-1;
        fclose(fp);
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        return head;
    }

    switch (read){
case '+'://��һ����Ч�ַ��ǼӺŵ����
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
case '-'://��һ����Ч�ַ��Ǽ��ŵ����
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
default://��һ����Ч�ַ������ֵ����
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
    }//switch ����

    integer *pre,*cur;
    pre=head->i;
    cur=NULL;

    read=fgetc(fp);
    while(read>='0'&&read<='9'){//����ʣ�µ���������
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

    if(read!='+'){//���������֮��ļӺ������
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }

    fscanf(fp,"%lld",&head->numerator);//�������
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

    if(read!='/'){//����������ĸ֮��ĳ��������
        printf("\n\nPresentation error!\nFailed to read \"%s\".\n",filename);
        *judge=-1;
        fclose(fp);
        return head;
    }

    fscanf(fp,"%lld",&head->denominator);//�����ĸ
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

    if(head->notation=='-'){//���Ǹ���������Ҫ���Ϸ�����
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

    if(read=='='){//����ǵȺ����������
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

    fraction *left,*right;//left ��ʾ��һ����right ��ʾ��һ��
    left = head;
    right=NULL;
    while(1){//��ʼѭ������
        right=malloc(sizeof(fraction));
        right->next=NULL;
        right->i=NULL;
        right->notation=read;
        right->numerator=-1;
        right->denominator=-1;
        left->next=right;//��������������

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

        left=right;//ָ���ƫ��
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

//����ԭ��:writeIntoFile
//��������:void ������:fraction������ͷָ��
//�������е���Ϣд���ļ���
void writeIntoFile(fraction *head)
{
    char filename[50];

    printf("���������������ļ���:\n");
    scanf("%s",filename);//�����ļ���

    FILE *fp;
    if((fp=fopen(filename,"w"))==NULL){
        printf("\n\nFile cannot be opened.\n");
        return;
    }

    fraction *right;
    right=head;
    while(right!=NULL){//ѭ��д���ļ�
        if(right==head){//ͷָ����������
            fprintf(fp,"%c%c",head->notation=='-'?'-':' ',head->notation=='-'?'(':' ');
        }
        else{
            fprintf(fp,"%c%c",right->notation=='-'?'-':'+',right->notation=='-'?'(':' ');
        }

        if(right->i!=NULL){//�������ֵ�д��
            integer *cur;
            cur=right->i;
            while(cur!=NULL){
                fprintf(fp,"%d",cur->n);
                cur=cur->next;
            }
        }
        fprintf(fp," %c %lld / %lld%c\n",'+',right->numerator,right->denominator,right->notation=='-'?')':' ');//���ӷ�ĸ��д��
        right=right->next;
    }

    fprintf(fp,"%c",'=');//��󽫵Ⱥ������ļ�
    fclose(fp);
    destroyFraction(head);//�����ڴ�
    printf("\n�����Ѵ����ļ�\"%s\"\n",filename);
    return;
}
