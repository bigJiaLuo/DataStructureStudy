/*
    生成树和最小生成树
    时间：2020年6月22日16:23:31
    作者：泽兑ing
*/
#include <stdio.h>
#define MAXV 10//最大顶点个数
#define INFINITY 65535//无穷大
typedef int InfoType;
typedef struct{
    int no;//顶点编号
    InfoType info;//顶点其他信息
}VertexType;//顶点类型

typedef struct{
    int edges[MAXV][MAXV];//邻接矩阵的边数组
    int numVertex,numEdges;//顶点数和边数
    VertexType vexs[MAXV];//顶点表
}MGraph;//完整的图邻接矩阵



/*
    创建邻接矩阵  无向网图
*/
void CreateMGraph(MGraph * G){
    int i,j,k,w;
    printf("输入顶点数，和边数：");
    scanf("%d %d",&G->numVertex,&G->numEdges);
    for ( i = 0; i < G->numVertex; i++)
    {
        printf("输入顶点信息，第%d个:",i+1);
        scanf("%d",&G->vexs[i].no);//写入顶点信息
    }

    for ( i = 0; i < G->numVertex; i++)
    {
        for (int j = 0; j < G->numVertex; j++)
        {
            if (i == j)
            {
                G->edges[i][j] = 0;
                continue;
            }
            
            G->edges[i][j] = INFINITY;//初始化 邻接矩阵
        }
    }

    for ( k = 0; k < G->numEdges; k++)
    {
        printf("输入边（vi,vj）上的下标i，j和权值：");
        scanf("%d %d %d",&i,&j,&w);
        G->edges[i][j] = w;
        G->edges[j][i] = w;//无向图，矩阵对称
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
void Prim(MGraph g,int v){
    int lowcost[MAXV],adjvex[MAXV];//lowcost[j]为 存储依附j的边的权值，adjvex[i]表示对应的顶点
    int min,i,j,k;//min为权值最小的值，k为 保存某顶点的邻接点
    for ( i = 0; i < g.numVertex; i++)
    {
        lowcost[i] = g.edges[v][i];//初始化，lowcost初值为 v，即v的邻接点的权值
        adjvex[i] = v;//adjvex 默认都为v顶点
    }

    for ( i = 1; i < g.numVertex; i++)//找出（n-1）个顶点
    {
        min = INFINITY;//初值为极大值
        for ( j = 0; j < g.numVertex; j++)
        {
            if (lowcost[j] != 0 && lowcost[j] < min)    //排除已经加入最小生成树中的顶点，且找出离U最近的顶点k
            {
                //min 赋上新的最小权值
                min = lowcost[j];
                k = j;//k记录最小权值的顶点位置 
            }
        }
        printf("边（%d,%d）权为：%d\n",adjvex[k],k,min);//adjvex[k]开始顶点，k为终端顶点
        lowcost[k] = 0;//将 k代表的顶点加入 最小生成树,   
        for ( j = 0; j < g.numVertex; j++)//更新k顶点到各边的权值数组lowcost，若k顶点到j的权值比 之前 顶点到j的权值 要小，则替换原来的lowcost[j]
        {
            //更新 lowcost，adjvex数组，因为 新加入k顶点
            if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j])//当前边存在，且 当前边权值小于对应 之前顶点到j的权值，替换之
            {
                lowcost[j] = g.edges[k][j];//（k，j） 的值替换（原先顶点，j）的值
                adjvex[j] = k;  //将开始顶点赋值
            }
            
        }
    }
}

int main(void){
    MGraph G;
    CreateMGraph(&G);
    Prim(G,0);

    getchar();
    getchar();
    return 0;
}