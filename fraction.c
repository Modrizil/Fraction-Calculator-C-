#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "fraction.h"

//����ԭ��:readFraction
//��������:fraction ���͵�ָ�룬����:fraction������ͷָ��
//�����û�������ʽ�ӣ�ֻ��������ȷʱ��ʽ�Ӳ��ܱ�����
fraction *readFraction(fraction *head)
{
    head=NULL;
    char read;

    read=getchar();
    while(read==' '||read=='\t'||read=='\n'){//�����ո�س�
        read=getchar();
    }

    if(!((read>='0'&&read<='9')||read=='+'||read=='-')){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }
//��ȡ��һ������
    switch(read){
case '+'://��һ����Ч�ַ��ǼӺŵ����
    head=malloc(sizeof(fraction));
    head->next=NULL;
    head->i=NULL;
    head->notation='+';
    read=getchar();
    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }

    if(!(read>='0'&&read<='9')){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
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
    read=getchar();
    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }
    if(read!='('){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }

    read=getchar();
    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }
    if(!(read>='0'&&read<='9')){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
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
    head->i=malloc(sizeof(integer));
    head->i->n=read-'0';
    head->i->last=NULL;
    head->i->next=NULL;
    break;
    }//switch ����

    integer *pre,*cur;
    pre=head->i;
    cur=NULL;

    read=getchar();
    while(read>='0'&&read<='9'){//����ʣ�µ���������
        cur=malloc(sizeof(integer));
        cur->n=read-'0';
        cur->next=NULL;
        cur->last=pre;
        pre->next=cur;
        pre=cur;
        read=getchar();
    }

    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }

    if(read!='+'){//���������֮��ļӺ������
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }

    scanf("%lld",&head->numerator);//�������
    if(head->numerator<0){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }
    read=getchar();

    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }

    if(read!='/'){//����������ĸ֮��ĳ��������
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }

    scanf("%lld",&head->denominator);//�����ĸ
    if(head->denominator<=0){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }
    read=getchar();
    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }

    if(head->notation=='-'){//���Ǹ���������Ҫ���Ϸ�����
        if(read!=')'){
            printf("\n\nPresentation error!\n");
            destroyFraction(head);
            return NULL;
        }
        read=getchar();
        while(read==' '||read=='\t'||read=='\n'){
            read=getchar();
        }
    }

    if(read=='='){//����ǵȺ����������
        return head;
    }

    if(read!='+'&&read!='-'){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }

//��ʼѭ���������
    fraction *left,*right;//left ��ʾ��һ����right ��ʾ��һ��
    left=head;
    right=NULL;

    while(1){
        right=malloc(sizeof(fraction));
        right->next=NULL;
        right->i=NULL;
        right->notation=read;
        read=getchar();
        while(read==' '||read=='\t'||read=='\n'){
            read=getchar();
        }

        if(right->notation=='-'){
            if(read!='('){
                printf("\n\nPresentation error!\n");
                destroyFraction(head);
                return NULL;
            }
            read=getchar();
            while(read==' '||read=='\t'||read=='\n'){
                read=getchar();
            }
        }

        if(!(read>='0'&&read<='9')){
            printf("\n\nPresentation error!\n");
            destroyFraction(head);
            return NULL;
        }
        right->i=malloc(sizeof(integer));
        right->i->n=read-'0';
        right->i->last=NULL;
        right->i->next=NULL;
        pre=right->i;
        cur=NULL;

        read=getchar();
        while(read>='0'&&read<='9'){
            cur=malloc(sizeof(integer));
            cur->n=read-'0';
            cur->next=NULL;
            cur->last=pre;
            pre->next=cur;
            pre=cur;
            read=getchar();
        }

        while(read==' '||read=='\t'||read=='\n'){
            read=getchar();
        }

        if(read!='+'){
            printf("\n\nPresentation error!\n");
            destroyFraction(head);
            return NULL;
        }

        scanf("%lld",&right->numerator);
        if(right->numerator<0){
            printf("\n\nPresentation error!\n");
            destroyFraction(head);
            return NULL;
        }
        read=getchar();

        while(read==' '||read=='\t'||read=='\n'){
            read=getchar();
        }

        if(read!='/'){
            printf("\n\nPresentation error!\n");
            destroyFraction(head);
            return NULL;
        }

        scanf("%lld",&right->denominator);
        if(right->denominator<=0){
            printf("\n\nPresentation error!\n");
            destroyFraction(head);
            return NULL;
        }
        read=getchar();
        while(read==' '||read=='\t'||read=='\n'){
            read=getchar();
        }

        if(right->notation=='-'){
            if(read!=')'){
                printf("\n\nPresentation error!\n");
                destroyFraction(head);
                return NULL;
            }
            read=getchar();
            while(read==' '||read=='\t'||read=='\n'){
                read=getchar();
            }
        }

        left->next=right;//��������������
        left=right;//ָ���ƫ��

        if(read=='='){
            return head;
        }

        if(read!='+'&&read!='-'){
            printf("Presentation error!\n");
            destroyFraction(head);
            return NULL;
        }
    }
}

