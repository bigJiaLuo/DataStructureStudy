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

/*
    括号匹配的检验
    str：字符串首地址，i：字符串长度
    思路：
        1.初始化一个栈，match：true，默认正确匹配
        2.遍历 字符串
            ·判断是否是（ 括号，是进栈，
            ·如果是 ）则取栈顶元素
                ·判断栈顶元素是否是  （ 括号
                    ·（ 括号则继续循环，math 为true
                    ·否则，match ：false
*/
bool match(char * str,int i){
    //初始化一个栈
    PSqStack stack;
    initStack(&stack);
    bool match = true;//默认匹配成功
    char ch = NULL;
    int j = 0;
    //遍历 括号字符串
    while(j < i && match){
        if (str[j] == '(')
        {
            //为 （ 括号 入栈
           push(&stack,str[j]);
        }
        else if (str[j] == ')')
        {
            //若是 ）
            if(getTopElem(stack,&ch) == true){
                //存在 栈顶元素
                if(ch != '(')
                    match = false;
                else
                    pop(&stack,&ch);
                    
            }else
            {
                match = false;
            }
            
        }
        j++;
    }
    if(!isEmpty(stack))
        match = false;//栈不空，false
    destroryStack(&stack);
    return match;
    
}
int main(void){

    char * str = "((12)";
    bool flag = match(str,6);
    printf("%d",flag);

    getchar();
    getchar();

    return 0;
}