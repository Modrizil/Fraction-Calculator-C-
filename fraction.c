#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "fraction.h"

//函数原型:readFraction
//返回类型:fraction 类型的指针，参数:fraction的链表头指针
//读入用户的输入式子，只有输入正确时，式子才能被保存
fraction *readFraction(fraction *head)
{
    head=NULL;
    char read;

    read=getchar();
    while(read==' '||read=='\t'||read=='\n'){//跳过空格回车
        read=getchar();
    }

    if(!((read>='0'&&read<='9')||read=='+'||read=='-')){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }
//读取第一个分数
    switch(read){
case '+'://第一个有效字符是加号的情况
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
case '-'://第一个有效字符是减号的情况
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
default://第一个有效字符是数字的情况
    head=malloc(sizeof(fraction));
    head->next=NULL;
    head->notation='+';
    head->i=malloc(sizeof(integer));
    head->i->n=read-'0';
    head->i->last=NULL;
    head->i->next=NULL;
    break;
    }//switch 结束

    integer *pre,*cur;
    pre=head->i;
    cur=NULL;

    read=getchar();
    while(read>='0'&&read<='9'){//读完剩下的整数部分
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

    if(read!='+'){//整数与分数之间的加号运算符
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }

    scanf("%lld",&head->numerator);//读入分子
    if(head->numerator<0){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }
    read=getchar();

    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }

    if(read!='/'){//读入分子与分母之间的除法运算符
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }

    scanf("%lld",&head->denominator);//读入分母
    if(head->denominator<=0){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }
    read=getchar();
    while(read==' '||read=='\t'||read=='\n'){
        read=getchar();
    }

    if(head->notation=='-'){//若是负分数，则要加上反括号
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

    if(read=='='){//如果是等号则结束输入
        return head;
    }

    if(read!='+'&&read!='-'){
        printf("\n\nPresentation error!\n");
        destroyFraction(head);
        return NULL;
    }

//开始循环读入分数
    fraction *left,*right;//left 表示上一个，right 表示下一个
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

        left->next=right;//将链表链接起来
        left=right;//指针的偏移

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

//函数原型:destroyFraction
//返回类型:void ，参数:fraction的链表头指针
//摧毁fraction链表，清理内存
void destroyFraction(fraction *head)
{
    if(head==NULL){
        return;
    }

    fraction *temp;
    while(head!=NULL){
        destroyInteger(head->i);//清理整数部分的链表
        temp=head;
        head=head->next;
        free(temp);
    }

    return;
}

//函数原型:displayFraction
//返回类型:void ，参数:fraction的链表头指针，fraction 结构体（计算结果）
//对齐打印fraction链表和最终答案
void displayFraction(fraction *head,fraction result)
{
    if(head==NULL){
        return;
    }

    fraction *right;//用于偏移链表
    int i,n;//n表示位数,i用于循环
    n=getLen(head->i);

    for(right=head->next;right!=NULL;right=right->next){
        if(n<getLen(right->i)){
            n=getLen(right->i);
        }
    }
    n=n>getLen(result.i)?n:getLen(result.i);//得到最长的一个整数部分的长度

//打印第一个分数
    printf("   %c %c",head->notation=='-'?'-':' ',head->notation=='-'?'(':' ');
    for(i=0;i<n-getLen(head->i);i++){//打印对齐所需的空格
        printf(" ");
    }
    displayInteger(head->i);//打印整数部分
    if(head->numerator!=0){
        printf(" + ");
        printf("%20lld / %20lld%c\n",head->numerator,head->denominator,head->notation=='-'?')':' ');
    }
    else
        printf("%c\n",head->notation=='-'?')':' ');
//循环打印之后的分数
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
//打印结果前的分界线
    for(i=0;i<n+54;i++){
        printf("-");
    }

    if(result.numerator==-1){//结果无法计算，则报错表示越界
        printf("\n=  Exceeded!\n");
        return;
    }
    if(result.numerator==-2){//用于通分操作时的打印
        printf("\n=\n");
        return;
    }

    printf("\n");
    printf("=  %c %c",result.notation=='-'?'-':' ',result.notation=='-'?'(':' ');
    for(i=0;i<n-getLen(result.i);i++){//打印对齐所需的空格
        printf(" ");
    }
    displayInteger(result.i);//打印结果的整数部分
    if(result.numerator!=0){
        printf(" + ");
        printf("%20lld / %20lld%c\n",result.numerator,result.denominator,result.notation=='-'?')':' ');
    }
    else
        printf("%c\n",result.notation=='-'?')':' ');

    return;
}

//函数原型:sortFraction
//返回类型:fraction 类型的指针，参数:fraction的链表头指针
//整理分数链表，进行约分化简的操作
fraction *sortFraction(fraction *head)
{
    if(head==NULL){
        return NULL;
    }
    if(head->numerator==-1){//表明分数表达错误，直接返回
        return head;
    }

    fraction *right;//用于遍历fraction链表
    integer *tail;//用于得到整数部分的最后一位
    int i;//用于约分用的循环变量
//循环化简分数
    for(right=head;right!=NULL;right=right->next){
        for(tail=right->i;tail->next!=NULL;tail=tail->next);//得到整数部分的最后一位

        if(right->numerator>=right->denominator){//得到真分数
            tail->n+=right->numerator/right->denominator;
            right->numerator=right->numerator%right->denominator;
        }
        right->i=sortInteger(right->i);

        if(right->numerator==0){
            continue;
        }

        for(i=2;i<=right->numerator;i++){//约分
            while(right->numerator%i==0&&right->denominator%i==0){
                right->numerator/=i;
                right->denominator/=i;
            }
        }
    }

    return head;
}

//函数原型:compareFractions
//返回类型:int ，参数:两个fraction 结构体 x ，y
//比较 x ，y 的绝对值大小（x>=y返回1，反之返回0）
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

//函数原型:calculateFraction
//返回类型:fraction的结构体，参数:fraction的链表头指针
//计算fraction链表得到一个最终结果并以结构体的形式返回
fraction calculateFraction(fraction *head)
{
    fraction result;//用于存放最终结果
    fraction *cur;//用于循环遍历

    result=*head;
    result.next=NULL;

    for(cur=head->next;cur!=NULL;cur=cur->next){//循环计算
        if(result.notation=='+'&&cur->notation=='+'){//都是正分数的情况
            result=addf(result,*cur);
            if(result.numerator==-1){//计算结果越界
                return result;
            }
        }
        else if(result.notation=='-'&&cur->notation=='-'){//都是负分数的情况
            result=addf(result,*cur);
            result.notation='-';//改变结果的正负号
            if(result.numerator==-1){//计算结果越界
                return result;
            }
        }
        else{
            if(result.notation=='-'){//result为负，cur为正
                result=minusf(*cur,result);
                if(result.numerator==-1){//计算结果越界
                    return result;
                }
            }
            else{
                result=minusf(result,*cur);
                if(result.numerator==-1){//计算结果越界
                    return result;
                }
            }
        }
    }

    return result;
}

//函数原型:addf
//返回类型:fraction的结构体，参数:两个fraction的结构体
//计算两个分数并得到和，存入结构体并返回
fraction addf(fraction x, fraction y)
{
    fraction sum;//加法的结果
    sum.next=NULL;//将指针指空，避免混乱
    sum.notation='+';
    sum.i=NULL;

    sum.i=addIntegers(x.i,y.i);//整数相加
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
        if(sum.denominator/x.denominator!=y.denominator){//计算结果越界
            sum.numerator=-1;
        }
        else{
            sum.numerator=x.denominator*y.numerator+x.numerator*y.denominator;
            if((x.denominator*y.numerator)/x.denominator!=y.numerator||(x.numerator*y.denominator)/y.denominator!=x.numerator){//计算结果越界
                sum.numerator=-1;
            }
            else if(sum.numerator-x.numerator*y.denominator!=x.denominator*y.numerator){//计算结果越界
                sum.numerator=-1;
            }
        }
        sortFraction(&sum);//整理加法结果
    }

    return sum;
}

//函数原型:minusf
//返回类型:fraction的结构体，参数:两个fraction的结构体
//计算两个分数并得到差值，符号等，存入结构体返回
fraction minusf(fraction x, fraction y)
{
    fraction difference;//减法的结果
    difference.next=NULL;//指空来避免混乱

    if(compareFractions(x,y)){//分数x大于y的时候
        difference.notation='+';
        difference.i=minusIntegers(x.i,y.i);//分数相减

        if(y.numerator==0){
            difference.denominator=x.denominator;
            difference.numerator=x.numerator;
        }
        else if(x.numerator==0){
            integer *tail;
            for(tail=difference.i;tail->next!=NULL;tail=tail->next);
            tail->n-=1;//得到整数的最后一位，退一位，加到分数部分进行运算

            difference.denominator=y.denominator;
            difference.numerator=y.denominator-y.numerator;
        }
        else{
            difference.denominator=x.denominator*y.denominator;
            if(difference.denominator/x.denominator!=y.denominator){//计算结果越界
                difference.numerator=-1;
                difference.i=sortInteger(difference.i);
                return difference;
            }

            if(x.numerator*y.denominator-x.denominator*y.numerator>=0){//分数部分的比较

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

    else{//分数x小于y的时候
        difference.notation='-';
        difference.i=minusIntegers(y.i,x.i);//分数相减
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
                if(difference.denominator/x.denominator!=y.denominator){//计算结果越界
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
                if(difference.denominator/x.denominator!=y.denominator){//计算结果越界
                    difference.numerator=-1;
                    return difference;
                }
                difference.numerator=y.denominator*x.denominator+y.numerator*x.denominator-y.denominator*x.numerator;
            }
        }
    }

    sortFraction(&difference);//整理分数结果
    return difference;
}
