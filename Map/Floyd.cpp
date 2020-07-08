/*
    弗洛伊德算法
    时间：2020年7月8日20:16:34
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

void Dispath(MGraph g,int A[][MAXV],int path[][MAXV]){
    int i,j;//循环迭代
    int k;//临时存放 前驱结点
    int apath[MAXV],d;//apath存放最短路径,d 为 apath角标
    for ( i = 0; i < g.numVertex; i++)
    {
        for ( j = 0; j < g.numVertex; j++)
        {
            if (A[i][j] < INFINITY && i != j)
            {
                printf("    从%d到%d的最短路径为：",i,j);
                k = path[i][j];//j的前驱顶点
                d = 0;
                apath[d] = j;//添加终点
                while (k != -1 && k != i)//路径上添加中间的
                {
                    d++;
                    apath[d] = k;
                    k = path[i][k];
                }
                d++;
                apath[d] = i;//添加起点
                printf("    %d",apath[d]);
                for (int s = d-1; s >= 0; s--)
                {
                    printf(",%d",apath[s]);
                }
                printf("  路径长度为：%d\n",A[i][j]);

            }
            
        }
        
    }
    
}

/*
    A[i][j]存放顶点i 到j的当前最短路径长度；
    path用于推到导所有顶点之间的最短路径，第i行表示 顶点i到其他顶点的最短路径，如path[i][j]存放顶点j的前驱顶点
    思想：
        初始化原邻接矩阵，每个顶点A[i][j]，都对 i，j 进行中间点k连接， A[i][j] = MIN{A[i][j] ,A[i][k]+A[k][j]},并修改对应的路径长度
        直到所有经过k顶点的所有路径都比较完毕，在处理完k顶点的基础上得到对应A，path，再处理 其他 经过顶点
        以此类推得到所有顶点对之间的最短路径长度与最短路径
*/
void Floyd(MGraph g){
    int A[MAXV][MAXV],path[MAXV][MAXV];
    int i,j,k;//k为中间点，i为边的开始结点，j为边的终端结点
    for ( i = 0; i < g.numVertex; i++)//初始化
    {
        for (j = 0; j < g.numVertex; j++)
        {
            A[i][j] = g.edges[i][j]; //默认为原邻接矩阵
            if (i != j && g.edges[i][j] < INFINITY)//<i,j>存在，且不是本身
            {
                path[i][j] = i;//保存j的前驱结点
            }else
            {
                path[i][j] = -1;//无边，本身 置为-1
            }
        }
    }

    for ( k = 0; k < g.numVertex; k++)
    {
        for ( i = 0; i < g.numVertex; i++)
        {
            for ( j = 0; j < g.numVertex; j++)//修改最短路径
            {
                if (A[i][j] > A[i][k] + A[k][j])//顶点i 到顶点j，大于 顶点i 借顶点k 再到顶点j时
                {
                    A[i][j] = A[i][k] + A[k][j];//<i,j>替换更小的路径长度
                    path[i][j] = path[k][j];//将<i,j>的最短路径的前驱改为 最后一个顶点的前驱（path[k][j]）
                }
                
            }
        }
        
    }
    Dispath(g,A,path);//输出最短路径
    

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
    Floyd(G);

    getchar();
    getchar();
    return 0;
}