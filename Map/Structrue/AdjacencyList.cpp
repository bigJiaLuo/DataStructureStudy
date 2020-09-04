/*
    邻接表
    时间：2020年6月15日20:35:21
    复习：2020年8月27日14:35:12
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
 q
void CreateALGraph1(GraphAdjList *G)
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
    }
}

bool visited[MAXV]; //标识此顶点是否被访问
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
void DFS(GraphAdjList G, int v)
{
    EdgeNode *p;                       //迭代边表
    visited[v] = 1;                    //置为已访问
    printf("%d\t", G.adjList[v].data); //输出当前顶点
    p = G.adjList[v].firstedg;         //p指向 v顶点的第一个邻接点
    while (p)
    {
        if (!visited[p->adjvex]) //判断该邻接点是否被访问
            DFS(G, p->adjvex);   //对此邻接点 调用DFS
        p = p->next;             //p指向 顶点v的下一个邻接点
    }
}

/*
    邻接表的广度优先遍历，类似树的层次遍历，需要借助一个队列
    思路：
        1.建立循环队列
        2.对visited数组进行初始化
        3.访问初始顶点，并入队，并置为已访问
        4.队列不空循环
            ·出队，顶点赋值给w
            ·p指向w顶点的第一个邻接点链
            ·循环（p）
                ·判断 p的每一个邻接点是否被访问；   注：因循环（p）就对p是否存在进行判断，故无需判断
                    ·true，输出邻接点，入队，置为已访问
                ·p迭代
*/
void BFS(GraphAdjList G, int v)
{
    //1
    EdgeNode *p;
    int queue[MAXV], rear = 0, front = 0;
    int w, i;
    //2
    for (i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    //3
    printf("%2d", G.adjList[v].data);
    visited[v] = 1;
    rear = (rear + 1) % MAXV;
    queue[rear] = v;
    //4
    while (rear != front)
    {
        //出队
        front = (front + 1) % MAXV;
        w = queue[front];
        //p指向顶点w的第一个邻接点
        p = G.adjList[w].firstedg;
        while (p)
        {
            if (!visited[p->adjvex]) //该顶点是否已访问
            {
                //输出，入队，置为已访问
                printf("%2d", p->adjvex);
                visited[p->adjvex] = 1;
                rear = (rear + 1) % MAXV;
                queue[rear] = p->adjvex;
            }
            p = p->next; //p指向顶点的下一个邻接点
        }
    }
}

//应用
/*
    判断图G是否为连通图
    思路：
        0.初始化visited
        1.对该图进行一次深度遍历
        2.再对该图的所有顶点判断，visited是否都为1
            ·1，连通
            ·0，不连通
*/
bool connect(GraphAdjList G)
{
    bool flag = true;
    //1
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }

    //2
    DFS(G, 0);
    for (int i = 0; i < G.numVertex; i++)
    {
        //是否都已访问
        if (visited[i] != 1)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
/*
    邻接表，判断 顶点u 到顶点 v是否存在简单路径
    思路：
        1.在深度遍历的基础上加上 u，和v两个参数
        2.判断u == v ，返回 has 作为是否存在简单路径标识
*/
void ExistPath(GraphAdjList G, int u, int v, bool *has)
{
    EdgeNode *p; //迭代邻接点
    //不可对visited数组初始化,导致visited都为0，因为是递归方法
    visited[u] = 1; //置为已访问
    if (u == v)     //说明从开始u顶点，一直沿着路径访问到v，存在着一条路径
    {
        *has = true;
        return;
    }

    p = G.adjList[u].firstedg; //p指向顶点u的第一个邻接点

    while (p) //遍历p的每一个邻接点
    {
        if (!visited[p->adjvex])
        {
            ExistPath(G, p->adjvex, v, has);
        }
        p = p->next;//指向下一个邻接点
    }
}

/*
    邻接表,输出图G中 所有从顶点u到顶点v的一条简单路径
    思路:
        1.利用图的深度优先遍历,附加三个形参,v,path,d； 每一层递归中的path中存放的路径元素都不同
            ·其中v代表终点v，path 存放u到v所经过的邻接点，d表示path的大小，初值为-1
            ·遍历过程中，将当前顶点，加入path[]
            ·满足u == v的终止条件，说明从u 到 v找到了一条简单路径，输出path
            ·再从顶点u找一个未访问的顶点w，
                ·若存在这样的顶点，这从w出发继续进行
                ·若不存在这样的w，说明该顶点u再往下找不到路径，所以置visited[u] = 0，以便顶点u作为其他路径上的顶点，称为恢复环境
        最后visited[]都归0，退栈过程中u往下无路径
*/
void FindPath(GraphAdjList G, int u, int v, int path[], int d)
{
    int w, i;
    EdgeNode *p;
    visited[u] = 1;//置为已访问u
    d++; //路径长度+1,u加入路径
    path[d] = u;
    if (u == v) //找到一条路径
    {
        printf("这是一条简单路径：");
        for (int i = 0; i <= d; i++)
        {
            printf("%2d", path[i]);
        }
        printf("\n");
    }

    p = G.adjList[u].firstedg; //p指向u的第一个邻接点
    while (p)
    {
        if (!visited[p->adjvex])
        {
            FindPath(G, p->adjvex, v, path, d);
        }
        p = p->next;//下一邻接点
    }
    visited[u] = 0; //恢复环境，说明顶点u往下找不到路径，让u重新恢复未访问状态，使其可以重新使用
}

/*
    输出图G中从顶点u到v的长度为1的所有简单路径   每一层递归中的path中存放的路径元素都不同
    思路：  和输出所有简单路径类似，将输出路径条件改为d == 1 && u == v即可
        1.
*/
void PathAll(GraphAdjList G, int u, int v, int path[], int d)
{
    //d表示path中的路径长度，初始为-1
    int w, i;
    EdgeNode *p;
    visited[u] = 1;
    d++;
    path[d] = u; //路径长度增1，顶点u加入路径
    if (u == v && d == 1)
    {
        for (int i = 0; i <= d; i++)
        {
            printf("%2d", path[i]);
        }
        printf("\n");
    }
    p = G.adjList[u].firstedg; //p指向u的第一个邻接点
    while (p)
    {
        w = p->adjvex; //w为u的邻接点
        if (!visited[w])
        {
            PathAll(G, w, v, path, d);
        }
        p = p->next; //p指向下一个邻接点
    }
    visited[u] = 0; //恢复环境，使u顶点可再次使用
}

/*
    邻接表，求图中 通过某顶点k的所有简单回路（若存在）。简单回路，指路径上的顶点不重复，但第一个和最后一个相同的路径
    其中v代表终点v，path 存放u到v所经过的邻接点，d表示path的大小，初值为-1
    思路：
        1.利用回溯的深度优先遍历
        2.从顶点u开始搜索与之相邻的w，若w等于顶点v其初值为（u）且路径长度大于0，表示找到一条回路，输出path数组
        3.继续搜索顶点u未访问的相邻点查找其他回路
*/
void DFSPath(GraphAdjList G, int u, int v, int path[], int d)
{
    int w, i;
    EdgeNode *p;
    d++;
    visited[u] = 1;
    path[d] = u;               //将u访问，且加入路径
    p = G.adjList[u].firstedg; //p指向顶点u的第一个相邻点

    while (p)
    {
        w = p->adjvex; //w为u 的相邻点

        if (w == v && d > 0) //找到一条回路，最少包含两个顶点
        {
            for (int i = 0; i <= d; i++)
            {
                printf("%2d", path[i]);
            }
            printf("%d\n",v);
        }
        if (!visited[w])
        {
            DFSPath(G, w, v, path, d);
        }
        p = p->next;
    }
    visited[u] = 0;
}
void FindCyclePath(GraphAdjList G, int k)
{
    int path[MAXV];
    printf("经过顶点%d的所有回路：\n");
    DFSPath(G, k, k, path, -1);
}



//广度优先遍历的应用
typedef struct
{
    int data;   //顶点信息
    int parent; //顶点前驱在队列中的下标
} QUEUE;

/* 
    邻接表，求不带权无向连通图G中从顶点u到顶点v的一条最短路径
    思路：
        1.利用广度优先遍历,一层一层，逐步扩散范围特性，当首次u == v时，对列中的元素即为最短路径
        2.采用非环形队列，出队时也可保留之前队首元素，便获取队列中每个顶点的前驱
*/
void ShortPath(GraphAdjList G, int u, int v)
{
    EdgeNode *p;
    int w, i;
    QUEUE qu[MAXV];
    int front = -1, rear = -1; //初始化非环形队列
    int visited[MAXV];         //标识数组
    for (i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    //入队，parent域指向其前驱
    rear++;
    qu[rear].data = u;
    qu[rear].parent = -1;
    //队列不空
    while (rear != front)
    {
        //队首顶点出队
        w = qu[++front].data;

        if (w == v) //当 顶点w 与 v首次相等，即最短路径
        {
            i = front;//i指向最短路径的最后一个顶点
            while (qu[i].parent != -1) //只要parent域不为顶点u
            {
                printf("%2d", qu[i].data);
                i = qu[i].parent;
            }
            printf("%2d\n", qu[i].data); //输出顶点u
            break;//退出整个循环
        }

        //p指向 w的 首个邻接点
        p = G.adjList[w].firstedg;
        //将顶点w的邻接点全部入队
        while (p)
        {
            if (visited[p->adjvex] == 0)
            {   //入队，parent域指向p顶点的前驱
                qu[++rear].data = p->adjvex;
                qu[rear].parent = front; //front 为顶点w在队列中的下标
            }
            p = p->next;//p指向 顶点w的下一个邻接点
        }
    }
}

/*
    邻接表，求不带权无向图中距离顶点v的最远的一个顶点
        其实就是求，距顶点v的边数最多的顶点
        广度优先遍历，队列中的最后一个顶点即为最远
        应不用输出路径，可采用循环队列
    思路：
        1.广度优先遍历，一层一层的思想，每一层都代表一条边，最底下一层的最后一个顶点为最远顶点
*/
int Maxdist(GraphAdjList G,int v){
    EdgeNode * p;
    int Qu[MAXV],rear = 0,front = 0;//初始化队列
    int j,k;//j临时队首顶点，k为 最远顶点
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;//初始化 标识数组
    }
    //标识，入队
    visited[v] = 1;
    rear = (rear+1) % MAXV;
    Qu[rear] = v;

    //队列不空
    while (rear != front)
    {
        front = (front + 1) % MAXV;
        k = Qu[front];//将队首赋给k，直到将最后一个队首赋给k

        p = G.adjList[k].firstedg;//p指向 k顶点的第一个邻接点
        //遍历p,将k的所有邻接点入队
        while (p && visited[p->adjvex] == 0 )
        {
            //入队，标识
            rear = (rear+1) % MAXV;
            Qu[rear] = p->adjvex;
            visited[p->adjvex] = 1;
            p = p->next;
        }
    }
    return k;
    
}


int main(void)
{

    GraphAdjList G;
    CreateALGraph1(&G);
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0;
    }
    
    // DFS(G,0);
    // BFS(G,0);
    // bool flag = connect(G);
    bool exist = false;
    VertexType path[MAXV];
    int d = -1;
    // ExistPath(G,0,3,&exist);
    // FindPath(G,0,3,path,d);
    // PathAll(G,0,3,path,d);
    FindCyclePath(G, 0);
    // int max = Maxdist(G,0);
    getchar();
    getchar();
    return 0;
}