//����ԭ��:destroyFraction
//��������:void ������:fraction������ͷָ��
//�ݻ�fraction���������ڴ�
void destroyFraction(fraction *head)
{
    if(head==NULL){
        return;
    }

    fraction *temp;
    while(head!=NULL){
        destroyInteger(head->i);//�����������ֵ�����
        temp=head;
        head=head->next;
        free(temp);
    }

    return;
}

//����ԭ��:displayFraction
//��������:void ������:fraction������ͷָ�룬fraction �ṹ�壨��������
//�����ӡfraction��������մ�
void displayFraction(fraction *head,fraction result)
{
    if(head==NULL){
        return;
    }

    fraction *right;//����ƫ������
    int i,n;//n��ʾλ��,i����ѭ��
    n=getLen(head->i);

    for(right=head->next;right!=NULL;right=right->next){
        if(n<getLen(right->i)){
            n=getLen(right->i);
        }
    }
    n=n>getLen(result.i)?n:getLen(result.i);//�õ����һ���������ֵĳ���

//��ӡ��һ������
    printf("   %c %c",head->notation=='-'?'-':' ',head->notation=='-'?'(':' ');
    for(i=0;i<n-getLen(head->i);i++){//��ӡ��������Ŀո�
        printf(" ");
    }
    displayInteger(head->i);//��ӡ��������
    if(head->numerator!=0){
        printf(" + ");
        printf("%20lld / %20lld%c\n",head->numerator,head->denominator,head->notation=='-'?')':' ');
    }
    else
        printf("%c\n",head->notation=='-'?')':' ');
//ѭ����ӡ֮��ķ���
    for(right=head->next;right!=NULL;right=right->next){
        printf("   %c %c",right->notation,right->notation=='-'?'(':' ');
        for(i=0;i<n-getLen(right->i);i++){
            printf(" ");
        }
        displayInteger(right->i);
        if(right->numerator!=0){
            printf(" + ");
            printf("%20lld / %20lld%c\n",right->numerator,right->denominator,right->notation=='-'?')':' ');
        }
        else
            printf("%c\n",right->notation=='-'?')':' ');
    }
//��ӡ���ǰ�ķֽ���
    for(i=0;i<n+54;i++){
        printf("-");
    }

    if(result.numerator==-1){//����޷����㣬�򱨴��ʾԽ��
        printf("\n=  Exceeded!\n");
        return;
    }
    if(result.numerator==-2){//����ͨ�ֲ���ʱ�Ĵ�ӡ
        printf("\n=\n");
        return;
    }

    printf("\n");
    printf("=  %c %c",result.notation=='-'?'-':' ',result.notation=='-'?'(':' ');
    for(i=0;i<n-getLen(result.i);i++){//��ӡ��������Ŀո�
        printf(" ");
    }
    displayInteger(result.i);//��ӡ�������������
    if(result.numerator!=0){
        printf(" + ");
        printf("%20lld / %20lld%c\n",result.numerator,result.denominator,result.notation=='-'?')':' ');
    }
    else
        printf("%c\n",result.notation=='-'?')':' ');

    return;
}

