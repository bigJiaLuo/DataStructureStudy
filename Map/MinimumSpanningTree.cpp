/*
    生成树和最小生成树
    时间：2020年6月22日16:23:31
    作者：泽兑ing
*/
#include <stdio.h>
#define MAXV 6        //最大顶点个数
#define MaxEdges 20 //最大边数
#define INFINITY 65535 //无穷大
typedef int InfoType;
typedef struct
{
    int no;        //顶点编号
    InfoType info; //顶点其他信息
} VertexType;      //顶点类型

typedef struct
{
    int edges[MAXV][MAXV];   //邻接矩阵的边数组
    int numVertex, numEdges; //顶点数和边数
    VertexType vexs[MAXV];   //顶点表
} MGraph;                    //完整的图邻接矩阵

/*
    创建邻接矩阵  无向网图
*/
void CreateMGraph(MGraph *G)
{
    int i, j, k, w;
    printf("输入顶点数，和边数：");
    scanf("%d %d", &G->numVertex, &G->numEdges);
    for (i = 0; i < G->numVertex; i++)
    {
        printf("输入顶点信息，第%d个:", i + 1);
        scanf("%d", &G->vexs[i].no); //写入顶点信息
    }

    for (i = 0; i < G->numVertex; i++)
    {
        for (int j = 0; j < G->numVertex; j++)
        {
            if (i == j)
            {
                G->edges[i][j] = 0;
                continue;
            }

            G->edges[i][j] = INFINITY; //初始化 邻接矩阵
        }
    }

    for (k = 0; k < G->numEdges; k++)
    {
        printf("输入边（vi,vj）上的下标i，j和权值：");
        scanf("%d %d %d", &i, &j, &w);
        G->edges[i][j] = w;
        G->edges[j][i] = w; //无向图，矩阵对称
    }
}

/*
    Prim普里姆算法
    adjvex[j] 为 lowcost[j]代表边 的起点，j为终点，lowcost[j] 为 权值    如：(adjvex[j],j) = lowcost[j]
    lowcost[j]为(adjvex[j],j)的权值
    lowcost[k] = 0,将已找出的最小权值的边的终点加入最小生成树
    思路： 
        1.初始化U={v}，以v到其他顶点的所有边为候选边
        2.重复一下步骤（n-1）次，使得其他（n-1）个顶点被加入到U中
            ·从候选边挑选权值最小的边加入lowcost[]，设该边在V-U中顶点是k，将k加入U中；
            ·考察当前V-U中所有顶点j，修改候选边，若边（k，j）的权值小于原来和顶点j关联的候选边，则用边（k，j）取代后者作为候选边
    时间复杂度（numVertex^2）
*/
void Prim(MGraph g, int v)
{
    int lowcost[MAXV], adjvex[MAXV]; //lowcost[j]为 存储依附j的边的权值，adjvex[i]表示对应的顶点
    int min, i, j, k;                //min为权值最小的值，k为 保存某顶点的邻接点
    for (i = 0; i < g.numVertex; i++)
    {
        lowcost[i] = g.edges[v][i]; //初始化，lowcost初值为 v，即v的邻接点的权值
        adjvex[i] = v;              //adjvex 默认都为v顶点
    }

    for (i = 1; i < g.numVertex; i++) //找出（n-1）个顶点
    {
        min = INFINITY; //初值为极大值
        for (j = 0; j < g.numVertex; j++)
        {
            if (lowcost[j] != 0 && lowcost[j] < min) //排除已经加入最小生成树中的顶点，且找出离U最近的顶点k
            {
                //min 赋上新的最小权值
                min = lowcost[j];
                k = j; //k记录最小权值的顶点位置
            }
        }
        printf("边（%d,%d）权为：%d\n", adjvex[k], k, min); //adjvex[k]开始顶点，k为终端顶点
        lowcost[k] = 0;                                     //将 k代表的顶点加入 最小生成树,
        for (j = 0; j < g.numVertex; j++)                   //更新k顶点到各边的权值数组lowcost，若k顶点到j的权值比 之前 顶点到j的权值 要小，则替换原来的lowcost[j]
        {
            //更新 lowcost，adjvex数组，因为 新加入k顶点
            if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j]) //当前边存在，且 当前边权值小于对应 之前顶点到j的权值，替换之
            {
                lowcost[j] = g.edges[k][j]; //（k，j） 的值替换（原先顶点，j）的值
                adjvex[j] = k;              //将开始顶点赋值
            }
        }
    }
}

