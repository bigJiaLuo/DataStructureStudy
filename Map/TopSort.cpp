/*
    拓扑排序
    时间：2020年9月2日10:23:51
    作者：泽兑ing
*/

#include <stdio.h>
#include <malloc.h>
#define MAXV 10       //最大顶点数
typedef int EdgeType; //边上权值类型

typedef int VertexType; //顶点类型

//边表类型
typedef struct EdgeNode
{
    int adjvex;            //该邻接点域，存储该顶点的下标
    EdgeType weight;       //该存储顶点到该顶点边上的权值，非网图不需要
    struct EdgeNode *next; //链域，指向下一个顶点的邻接点
} EdgeNode;

//顶点表类型
typedef struct VertexNode
{
    VertexType data;    //数据域，顶点信息
    int inCount;//顶点的入度
    EdgeNode *firstedg; //边域，指向边表的头
} VertexNode, AdjList[MAXV];

//邻接表类型
typedef struct ALGragh
{
    AdjList adjList;//边表类型
    int vertex,edges;//顶点数，边数
}ALGragh;


void topSort(ALGragh * G){
    //1.栈St的指针为top
    int i,j;
    int St[MAXV],top = -1;
    EdgeNode * p;
    //2.入度置为0
    for ( i = 0; i < G->vertex; i++)
    {
        G->adjList[i].inCount = 0;
    }
    // 3.求所有顶点的入度
    for ( i = 0; i < G->vertex; i++)
    {
        p = G->adjList[i].firstedg;
        while(p != NULL){
            G->adjList[p->adjvex].inCount++;//p->adjvex为 i的入度
            p = p->next;//p指向下一个邻接点
        }
    }
    //4.入度为0的顶点进栈
    for ( i = 0; i < G->vertex; i++)
    {
        if(G->adjList[i].inCount == 0){
            top++;
            St[top] = i;
        }
    }

    //5.输出拓扑排序
    while(top > -1){
        i = St[top--];
        printf("%d ",i);
        p = G->adjList[i].firstedg;//找到顶点i的第一个邻接点
        //将i的所有的邻接点点入度减一
        while (p != NULL)
        {
            j = p->adjvex;
            G->adjList[j].inCount--;
            //如果减一后，入度为0，则入栈
            if (G->adjList[j].inCount == 0)
            {
                St[++top] = j;
            }
            p = p->next;
        }
        
    }
}

void CreateALGraph1(ALGragh *G)
{
    int i, j, k; //i为起点，j为终点
    EdgeNode *e; //临时保存新邻接点
    printf("请输入无向图的顶点个数，边数：");
    scanf("%d %d", &G->vertex, &G->edges);
    //初始化顶点表
    for (i = 0; i < G->vertex; i++)
    {

        printf("输入第%d个顶点编号:", i + 1);
        scanf("%d", &G->adjList[i].data);
        G->adjList[i].firstedg = NULL; //边表置为空
    }
    //创建边，建立边表
    for (k = 0; k < G->edges; k++)
    {
        printf("请输入（vi，vj）上顶点的序号：");
        scanf("%d %d", &i, &j);

        //头插法
        //建立新的邻接点，i为顶点，j为邻接点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j; //邻接序号为j
        e->next = G->adjList[i].firstedg;
        G->adjList[i].firstedg = e;
    }
}


int *etv,*ltv;//事件最早发生时间和最迟发生时间数组
int *stack2;//用于存储拓扑排序的栈
int top2;//用于stack2的栈顶指针
/*
    拓扑排序，用于关键路径计算
*/
bool TopologicalSort(ALGragh * G){
    EdgeNode * e;
    int i,k,gettop;
    int count;//计算已进行拓扑排序顶点的个数

    int top = 0;int count = 0;int * stack;//top用于栈顶
    stack = (int *)malloc(G->vertex * sizeof(int));
    //将所有入度为0的顶点入栈
    for ( i = 0; i < G->vertex; i++)
    {
        if(0 == G->adjList[i].inCount)
            stack[++top] = i;
    }
    top2 = 0;//初始化为0
    etv = (int *)malloc(G->vertex * sizeof(int));
    //初始化事件最早发生时间
    for ( i = 0; i < G->vertex; i++)
    {
        etv[i] = 0;
    }
    stack2 = (int *)malloc(G->vertex * sizeof(int));
    
    //将拓扑序列入栈，且求出对应的最早事件发生时间
    while (top != 0)
    {
        gettop = stack[top--];
        count++;
        stack2[++top2] = gettop;//将弹出的顶点序列压入拓扑序列的栈

        for ( e = G->adjList[gettop].firstedg; e; e = e->next)
        {
            k = e->adjvex;
            //e顶点的邻接点入度都减一，将出现入度为0的元素入栈
            if (0 == (--G->adjList[k].inCount))
                stack[++top] = k;
            //求出所有顶点最早发生时间，如有两条路径，则需要前后出栈两次比较出最大值，进行赋值
            if (etv[gettop]+e->weight > etv[k])
                etv[k] = etv[gettop]+e->weight;
        }
    }

    //拓扑序列中顶点个数不等于原顶点个数，存在回路
    if(count < G->vertex)
        return false;
    else
        return true;
}

/*
    求关键路径，G为有向网，输出G的各项关键活动
*/
void CriticalPath(ALGragh *G){
    EdgeNode * e;
    int i,gettop,k,j;
    int ete,lte;//声明活动最早发生和最迟发生时间变量
    TopologicalSort(G);//求出拓扑序列，计算数组etv和stack2的值
    ltv = (int *)malloc(G->vertex * sizeof(int));//事件最晚发生时间
    for ( i = 0; i < G->vertex; i++)
    {
        ltv[i] = etv[G->vertex-1];//初始化ltv
    }
    while (top2 != 0)//计算ltv
    {
        gettop = stack2[top2--];//将拓扑序列出栈，后进先出
        for ( e = G->adjList[gettop].firstedg; e; e = e->next)
        {
            //求个顶点事件最迟发生时间ltv
            k = e->adjvex;
            if (ltv[k]-e->weight < ltv[gettop])
            {
                ltv[gettop] = ltv[k]-e->weight;
            }
        }
        
        //求etv，lte和关键活动
        for ( i = 0; i < G->vertex; i++)
        {
            for (e = G->adjList[j].firstedg; e; e = e->next)
            {
                k = e->adjvex;
                ete = etv[j];//活动最早发生时间
                lte = ltv[k] - e->weight;//活动最晚发生时间
                if (ete == lte)
                {
                    printf("<v%d,v%d> length: %d,",G->adjList[j].data,G->adjList[k].data,e->weight);
                }
            }
            
        }
        

    }

}

int main(void){
    ALGragh G;
    CreateALGraph1(&G);
    topSort(&G);

    getchar();
    getchar();
    return 0;
}