//����ԭ��:sortFraction
//��������:fraction ���͵�ָ�룬����:fraction������ͷָ��
//���������������Լ�ֻ���Ĳ���
fraction *sortFraction(fraction *head)
{
    if(head==NULL){
        return NULL;
    }
    if(head->numerator==-1){//��������������ֱ�ӷ���
        return head;
    }

    fraction *right;//���ڱ���fraction����
    integer *tail;//���ڵõ��������ֵ����һλ
    int i;//����Լ���õ�ѭ������
//ѭ���������
    for(right=head;right!=NULL;right=right->next){
        for(tail=right->i;tail->next!=NULL;tail=tail->next);//�õ��������ֵ����һλ

        if(right->numerator>=right->denominator){//�õ������
            tail->n+=right->numerator/right->denominator;
            right->numerator=right->numerator%right->denominator;
        }
        right->i=sortInteger(right->i);

        if(right->numerator==0){
            continue;
        }

        for(i=2;i<=right->numerator;i++){//Լ��
            while(right->numerator%i==0&&right->denominator%i==0){
                right->numerator/=i;
                right->denominator/=i;
            }
        }
    }

    return head;
}

//����ԭ��:compareFractions
//��������:int ������:����fraction �ṹ�� x ��y
//�Ƚ� x ��y �ľ���ֵ��С��x>=y����1����֮����0��
int compareFractions(fraction x,fraction y)
{
    if(getLen(x.i)>getLen(y.i)){
        return 1;
    }
    if(getLen(x.i)==getLen(y.i)){
        integer *curX,*curY;
        curX=x.i;
        curY=y.i;
        while(curX!=NULL){
            if(curX->n>curY->n)return 1;
            if(curX->n<curY->n)return 0;
            curX=curX->next;
            curY=curY->next;
        }
        if(x.numerator*y.denominator-x.denominator*y.numerator>=0)return 1;
        else return 0;
    }
    return 0;
}

//����ԭ��:calculateFraction
//��������:fraction�Ľṹ�壬����:fraction������ͷָ��
//����fraction����õ�һ�����ս�����Խṹ�����ʽ����
fraction calculateFraction(fraction *head)
{
    fraction result;//���ڴ�����ս��
    fraction *cur;//����ѭ������

    result=*head;
    result.next=NULL;

    for(cur=head->next;cur!=NULL;cur=cur->next){//ѭ������
        if(result.notation=='+'&&cur->notation=='+'){//���������������
            result=addf(result,*cur);
            if(result.numerator==-1){//������Խ��
                return result;
            }
        }
        else if(result.notation=='-'&&cur->notation=='-'){//���Ǹ����������
            result=addf(result,*cur);
            result.notation='-';//�ı�����������
            if(result.numerator==-1){//������Խ��
                return result;
            }
        }
        else{
            if(result.notation=='-'){//resultΪ����curΪ��
                result=minusf(*cur,result);
                if(result.numerator==-1){//������Խ��
                    return result;
                }
            }
            else{
                result=minusf(result,*cur);
                if(result.numerator==-1){//������Խ��
                    return result;
                }
            }
        }
    }

    return result;
}

