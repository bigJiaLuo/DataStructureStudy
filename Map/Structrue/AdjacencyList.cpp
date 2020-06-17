/*
    邻接表
    时间：2020年6月15日20:35:21
    作者：洛
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
    EdgeNode *firstedg; //边域，指向边表的头
} VertexNode, AdjList[MAXV];

//图的邻接表
typedef struct
{
    AdjList adjList;         //邻接表
    int numVertex, numEdges; //图中顶点数，边数
} GraphAdjList;

/*
    使用邻接表 创建一个无向图，不带权
*/
void CreateALGraph(GraphAdjList *G)
{
    int i, j, k; //i为起点，j为终点
    EdgeNode *e; //临时保存新邻接点
    printf("请输入无向图的顶点个数，边数：");
    scanf("%d %d", &G->numVertex, &G->numEdges);
    //初始化顶点表
    for (i = 0; i < G->numVertex; i++)
    {

        printf("输入第%d个顶点编号:", i + 1);
        scanf("%d", &G->adjList[i].data);
        G->adjList[i].firstedg = NULL; //边表置为空
    }
    //创建边，建立边表
    for (k = 0; k < G->numEdges; k++)
    {
        printf("请输入（vi，vj）上顶点的序号：");
        scanf("%d %d", &i, &j);

        //头插法
        //建立新的邻接点，i为顶点，j为邻接点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j; //邻接序号为j
        e->next = G->adjList[i].firstedg;
        G->adjList[i].firstedg = e;

        //建立新得邻接点，j为顶点，i为邻接点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->next = G->adjList[j].firstedg;
        G->adjList[j].firstedg = e;
    }
}

bool visited[MAXV];//标识此顶点是否被访问
/*
    邻接表的深度优先遍历
    思路：
        1.将顶点v输出，并将visited[v]置为已访问
        2.遍历 图中顶点表中边表的第一个邻接点
        3.判断该邻接点是否已访问
        4.对该邻接点使用DFS，形成递归
        5.当层递归后辉继续判断 顶点v是否还有未访问的邻接点，有则继续递归
      时间复杂度：O(n+e) 顶点，边数
*/
void DFS(GraphAdjList G,int v){
    EdgeNode * p;//迭代边表
    visited[v] = 1;//置为已访问
    printf("%d\t",G.adjList[v].data);//输出当前顶点
    p = G.adjList[v].firstedg;//p指向 v顶点的第一个邻接点
    while (p)
    {
        if(!visited[p->adjvex])//判断该邻接点是否被访问
            DFS(G,p->adjvex);//对此邻接点 调用DFS
        p = p->next;//p指向 顶点v的下一个邻接点
    }
    
}

/*
    邻接表的广度优先遍历
    思路：
        1.建立循环队列
        2.对数组进行初始化
        3.访问初始顶点，并入队，并置为已访问
        4.栈不空
            ·出队，顶点赋值为=给w
            ·p指向w顶点的第一个邻接点链
            ·循环（p）
                ·判断 p邻接点是否被访问，因循环（p）就对p是否存在进行判断，故无需判断
                    ·true，输出邻接点，入队，置为已访问
                ·p迭代
*/
void BFS(GraphAdjList G,int v){
    //1
    EdgeNode * p;
    int queue[MAXV],rear = 0,front = 0;
    int w,i;
    //2
    for ( i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    //3
    printf("%2d",G.adjList[v].data);
    visited[v] = 1;
    rear = (rear+1) % MAXV;
    queue[rear] = v;
    //4
    while (rear != front)
    {
        //出队
        front = (front+1) % MAXV;
        w = queue[front];
        //指向栈顶，顶点的第一个邻接点
        p = G.adjList[w].firstedg;
        while (p)
        {
            if (!visited[p->adjvex])//该顶点是否已访问
            {
                //输出，入队，置为已访问
                printf("%2d",p->adjvex);
                visited[p->adjvex] = 1;
                rear = (rear+1) % MAXV;
                queue[rear] = p->adjvex;
            }
            p = p->next;//p指向栈顶，顶点的下一个邻接点
        }
        
    }
    
    

}

int main(void)
{

    GraphAdjList G;
    CreateALGraph(&G);
    // DFS(G,0);
    BFS(G,0);
    getchar();
    getchar();
    return 0;
}