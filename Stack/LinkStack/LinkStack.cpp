/* 
    作者：洛
    时间：2020年5月30日19:56:52
    链式 栈
*/

#include <stdio.h>
#include <malloc.h>

typedef int ElemType;
typedef struct linknode{
    ElemType data;//数据源
    struct linknode * next;//指针域
}LinkStack,* PLinkStack;

void initStack(PLinkStack * stack);
/*
    初始化 一个链栈
*/
void initStack(PLinkStack * stack){
    *stack = (PLinkStack)malloc(sizeof(LinkStack));
    (*stack)->next = NULL;
}

/*
    判断 一个堆栈是否为空
*/
bool isEmpty(PLinkStack stack){
    return (stack->next == NULL);
}
/*
    销毁一个链栈
    思路:
        1.将下一结点存入q
        2.循环释放每一个结点
        3.最后释放头结点
*/
void destroryStack(PLinkStack * stack){
    PLinkStack q = (*stack)->next,s = *stack;
    while(q != NULL){
        free(s);
        s = q;//保存下一结点
        q = q->next;//q指向下一结点
    }
    free(s);//释放头结点
    (*stack)->next =  NULL;
}


/*
    进栈
*/
bool push(PLinkStack * stack,ElemType e){
    PLinkStack s = (PLinkStack)malloc(sizeof(LinkStack));
    s->data = e;
    //进栈,将s插入到 头结点后，头插法
    s->next = (*stack)->next;
    (*stack)->next = s;
    return true;
}

/*
    出栈
*/
bool pop(PLinkStack * stack,ElemType * e){
    if(isEmpty(*stack))
        return false;
        //指向第一个结点
    PLinkStack p = (*stack)->next;
    *e = p->data;
    //头结点指向p的下一节点
    (*stack)->next = p->next;
    free(p);
    p = NULL;
    return true;
}

/*
    取栈顶元素
*/
bool getTopElem(PLinkStack stack,ElemType * e){
    if(isEmpty(stack))
        return false;
    *e = stack->next->data;
    return true;
}

/*
    由于 p知识用来存储 stack的下一节点，并没有又 该  p->next域中数据
*/
void displayStack(PLinkStack stack){
    PLinkStack p = stack->next;//指向栈顶元素
    printf("链栈遍历：");
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
        printf("第%d个：",i+1);
        scanf("%d",&e);
        push(&stack,e);
    }
    displayStack(stack);
    destroryStack(&stack);
    displayStack(stack);

    getchar();
    getchar();
}