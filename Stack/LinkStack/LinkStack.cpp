/* 
    ���ߣ���
    ʱ�䣺2020��5��30��19:56:52
    ��ʽ ջ
*/

#include <stdio.h>
#include <malloc.h>

typedef int ElemType;
typedef struct linknode{
    ElemType data;//����Դ
    struct linknode * next;//ָ����
}LinkStack,* PLinkStack;

void initStack(PLinkStack * stack);
/*
    ��ʼ�� һ����ջ
*/
void initStack(PLinkStack * stack){
    *stack = (PLinkStack)malloc(sizeof(LinkStack));
    (*stack)->next = NULL;
}

/*
    �ж� һ����ջ�Ƿ�Ϊ��
*/
bool isEmpty(PLinkStack stack){
    return (stack->next == NULL);
}
/*
    ����һ����ջ
    ˼·:
        1.����һ������q
        2.ѭ���ͷ�ÿһ�����
        3.����ͷ�ͷ���
*/
void destroryStack(PLinkStack * stack){
    PLinkStack q = (*stack)->next,s = *stack;
    while(q != NULL){
        free(s);
        s = q;//������һ���
        q = q->next;//qָ����һ���
    }
    free(s);//�ͷ�ͷ���
    (*stack)->next =  NULL;
}


/*
    ��ջ
*/
bool push(PLinkStack * stack,ElemType e){
    PLinkStack s = (PLinkStack)malloc(sizeof(LinkStack));
    s->data = e;
    //��ջ,��s���뵽 ͷ����ͷ�巨
    s->next = (*stack)->next;
    (*stack)->next = s;
    return true;
}

/*
    ��ջ
*/
bool pop(PLinkStack * stack,ElemType * e){
    if(isEmpty(*stack))
        return false;
        //ָ���һ�����
    PLinkStack p = (*stack)->next;
    *e = p->data;
    //ͷ���ָ��p����һ�ڵ�
    (*stack)->next = p->next;
    free(p);
    p = NULL;
    return true;
}

/*
    ȡջ��Ԫ��
*/
bool getTopElem(PLinkStack stack,ElemType * e){
    if(isEmpty(stack))
        return false;
    *e = stack->next->data;
    return true;
}

/*
    ���� p֪ʶ�����洢 stack����һ�ڵ㣬��û���� ��  p->next��������
*/
void displayStack(PLinkStack stack){
    PLinkStack p = stack->next;//ָ��ջ��Ԫ��
    printf("��ջ������");
    while(p != NULL){
        printf("%d\t",p->data);
        p = p->next;
    }
}

int main(void){
    PLinkStack stack;
    initStack(&stack);
    ElemType e;
    for(int i = 0; i < 5; i++){
        printf("��%d����",i+1);
        scanf("%d",&e);
        push(&stack,e);
    }
    displayStack(stack);
    destroryStack(&stack);
    displayStack(stack);

    getchar();
    getchar();
}