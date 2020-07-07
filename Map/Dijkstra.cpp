/*
    狄克斯拉特算法
    时间：2020年7月7日10:39:12
    作者：泽兑ing
*/

#include <stdio.h>
#define MAXV 7        //最大顶点个数
#define MaxEdges 12 //最大边数
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
void Dispath(MGraph g, int dist[],int path[],int S[],int v){
    //输出从顶点 v出发的所有最短路径
    int i,j,k;
    int apath[MAXV],d;//存放一条最短路径（逆向）及其顶点个数
    for ( i = 0; i < g.numVertex; i++)
    {
        if (S[i] == 1 && i != v)
        {
            printf("    从顶点%d到顶点%d路径长度为：%d\t路径为:",v,i,dist[i]);
            d = 0;
            apath[d] = i;//添加路径上的终点
            k = path[i];//k 保存 i 的前一个顶点编号
            if (k == -1)
            {
                printf("无路径\n");
            }else
            {
                while (k != v)
                {
                    d++;
                    apath[d] = k;
                    k = path[k];//k向前寻找前一个顶点

                }
                d++;
                apath[d] = v;//添加路径上的起点
                printf("%d",apath[d]);//先输出起点
                for ( j = d-1; j >= 0; j--)
                {
                    printf(",%d",apath[j]);
                }
                printf("\n");

            }
        }
        
    }
    
}


/*
    思想：
        迪克斯特拉的思想为：通过原点v 找到一个与之 最短路径的一个邻接点，再通 之前的邻接点找到下一个权值最小的邻接点，
        在此期间，每找到一个新的邻接点都要与U中其他顶点比较权值并修改（不包括以加入到S中的顶点），基于以求出的最短路径的基础上，进一步求v到u的其他顶点的最短路径

    步骤：
        ·初始化，S={v},U包含除v以外的其他顶点，v到U中顶点的距离边上的权
        ·从U中选取一个具有最小权值的顶点u，加其加入到S中（该选定的距离就是v到u的最短路径）
        ·以顶点u为新考虑的中间点，修改固定顶点v到U中个顶点的距离（ Cvj < Cvu+Wuj ）
        ·重复2,3步骤
*/
void Dijkstra(MGraph G,int v){
    int dist[MAXV],path[MAXV];//dist 当前原点v到顶点i的最短路径，path[i]存放当前最短路径中前一个顶点的编号
    int s[MAXV];//标记 顶点i是否已经加入S中，找到最短路径
    int mindis,i,j,u;//mindis  权值最小标记
    for ( i = 0; i < G.numVertex; i++)
    {
        dist[i] = G.edges[v][i];//距离初始化
        s[i] = 0;//s[] 置空
        if (G.edges[v][i] < INFINITY)
        {
            path[i] = v;//顶点v到顶点i有边时，置顶点i的前一个顶点为v
        }else
        {
            path[i] = -1;//不存在边，顶点i的前一个 顶点为 -1
        }
    }

    s[v] = 1;path[v] = 0;//将原点v加入S中并标记；path中 原点v的前一个顶点没有，故设为0
    for ( i = 0; i < G.numVertex; i++)
    {
        mindis = INFINITY; //权值最小 初值为 无穷
        for (j = 0; j < G.numVertex; j++)//选取不在S中的顶点且具有最小距离的顶点u
        {
            if (s[j] == 0 && dist[j] < mindis)
            {
                u = j;
                mindis = dist[j];
            }
        }
        s[u] = 1;//将选出的具有最小距离的顶点u 加入到 S中
        for ( j = 0; j < G.numVertex; j++)//修改不在S中的顶点距离
        {
            if (s[j] == 0)
            {
                if (G.edges[u][j] < INFINITY && dist[u] + G.edges[u][j] < dist[j])
                {
                    dist[j] = dist[u] + G.edges[u][j];
                    path[j] = u;
                }
                
            }
            
        }
    }
    Dispath(G,dist,path,s,v);//输出最短路径
    
}

int main(void){
    MGraph G;
    int edges[7][7] = {{0,4,6,6,INFINITY,INFINITY,INFINITY},{INFINITY,0,1,INFINITY,7,INFINITY,INFINITY},{INFINITY,INFINITY,0,INFINITY,6,4,INFINITY},{INFINITY,INFINITY,2,0,INFINITY,5,INFINITY},{INFINITY,INFINITY,INFINITY,INFINITY,0,INFINITY,6},{INFINITY,INFINITY,INFINITY,INFINITY,1,0,8},{INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,0}};
    G.numVertex = 7;
    G.numEdges = 12;
    for (int i = 0; i < G.numVertex; i++)
    {
        for (int j = 0; j < G.numVertex; j++)
        {
            G.edges[i][j] = edges[i][j];
        }
        
    }
    
    Dijkstra(G,0);    

    getchar();
    getchar();
    return 0;
}