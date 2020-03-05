#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tongfen.h"

//����ԭ��:displayTongfen
//��������:void ������:fraction������ͷָ��
//��ӡ������ͨ�ֽ��
void displayTongfen(fraction *head)
{
    if(head==NULL){
        return;
    }

    fraction *right,answer;//right ���ڱ�����answer ���ڴ�ż�����
    right=head->next;
    answer.i=NULL;//ָ��ָ��
    answer.next=NULL;//ָ��ָ��
//���������������
    if(head->notation=='+'&&right->notation=='+'){
        answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
        if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//������Խ��
            printf("   Exceeded!\n");
            return;
        }
        answer.numerator=answer.denominator/head->denominator*head->numerator+answer.denominator/right->denominator*right->numerator;
        if(answer.numerator-answer.denominator/head->denominator*head->numerator!=answer.denominator/right->denominator*right->numerator){//������Խ��
            printf("   Exceeded!\n");
            return;
        }
        answer.i=addIntegers(head->i,right->i);//�����������
        answer.i=sortInteger(answer.i);//������������
        printf("      ");
        displayInteger(answer.i);
        //��ӡͨ�ֹ���
        printf(" + (%lld*%lld)/(%lld*%lld)+(%lld*%lld)/(%lld*%lld)\n",head->numerator,answer.denominator/head->denominator,
                                                                      head->denominator,answer.denominator/head->denominator,
                                                                      right->numerator,answer.denominator/right->denominator,
                                                                      right->denominator,answer.denominator/right->denominator);
        //�ٴδ�ӡ������
        printf("\n=     ");
        displayInteger(answer.i);
        printf(" + %lld / %lld\n",answer.numerator,answer.denominator);

        while(CommonDivisor(answer.denominator,answer.numerator)!=1||answer.numerator>=answer.denominator){
            if(answer.numerator>=answer.denominator){//�õ������
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
            mid=CommonDivisor(answer.numerator,answer.denominator);//�õ�Լ�ֵ�����
            printf("\n=     ");
            displayInteger(answer.i);
            printf(" + (%lld*%lld) / (%lld*%lld)\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

            answer.denominator/=mid;
            answer.numerator/=mid;
            //��ӡ������
            printf("\n=     ");
            displayInteger(answer.i);
            printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
        }
    }
//���Ǹ����������
    else if(head->notation=='-'&&right->notation=='-'){
        answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
        if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//������Խ��
            printf("   Exceeded!\n");
            return;
        }
        answer.numerator=answer.denominator/head->denominator*head->numerator+answer.denominator/right->denominator*right->numerator;
        if(answer.numerator-answer.denominator/head->denominator*head->numerator!=answer.denominator/right->denominator*right->numerator){//������Խ��
            printf("   Exceeded!\n");
            return;
        }
        answer.i=addIntegers(head->i,right->i);//�������
        answer.i=sortInteger(answer.i);//��������
        printf("   - (");
        displayInteger(answer.i);
        //��ӡͨ�ֹ���
        printf(" + (%lld*%lld)/(%lld*%lld)+(%lld*%lld)/(%lld*%lld) )\n",head->numerator,answer.denominator/head->denominator,
                                                                      head->denominator,answer.denominator/head->denominator,
                                                                      right->numerator,answer.denominator/right->denominator,
                                                                      right->denominator,answer.denominator/right->denominator);
        //�ٴδ�ӡ�������
        printf("\n=  - (");
        displayInteger(answer.i);
        printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);

        while(CommonDivisor(answer.denominator,answer.numerator)!=1||answer.numerator>=answer.denominator){
            if(answer.numerator>=answer.denominator){//�õ������
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
            mid=CommonDivisor(answer.numerator,answer.denominator);//�õ�Լ�ֵ�����
            printf("\n=  - (");
            displayInteger(answer.i);
            printf(" + (%lld*%lld) / (%lld*%lld) )\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

            answer.denominator/=mid;
            answer.numerator/=mid;
            //��ӡ������
            printf("\n=  - (");
            displayInteger(answer.i);
            printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
        }
    }
//��һ�������������ڶ����Ǹ����������
    else if(head->notation=='+'&&right->notation=='-'){
        if(compareFractions(*head,*right)){//head ���ڵ��� right ʱ
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
                tail->n-=1;//��λ
                answer.i=sortInteger(answer.i);

                answer.denominator=right->denominator;
                answer.numerator=right->denominator-right->numerator;
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                //�ٴδ�ӡ������
                printf("      ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
                if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//������Խ��
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
                    //��ӡͨ�ֹ���
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
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
                    //��ӡͨ�ֹ���
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",answer.denominator,answer.denominator,
                                                                                                head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
                    printf("\n=     ");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//�õ�Լ������
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld)\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //��ӡ������
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
        }
        else{//head С�� rightʱ
            answer.notation=='-';
            answer.i=minusIntegers(right->i,head->i);//�����������

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
                tail->n-=1;//��λ
                answer.i=sortInteger(answer.i);

                answer.denominator=head->denominator;
                answer.numerator=head->denominator-head->numerator;
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                //�ٴδ�ӡ������
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=right->denominator*head->denominator/CommonDivisor(right->denominator,head->denominator);
                if(answer.denominator/right->denominator!=head->denominator/CommonDivisor(right->denominator,head->denominator)){//������Խ��
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
                    //��ӡͨ�ֽ��
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
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
                    tail->n-=1;//��λ

                    answer.numerator=right->denominator*head->denominator+right->numerator*head->denominator-right->denominator*head->numerator;
                    //��ӡͨ�ֹ���
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",answer.denominator,answer.denominator,
                                                                                                  right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
                    printf("\n=  - (");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//�õ�Լ�ֵ�����
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld) )\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //��ӡ������
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
        }
    }
//��һ���Ǹ��������ڶ�����������
    else{
        if(compareFractions(*head,*right)){//head ���ڵ��� right ʱ
            answer.notation=='-';
            answer.i=minusIntegers(head->i,right->i);//�����������

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
                tail->n-=1;//��λ
                answer.i=sortInteger(answer.i);

                answer.denominator=right->denominator;
                answer.numerator=right->denominator-right->numerator;
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                //�ٴδ�ӡ������
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=head->denominator*right->denominator/CommonDivisor(head->denominator,right->denominator);
                if(answer.denominator/head->denominator!=right->denominator/CommonDivisor(head->denominator,right->denominator)){//������Խ��
                    answer.numerator=-1;
                    printf("   Exceeded!\n");
                    return;
                }

                if(head->numerator*right->denominator/CommonDivisor(head->denominator,right->denominator)-head->denominator*right->numerator/CommonDivisor(head->denominator,right->denominator)>=0){
                    answer.numerator=head->numerator*right->denominator/CommonDivisor(head->denominator,right->denominator)
                                     -head->denominator*right->numerator/CommonDivisor(head->denominator,right->denominator);
                    printf("\n   - (");
                    displayInteger(answer.i);
                    //��ӡͨ�ֹ���
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                    right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
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
                    tail->n-=1;//��λ
                    answer.i=sortInteger(answer.i);

                    answer.numerator=head->denominator*right->denominator+head->numerator*right->denominator-head->denominator*right->numerator;
                    //��ӡͨ�ֹ���
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld) )\n",answer.denominator,answer.denominator,
                                                                                                  head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
                    printf("\n=  - (");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//�õ�Լ������
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld) )\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //��ӡ������
                printf("\n=  - (");
                displayInteger(answer.i);
                printf(" + %lld / %lld)\n",answer.numerator,answer.denominator);
            }
        }
        else{
            answer.notation=='+';
            answer.i=minusIntegers(right->i,head->i);//�����������

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
                tail->n-=1;//��λ
                answer.i=sortInteger(answer.i);

                answer.denominator=head->denominator;
                answer.numerator=head->denominator-head->numerator;
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                //�ٴδ�ӡ������
                printf("\n      ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
            else{
                answer.denominator=right->denominator*head->denominator/CommonDivisor(head->denominator,right->denominator);
                if(answer.denominator/right->denominator!=head->denominator/CommonDivisor(head->denominator,right->denominator)){//������Խ��
                    answer.numerator=-1;
                    printf("   Exceeded!\n");
                    return;
                }

                if(right->numerator*head->denominator/CommonDivisor(head->denominator,right->denominator)-right->denominator*head->numerator/CommonDivisor(head->denominator,right->denominator)>=0){
                    answer.numerator=right->numerator*head->denominator/CommonDivisor(head->denominator,right->denominator)
                                     -right->denominator*head->numerator/CommonDivisor(head->denominator,right->denominator);
                    printf("\n      ");
                    displayInteger(answer.i);
                    //��ӡͨ�ֹ���
                    printf(" + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                  head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
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
                    tail->n-=1;//��λ
                    answer.i=sortInteger(answer.i);

                    answer.numerator=right->denominator*head->denominator+right->numerator*head->denominator-right->denominator*head->numerator;
                    //��ӡͨ�ֹ���
                    printf(" + (%lld/%lld) + (%lld*%lld)/(%lld*%lld)-(%lld*%lld)/(%lld*%lld)\n",answer.denominator,answer.denominator,
                                                                                                right->numerator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                right->denominator,head->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                head->numerator,right->denominator/CommonDivisor(head->denominator,right->denominator),
                                                                                                head->denominator,right->denominator/CommonDivisor(head->denominator,right->denominator));
                    //�ٴδ�ӡ������
                    printf("\n=     ");
                    displayInteger(answer.i);
                    printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
                }
            }

            while(CommonDivisor(answer.denominator,answer.numerator)!=1){
                long long int mid;
                mid=CommonDivisor(answer.numerator,answer.denominator);//�õ�Լ������
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + (%lld*%lld) / (%lld*%lld)\n",mid,answer.numerator/mid,mid,answer.denominator/mid);

                answer.denominator/=mid;
                answer.numerator/=mid;
                //��ӡ������
                printf("\n=     ");
                displayInteger(answer.i);
                printf(" + %lld / %lld\n",answer.numerator,answer.denominator);
            }
        }
    }
}

//����ԭ��:CommonDivisor
//��������:long long int ������:����long long int ���͵�����
//�õ�a ��b�����Լ��
long long int CommonDivisor(long long int a,long long int b)
{
    if(a*b==0)
    return (a ==0?b:a);
    if(a>b)
    return CommonDivisor(a%b,b);
    else if(a<b)
    return CommonDivisor(b%a,a);
}
