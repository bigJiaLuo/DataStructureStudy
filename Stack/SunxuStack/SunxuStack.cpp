/*
    ���ߣ���
    ʱ�䣺2020��5��30��16:28:12
    ˳��ջ

*/

#include <stdio.h>
#include <malloc.h>
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define MaxSize 10

typedef char ElemType;
typedef int Status;
typedef struct SequenceStack
{
    /* data */
    ElemType data[MaxSize];//������
    int top;//ջ��ָ��
}SqStack,* PSqStack;
void initStack(PSqStack * stack);
void destroryStack(PSqStack * stack);
/*
    ��ʼ��һ����˳��ջ
    ��ջtopָ�� -1
*/
void initStack(PSqStack * stack){
    *stack = (PSqStack)malloc(sizeof(SqStack));
    (*stack)->top = -1;
}

/*
    ����һ��˳��ջ
*/
void destroryStack(PSqStack * stack){
    free(*stack);
    *stack = NULL;
}

/*
    �ж�һ��˳��ջ�Ƿ�Ϊ��
*/
Status isEmpty(PSqStack stack){
    if(stack->top <= -1)
        return TRUE;
    return FALSE;
}
/*
    �ж�һ��˳���Ƿ�����
*/
Status isFull(PSqStack stack){
    if(stack->top >= MaxSize-1)
        return TRUE;
    return FALSE;
}

/*
    ��ջ
    stack Ϊ˳��ջ��xΪ��Ҫ��ջ��Ԫ��
    ˼·��
        1.���ж�ջ�Ƿ�����
        2.�ٽ���ջ����
*/
Status push(PSqStack * stack,ElemType x){
    if(isFull(*stack)){
        //����
        return ERROR;
    }
    //��ջ
    int top = ++(*stack)->top;//��ջ������
    (*stack)->data[top] = x;//Ԫ�ش���ջ��
    return OK;
}

/*
    ��ջ
    ˼·��
        1.�ж��Ƿ��Ѿ���ջ��
        2.���س�ջԪ��
        3.��ջ
*/
Status pop(PSqStack * stack,ElemType * e){
    if(isEmpty(*stack))
        return ERROR;
    
    *e = (*stack)->data[(*stack)->top];
    (*stack)->top--;
    return OK;
}

/*
    ȡ��ջ��Ԫ��
    e:����ջ��Ԫ��
*/
Status getTopElem(PSqStack stack,ElemType * e){
    if(isEmpty(stack))
        return ERROR;
    *e = stack->data[stack->top];
    return OK;
}

/*
    ��������ջ
*/
Status displayStack(SqStack stack){
    //�����Դ��� ָ��������������޸�ָ�������ָtop��ֵ�������ָ�����
    ElemType e = NULL;
    int top = stack.top;
    printf("����˳��ջ��");
    while(!isEmpty(&stack)){
        getTopElem(&stack,&e);
        stack.top--;
        printf("%d\t",e);
    }
    printf("\n");
    // stack = NULL;
    return OK;
}

//˳��ջӦ��
/*
    �ж�һ���ַ����Ƿ� �ǶԳƴ�
    ˼·��
        1.������ÿһ���ַ�����ջ
        2.��ջ��ÿȡһ��Ԫ�ؾͺ� �ַ����� iλ���бȽϣ�i����
        3.����ͬ�����ǶԳƴ�
*/
Status symmetry(ElemType str[]){
    
    int i;
    ElemType e;
    PSqStack st;
    initStack(&st);//��ʼ��ջ
    for(i = 0; str[i] != '\0'; i++){
        push(&st,str[i]);//��str�е��ַ����� ջ��
    }
    //��ջԪ�أ����ַ��Ƚ�
    for(i = 0; str[i] != '\0'; i++){
        pop(&st,&e);
        if(str[i] != e){
            destroryStack(&st);
            return FALSE;
        }
    }
    destroryStack(&st);
    return TRUE;
}


int main(void){
    // PSqStack stack = NULL;
    // initStack(&stack);
    // ElemType e = NULL;
    // for(int i = 0; i < 10; i++){
    //     printf("����Ԫ�ص�%d��",i+1);
    //     scanf("%d",&e);
    //     push(&stack,e);
    // }
    // displayStack(*stack);
    // // push(&stack,11);
    // for(int j =0; j < 10; j++){
    //     pop(&stack,&e);
    // }
    // displayStack(*stack);
    // if(stack == NULL)
    //     printf("stack Ϊ NULL��");
    // destroryStack(&stack);
    ElemType * str = "abccba";
    if(symmetry(str))
        printf("�ǶԳƴ�\n");
    else
    {
            printf("���ǶԳƴ�\n");
    }
    

    getchar();
    getchar();
    return 0;
}



