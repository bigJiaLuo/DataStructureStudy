/*
    作者：洛
    时间：2020年5月30日16:28:12
    顺序栈

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
    ElemType data[MaxSize];//数据域
    int top;//栈顶指针
}SqStack,* PSqStack;
void initStack(PSqStack * stack);
void destroryStack(PSqStack * stack);
/*
    初始化一个空顺序栈
    空栈top指向 -1
*/
void initStack(PSqStack * stack){
    *stack = (PSqStack)malloc(sizeof(SqStack));
    (*stack)->top = -1;
}

/*
    销毁一个顺序栈
*/
void destroryStack(PSqStack * stack){
    free(*stack);
    *stack = NULL;
}

/*
    判断一个顺序栈是否为空
*/
Status isEmpty(PSqStack stack){
    if(stack->top <= -1)
        return TRUE;
    return FALSE;
}
/*
    判断一个顺序是否已满
*/
Status isFull(PSqStack stack){
    if(stack->top >= MaxSize-1)
        return TRUE;
    return FALSE;
}

/*
    进栈
    stack 为顺序栈，x为需要入栈的元素
    思路：
        1.先判断栈是否已满
        2.再进入栈操作
*/
Status push(PSqStack * stack,ElemType x){
    if(isFull(*stack)){
        //满了
        return ERROR;
    }
    //入栈
    int top = ++(*stack)->top;//先栈顶自增
    (*stack)->data[top] = x;//元素存入栈顶
    return OK;
}

/*
    出栈
    思路：
        1.判断是否已经到栈底
        2.返回出栈元素
        3.出栈
*/
Status pop(PSqStack * stack,ElemType * e){
    if(isEmpty(*stack))
        return ERROR;
    
    *e = (*stack)->data[(*stack)->top];
    (*stack)->top--;
    return OK;
}

/*
    取出栈顶元素
    e:返回栈顶元素
*/
Status getTopElem(PSqStack stack,ElemType * e){
    if(isEmpty(stack))
        return ERROR;
    *e = stack->data[stack->top];
    return OK;
}

/*
    遍历整个栈
*/
Status displayStack(SqStack stack){
    //不可以传递 指针变量过来，会修改指针变量所指top的值，传入非指针变量
    ElemType e = NULL;
    int top = stack.top;
    printf("遍历顺序栈：");
    while(!isEmpty(&stack)){
        getTopElem(&stack,&e);
        stack.top--;
        printf("%d\t",e);
    }
    printf("\n");
    // stack = NULL;
    return OK;
}

//顺序栈应用
/*
    判断一个字符串是否 是对称串
    思路：
        1.将串的每一个字符先入栈
        2.从栈顶每取一个元素就和 字符串的 i位进行比较，i自增
        3.不相同，则不是对称串
*/
Status symmetry(ElemType str[]){
    
    int i;
    ElemType e;
    PSqStack st;
    initStack(&st);//初始化栈
    for(i = 0; str[i] != '\0'; i++){
        push(&st,str[i]);//将str中的字符存入 栈中
    }
    //退栈元素，和字符比较
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
    //     printf("输入元素第%d：",i+1);
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
    //     printf("stack 为 NULL！");
    // destroryStack(&stack);
    ElemType * str = "abccba";
    if(symmetry(str))
        printf("是对称串\n");
    else
    {
            printf("不是对称串\n");
    }
    

    getchar();
    getchar();
    return 0;
}