//����ԭ��:addf
//��������:fraction�Ľṹ�壬����:����fraction�Ľṹ��
//���������������õ��ͣ�����ṹ�岢����
fraction addf(fraction x, fraction y)
{
    fraction sum;//�ӷ��Ľ��
    sum.next=NULL;//��ָ��ָ�գ��������
    sum.notation='+';
    sum.i=NULL;

    sum.i=addIntegers(x.i,y.i);//�������
    if(x.numerator==0&&y.numerator!=0){
        sum.denominator=y.denominator;
        sum.numerator=y.numerator;
    }
    else if(y.numerator==0&&x.numerator!=0){
        sum.denominator=x.denominator;
        sum.numerator=x.numerator;
    }
    else{
        sum.denominator=x.denominator*y.denominator;
        if(sum.denominator/x.denominator!=y.denominator){//������Խ��
            sum.numerator=-1;
        }
        else{
            sum.numerator=x.denominator*y.numerator+x.numerator*y.denominator;
            if((x.denominator*y.numerator)/x.denominator!=y.numerator||(x.numerator*y.denominator)/y.denominator!=x.numerator){//������Խ��
                sum.numerator=-1;
            }
            else if(sum.numerator-x.numerator*y.denominator!=x.denominator*y.numerator){//������Խ��
                sum.numerator=-1;
            }
        }
        sortFraction(&sum);//����ӷ����
    }

    return sum;
}

//����ԭ��:minusf
//��������:fraction�Ľṹ�壬����:����fraction�Ľṹ��
//���������������õ���ֵ�����ŵȣ�����ṹ�巵��
fraction minusf(fraction x, fraction y)
{
    fraction difference;//�����Ľ��
    difference.next=NULL;//ָ�����������

    if(compareFractions(x,y)){//����x����y��ʱ��
        difference.notation='+';
        difference.i=minusIntegers(x.i,y.i);//�������

        if(y.numerator==0){
            difference.denominator=x.denominator;
            difference.numerator=x.numerator;
        }
        else if(x.numerator==0){
            integer *tail;
            for(tail=difference.i;tail->next!=NULL;tail=tail->next);
            tail->n-=1;//�õ����������һλ����һλ���ӵ��������ֽ�������

            difference.denominator=y.denominator;
            difference.numerator=y.denominator-y.numerator;
        }
        else{
            difference.denominator=x.denominator*y.denominator;
            if(difference.denominator/x.denominator!=y.denominator){//������Խ��
                difference.numerator=-1;
                difference.i=sortInteger(difference.i);
                return difference;
            }

            if(x.numerator*y.denominator-x.denominator*y.numerator>=0){//�������ֵıȽ�

                difference.numerator=x.numerator*y.denominator-x.denominator*y.numerator;
            }
            else{
                integer *tail;
                for(tail=difference.i;tail->next!=NULL;tail=tail->next);
                tail->n-=1;

                difference.numerator=x.denominator*y.denominator+x.numerator*y.denominator-x.denominator*y.numerator;
            }
        }
    }

    else{//����xС��y��ʱ��
        difference.notation='-';
        difference.i=minusIntegers(y.i,x.i);//�������
        if(x.numerator==0){
            difference.denominator=y.denominator;
            difference.numerator=y.numerator;
        }
        else if(y.numerator==0){
            integer *tail;
            for(tail=difference.i;tail->next!=NULL;tail=tail->next);
            tail->n-=1;

            difference.denominator=x.denominator;
            difference.numerator=x.denominator-x.numerator;
        }
        else{
            if(y.numerator*x.denominator-y.denominator*x.numerator>=0){
                difference.denominator=y.denominator*x.denominator;
                if(difference.denominator/x.denominator!=y.denominator){//������Խ��
                    difference.numerator=-1;
                    return difference;
                }
                difference.numerator=y.numerator*x.denominator-y.denominator*x.numerator;
            }
            else{
                integer *tail;
                for(tail=difference.i;tail->next!=NULL;tail=tail->next);
                tail->n-=1;

                difference.denominator=x.denominator*y.denominator;
                if(difference.denominator/x.denominator!=y.denominator){//������Խ��
                    difference.numerator=-1;
                    return difference;
                }
                difference.numerator=y.denominator*x.denominator+y.numerator*x.denominator-y.denominator*x.numerator;
            }
        }
    }

    sortFraction(&difference);//����������
    return difference;
}
