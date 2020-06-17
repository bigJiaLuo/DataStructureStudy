/*
    邻接矩阵
    时间：2020年6月15日19:55:40
    作者：洛
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

bool visited[MAXV];//记录顶点是否被访问过
/*
    深度优先遍历
    思路：
        1.将此顶点置上标记，并输出
        2.对此顶点的邻接点 逐一使用 深度优先遍历
        3.一直递归，知道对此顶点的所有邻接点访问完毕
        4.当层递归后辉继续判断 顶点v是否还有未访问的邻接点，有则继续递归
    时间复杂度：O(n^2)
*/
void DFS(MGraph G,int v){
    visited[v] = 1;//置为已经访问
    printf("%d\t",G.vexs[v].no);//输出访问的顶点
    for (int i = 0; i < G.numVertex; i++)
    {
        if(!visited[v] && G.edges[v][i] == 1)//该顶点未被访问，且对于的边存在
        {
            DFS(G,i);
        }
    }
}
/*
    调用深度优先遍历
    思路：
        1.建立循环
            对图中G的每一个顶点调用深度优先遍历
*/
void DFSTravel(MGraph G){
    int i;
    for ( i = 0; i < G.numVertex; i++)
    {
        if(!visited[i])
            DFS(G,i);
    }
}

/*
    广度优先遍历
    其遍历方式 和 二叉树的 层次遍历类似
    思路：
        1.建立一个 队列
        2.对访问访问数组标识进行初始化
        3.访问该顶点，并标识已访问
        4.将该顶点入队
        5.对该顶点的所在一行进行遍历重复执行
            ·判断栈是否为空
                ·不空，出队
                ·判断该顶点是否已访问
                ·否，输出该顶点，并进队
        6.直到队列为空
*/
void BFS(MGraph G, int v)
{
    int queue[MAXV];
    int front = 0, rear = 0; //定义一个循环队列
    int w, i;
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0; //初始化数组
    }

    for (int j = 0; j < G.numVertex; j++)//对每一个顶点进行访问
    {
        if (!visited[j])
        {
            printf("%d\t", G.vexs[j]); //输出顶点
            visited[j] = 1;            //已访问
            rear = (rear + 1) % MAXV;
            queue[rear] = j; //将顶点入队

            while (rear != front)
            {
                front = (front + 1) % MAXV;
                w = queue[front];
                for (int i = 0; i < G.numVertex; i++)
                {
                    if (!visited[w] && G.edges[j][i] == 1)
                    {
                        printf("%d\t", G.vexs[i]);
                        visited[i] = 1;
                        rear = (rear + 1) % MAXV;
                        queue[rear] = i;
                    }
                }
            }
        }
    }
}

int main(void){

    MGraph G;
    CreateMGraph(&G);
    // DFSTravel(G);
    BFS(G,0);
    getchar();
    getchar();
    return 0;
}