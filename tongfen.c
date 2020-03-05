#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tongfen.h"

//函数原型:displayTongfen
//返回类型:void ，参数:fraction的链表头指针
//打印分数的通分结果
void displayTongfen(fraction *head)
{
    if(head==NULL){
        return;
    }

    fraction *right,answer;//right 用于遍历，answer 用于存放计算结果
    right=head->next;
    answer.i=NULL;//指针指空
    answer.next=NULL;//指针指空
//都是正分数的情况
    if(head->notation=='+'&&right->notation=='+'){
        answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
        if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//计算结果越界
            printf("   Exceeded!\n");
            return;
        }
        answer.numerator=answer.denominator/head->denominator*head->numerator+answer.denominator/right->denominator*right->numerator;
        if(answer.numerator-answer.denominator/head->denominator*head->numerator!=answer.denominator/right->denominator*right->numerator){//计算结果越界
            printf("   Exceeded!\n");
            return;
        }
        answer.i=addIntegers(head->i,right->i);//整数部分相加
        answer.i=sortInteger(answer.i);//整理整数部分
        printf("      ");
        displayInteger(answer.i);
        //打印通分过程
        printf(" + (%lld*%lld)/(%lld*%lld)+(%lld*%lld)/(%lld*%lld)\n",head->numerator,answer.denominator/head->denominator,
                                                                      head->denominator,answer.denominator/head->denominator,
                                                                      right->numerator,answer.denominator/right->denominator,
                                                                      right->denominator,answer.denominator/right->denominator);
        //再次打印化简结果
        printf("\n=     ");
        displayInteger(answer.i);
        printf(" + %lld / %lld\n",answer.numerator,answer.denominator);

        while(CommonDivisor(answer.denominator,answer.numerator)!=1||answer.numerator>=answer.denominator){
            if(answer.numerator>=answer.denominator){//得到真分数
                integer *tail;
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + %d",answer.numerator/answer.denominator);
                for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                tail->n+=answer.numerator/answer.denominator;
                answer.numerator%=answer.denominator;
                answer.i=sortInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
            long long int mid;
            mid=CommonDivisor(answer.numerator,answer.denominator);//得到约分的因子
            printf("\n=     ");
            displayInteger(answer.i);
            printf(" + (%lld*%lld) / (%lld*%lld)\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

            answer.denominator/=mid;
            answer.numerator/=mid;
            //打印化简结果
            printf("\n=     ");
            displayInteger(answer.i);
            printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
        }
    }
//都是负分数的情况
    else if(head->notation=='-'&&right->notation=='-'){
        answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
        if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//计算结果越界
            printf("   Exceeded!\n");
            return;
        }
        answer.numerator=answer.denominator/head->denominator*head->numerator+answer.denominator/right->denominator*right->numerator;
        if(answer.numerator-answer.denominator/head->denominator*head->numerator!=answer.denominator/right->denominator*right->numerator){//计算结果越界
            printf("   Exceeded!\n");
            return;
        }
        answer.i=addIntegers(head->i,right->i);//整数相加
        answer.i=sortInteger(answer.i);//整理整数
        printf("   - (");
        displayInteger(answer.i);
        //打印通分过程
        printf(" + (%lld*%lld)/(%lld*%lld)+(%lld*%lld)/(%lld*%lld) )\n",head->numerator,answer.denominator/head->denominator,
                                                                      head->denominator,answer.denominator/head->denominator,
                                                                      right->numerator,answer.denominator/right->denominator,
                                                                      right->denominator,answer.denominator/right->denominator);
        //再次打印化简过程
        printf("\n=  - (");
        displayInteger(answer.i);
        printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);

        while(CommonDivisor(answer.denominator,answer.numerator)!=1||answer.numerator>=answer.denominator){
            if(answer.numerator>=answer.denominator){//得到真分数
                integer *tail;
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %d",answer.numerator/answer.denominator);
                for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                tail->n+=answer.numerator/answer.denominator;
                answer.numerator%=answer.denominator;
                answer.i=sortInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
            long long int mid;
            mid=CommonDivisor(answer.numerator,answer.denominator);//得到约分的因子
            printf("\n=  - (");
            displayInteger(answer.i);
            printf(" + (%lld*%lld) / (%lld*%lld) )\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

            answer.denominator/=mid;
            answer.numerator/=mid;
            //打印化简结果
            printf("\n=  - (");
            displayInteger(answer.i);
            printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
        }
    }
//第一个是正分数，第二个是负分数的情况
    else if(head->notation=='+'&&right->notation=='-'){
        if(compareFractions(*head,*right)){//head 大于等于 right 时
            answer.notation=='+';
            answer.i=minusIntegers(head->i,right->i);

            if(right->numerator==0){
                answer.denominator=head->denominator;
                answer.numerator=head->numerator;
                answer.i=sortInteger(answer.i);
                printf("      ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
            else if(head->numerator==0){
                integer *tail;
                printf("\n   - (");
                answer.i=sortInteger(answer.i);
                displayInteger(answer.i);
                printf(" - %d",1);
                for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                tail->n-=1;//退位
                answer.i=sortInteger(answer.i);

                answer.denominator=right->denominator;
                answer.numerator=right->denominator-right->numerator;
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                //再次打印化简结果
                printf("      ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
                if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//计算结果越界
                    answer.numerator=-1;
                    printf("   Exceeded!\n");
                    return;
                }

                if(head->numerator*right->denominator-head->denominator*right->numerator>=0){
                    answer.numerator=head->numerator*right->denominator/CommonDivisor(head->denominator,right->denominator)
                    -head->denominator*right->numerator/CommonDivisor(head->denominator,right->denominator);
                    printf("      ");
                    answer.i=sortInteger(answer.i);
                    displayInteger(answer.i);
                    //打印通分过程
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=     ");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                }
                else{
                    printf("      ");
                    answer.i=sortInteger(answer.i);
                    displayInteger(answer.i);
                    printf(" - %d",1);
                    integer *tail;
                    for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                    tail->n-=1;
                    answer.i=sortInteger(answer.i);

                    answer.numerator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator)
                                     +head->numerator*right->denominator/CommonDivisor(head->denominator,right->denominator)
                                     -head->denominator*right->numerator/CommonDivisor(head->denominator,right->denominator);
                    //打印通分过程
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",answer.denominator,answer.denominator,
                                                                                                head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=     ");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//得到约分因子
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld)\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //打印化简结果
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
        }
        else{//head 小于 right时
            answer.notation=='-';
            answer.i=minusIntegers(right->i,head->i);//整数部分相减

            if(head->numerator==0){
                answer.denominator=right->denominator;
                answer.numerator=right->numerator;
                answer.i=sortInteger(answer.i);
                printf("\n   - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
            else if(right->numerator==0){
                integer *tail;
                printf("\n   - (");
                answer.i=sortInteger(answer.i);
                displayInteger(answer.i);
                printf(" - %d",1);
                for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                tail->n-=1;//退位
                answer.i=sortInteger(answer.i);

                answer.denominator=head->denominator;
                answer.numerator=head->denominator-head->numerator;
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                //再次打印化简结果
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=right->denominator*head->denominator/CommonDivisor(right->denominator,head->denominator);
                if(answer.denominator/right->denominator!=head->denominator/CommonDivisor(right->denominator,head->denominator)){//计算结果越界
                    answer.numerator=-1;
                    printf("   Exceeded!\n");
                    return;
                }

                if(right->numerator*head->denominator/CommonDivisor(right->denominator,head->denominator)-right->denominator*head->numerator/CommonDivisor(right->denominator,head->denominator)>=0){
                    answer.numerator=right->numerator*head->denominator/CommonDivisor(right->denominator,head->denominator)
                                     -right->denominator*head->numerator/CommonDivisor(right->denominator,head->denominator);
                    printf("\n   - (");
                    answer.i=sortInteger(answer.i);
                    displayInteger(answer.i);
                    //打印通分结果
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=  - (");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                }
                else{
                    printf("\n   - (");
                    answer.i=sortInteger(answer.i);
                    displayInteger(answer.i);
                    printf(" - %d",1);
                    integer *tail;
                    for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                    tail->n-=1;//退位

                    answer.numerator=right->denominator*head->denominator+right->numerator*head->denominator-right->denominator*head->numerator;
                    //打印通分过程
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",answer.denominator,answer.denominator,
                                                                                                  right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=  - (");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//得到约分的因子
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld) )\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //打印化简结果
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
        }
    }
//第一个是负分数，第二个是正分数
    else{
        if(compareFractions(*head,*right)){//head 大于等于 right 时
            answer.notation=='-';
            answer.i=minusIntegers(head->i,right->i);//整数部分相减

            if(right->numerator==0){
                answer.denominator=head->denominator;
                answer.numerator=head->numerator;
                answer.i=sortInteger(answer.i);
                printf("\n   - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
            else if(head->numerator==0){
                integer *tail;
                printf("\n   - (");
                answer.i=sortInteger(answer.i);
                displayInteger(answer.i);
                printf(" - %d",1);
                for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                tail->n-=1;//退位
                answer.i=sortInteger(answer.i);

                answer.denominator=right->denominator;
                answer.numerator=right->denominator-right->numerator;
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                //再次打印化简结果
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
                if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//计算结果越界
                    answer.numerator=-1;
                    printf("   Exceeded!\n");
                    return;
                }

                if(head->numerator*right->denominator/CommonDivisor(head->denominator,right->denominator)-head->denominator*right->numerator/CommonDivisor(head->denominator,right->denominator)>=0){
                    answer.numerator=head->numerator*right->denominator/CommonDivisor(head->denominator,right->denominator)
                                     -head->denominator*right->numerator/CommonDivisor(head->denominator,right->denominator);
                    printf("\n   - (");
                    displayInteger(answer.i);
                    //打印通分过程
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=  - (");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                }
                else{
                    printf("\n   - (");
                    answer.i=sortInteger(answer.i);
                    displayInteger(answer.i);
                    printf(" - %d",1);
                    integer *tail;
                    for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                    tail->n-=1;//退位
                    answer.i=sortInteger(answer.i);

                    answer.numerator=head->denominator*right->denominator+head->numerator*right->denominator-head->denominator*right->numerator;
                    //打印通分过程
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",answer.denominator,answer.denominator,
                                                                                                  head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=  - (");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//得到约分因子
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld) )\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //打印化简结果
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
        }
        else{
            answer.notation=='+';
            answer.i=minusIntegers(right->i,head->i);//整数部分相减

            if(head->numerator==0){
                answer.denominator=right->denominator;
                answer.numerator=right->numerator;
                answer.i=sortInteger(answer.i);
                printf("\n      ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
            else if(right->numerator==0){
                integer *tail;
                printf("\n      ");
                answer.i=sortInteger(answer.i);
                displayInteger(answer.i);
                printf(" - %d",1);
                for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                tail->n-=1;//退位
                answer.i=sortInteger(answer.i);

                answer.denominator=head->denominator;
                answer.numerator=head->denominator-head->numerator;
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                //再次打印化简结果
                printf("\n      ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=right->denominator*head->denominator/CommonDivisor(head->denominator,right->denominator);
                if(answer.denominator/right->denominator!=head->denominator/CommonDivisor(head->denominator,right->denominator)){//计算结果越界
                    answer.numerator=-1;
                    printf("   Exceeded!\n");
                    return;
                }

                if(right->numerator*head->denominator/CommonDivisor(head->denominator,right->denominator)-right->denominator*head->numerator/CommonDivisor(head->denominator,right->denominator)>=0){
                    answer.numerator=right->numerator*head->denominator/CommonDivisor(head->denominator,right->denominator)
                                     -right->denominator*head->numerator/CommonDivisor(head->denominator,right->denominator);
                    printf("\n      ");
                    displayInteger(answer.i);
                    //打印通分过程
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=     ");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                }
                else{
                    printf("\n      ");
                    answer.i=sortInteger(answer.i);
                    displayInteger(answer.i);
                    printf(" - %d",1);
                    integer *tail;
                    for(tail=answer.i;tail->next!=NULL;tail=tail->next);
                    tail->n-=1;//退位
                    answer.i=sortInteger(answer.i);

                    answer.numerator=right->denominator*head->denominator+right->numerator*head->denominator-right->denominator*head->numerator;
                    //打印通分过程
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",answer.denominator,answer.denominator,
                                                                                                right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //再次打印化简结果
                    printf("\n=     ");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//得到约分因子
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld)\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //打印化简结果
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
        }
    }
}

//函数原型:CommonDivisor
//返回类型:long long int ，参数:两个long long int 类型的整数
//得到a ，b的最大公约数
long long int CommonDivisor(long long int a,long long int b)
{
    if(a*b==0)
    return (a ==0?b:a);
    if(a>b)
    return CommonDivisor(a%b,b);
    else if(a<b)
    return CommonDivisor(b%a,a);
}