typedef struct
{
    int u; //边的起点
    int v; //边的终点
    int w; //边的权值
} Edge;
/*
    直接插入排序
*/
void insertSort(Edge E[], int edges)
{
    Edge temp;
    for (int i = 0; i < edges; i++)
    {
        for (int j = i + 1; j < edges; j++)
        {
            if (E[i].w > E[j].w)
            {
                temp = E[i];
                E[i] = E[j];
                E[j] = temp;
            }
        }
    }
    printf("");
}
/*
    Kruskal算法（）
    辅助数组vset，用于判断两个顶点是否连通

    思路：
        1.初始化边集E，有图g产生
        2.对边集E进行升序排序
        3.循环，（生成的边k 不大于 图的顶点数）
            ·取出 边集中第j条边中的 头尾顶点
            ·将其顶点所在的辅助数组中的值取出
            ·判断 sn1和sn2是否相等，相等则连通，跳过
                ·不相等，生成边加1，打印边路径
            j++，边集加一
        4.直到while循环结束
*/
void Kruskal(MGraph g)
{
    int i, j, u1, v1, sn1, sn2, k;
    int vset[MAXV];
    Edge E[MaxEdges];                     //存放所有边
    k = 0;                            //E数组从0下标开始计
    for (i = 0; i < g.numVertex; i++) //由g产生的边集E
    {
        for (j = 0; j < g.numVertex; j++)
        {
            if (g.edges[i][j] != 0 && g.edges[i][j] != INFINITY)
            {
                E[k].u = i;
                E[k].v = j;
                E[k].w = g.edges[i][j];
                k++;
            }
        }
    }

    insertSort(E, g.numEdges);// 采用直接插入排序对E数组按权值排序
    for ( i = 0; i < g.numVertex; i++)//初始化 辅助数组
    {
        vset[i] = i;
    }
    k = 1;// k表示当前构造生成树的第几条边，初值为1
    j = 0;//E中边的下标
    while (k < g.numVertex)//生成树的边数小于顶点数循环
    {
        u1 = E[j].u; v1 = E[j].v;//取一条边的 头尾顶点
        sn1 = vset[u1];
        sn2 = vset[v1];
        if (sn1 != sn2)
        {
            printf("(%d, %d): %d\n",u1,v1,E[j].w);
            k++;//生成边数加1
            for ( i = 0; i < g.numVertex; i++)//两集合统一编号
            {
                if (vset[i] == sn2)//将sn2代表的vset[i] 改为 sn1
                {
                    vset[i] = sn1;
                }
                
            }
            
        }
        j++;//下一条边

    }
    
    
}

int main(void)
{
    MGraph G;
    int edges[MAXV][MAXV] = {{0, 6, 1, 5, INFINITY, INFINITY}, {6, 0, 5, INFINITY, 3, INFINITY}, {1, 5, 0, 5, 6, 4}, {5, INFINITY, 5, 0, INFINITY, 2}, {INFINITY, 3, 6, INFINITY, 0, 6}, {INFINITY, INFINITY, 4, 2, 6, 0}};
    G.numVertex = 6;
    G.numEdges = MaxEdges;
    for (int i = 0; i < G.numVertex; i++)
    {
        for (int j = 0; j < G.numVertex; j++)
        {
            G.edges[i][j] = edges[i][j];
        }
        G.vexs[i].no = i;
    }
    
    // CreateMGraph(&G);
    // Prim(G, 0);
    Kruskal(G);

    getchar();
    getchar();
    return 0;
}