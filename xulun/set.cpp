
// �Զ���Set����
// 13.����һ�����ϵĳ�����������ASet����������Ԫ��Ϊ�����������ϵĻ������������
// ��1������������a[0..n-1]����һ�����ϡ�
// ��2�����һ�����ϵ�����Ԫ�ء�
// ��3���ж�һ��Ԫ���Ƿ���һ�������С�
// ��4�����������ϵĲ�����
// ��5�����������ϵĲ��
// ��6�����������ϵĽ�����
// �ڴ˻�������Ƽ��ϵ�˳��洢�ṹ����ʵ�ָ�����������㷨��
// �𣺳�����������ASet���������£�
// ADT ASet
// {���ݶ���D={d��l0��isn��nΪһ��������}
// ���ݹ�ϵ���ޡ�
// �������㣺
// createset��&s��a��n��������һ������s��
// dispset��s�����������s��
// inset��s��e�����ж�Ԫ��e�Ƿ��ڼ���s�С�
//�󼯺ϵĲ���
// void add��sl��s2��s3����s3=slUs2��
// �󼯺ϵĲ
// void sub��s1��s2��s3����s3=sl-s2��
//�󼯺ϵĽ���
// void intersection��s1��s2��s3����s3=slls2��
// }
#include <stdio.h>
#define MaxSize 10

// Set���ϵĴ洢�ṹ
typedef struct Set
{
    int data[MaxSize];//Set�����е�����
    int length = 0;//Set���ϵ�ʵ�ʳ���
}Set,* pSet;

/*
    s Ϊ Set���ϵ�ָ�������a Ϊ ��Ҫ��������飬nΪ����ĳ���
*/
void createSet(Set * s,int a[],int n){
    if(a != NULL){
        for(int i = 0; i < n; i++){
            s->data[i] = a[i];
        }
        s->length = n;
    }
}

/*
    ��� Set����
*/
void dispSet(Set s){
    for(int i = 0; i < s.length; i++){
        printf("%d\t",s.data[i]);
    }
    printf("���ϳ���Ϊ��%d\t",s.length);
}

/*
    �ж� Set�������Ƿ����e ���Ԫ�أ�������ھ� ����true
*/
bool inSet(Set s,int e){
    for(int i = 0; i < s.length; i++){
        if(s.data[i] == e){
            return true;
        }
    }
    return false;
}

/*
    ���������ϵĲ��������� ���������򲢵��¼���
*/

Set add(Set s1,Set s2,Set s3){
    // 1.��������s1��s2����������Ԫ��׷�ӵ�s3������
    s3.length = 0;
    for (int i = 0; i < s1.length; i++)
    {
        /* code */
        s3.data[i] = s1.data[i];
        s3.length++;
    }
    for(int j = 0; j < s2.length; j++){
        s3.data[s3.length] = s2.data[j];
        s3.length++;
    }

    return s3;
}

/*
    ���������ϵĲ s3�������������ϵĲ�.s3
    s1,������ s2�е�Ԫ�أ���Ϊ�� 
*/
Set sub(Set s1,Set s2,Set s3){
    // 1.����s1  ����
      s3.length = 0;
    for(int i = 0; i < s1.length; i++){
        // 2.�ų� s1����s2 ��ͬ��Ԫ��,����inSet�������ж��Ƿ����
        if(!inSet(s2,s1.data[i])){
            // ��s2�в�����
            s3.data[s3.length] = s1.data[i];
            s3.length++;
        }
    }

    return s3;
}

/*
    �������ϵ� ������s3���������Ϲ��е�����
*/
Set intersection(Set s1,Set s2,Set s3){
    s3.length = 0;
    // 1.���� s1
    for(int i = 0; i < s1.length; i++){
        // 2.�ж� s1�е�Ԫ���Ƿ���s2�д���
        if(inSet(s2,s1.data[i])){
            s3.data[s3.length] = s1.data[i];
            s3.length++;
        }
    }

    return s3;
}






int main(void){
    int a[] = {1,2,3};
    int b[] = {3,4,5};
    Set set1,set2,set3;
    createSet(&set1,a,3);
    createSet(&set2,b,3);
    // set3 = add(set1,set2,set3);
    // set3 = sub(set1,set2,set3);
    set3 = intersection(set1,set2,set3);
    dispSet(set3);
    // bool flag = inSet(set1,2);
    // printf("%d",flag);

    getchar();
    return 0;
}

