#include <stdio.h>
#include <malloc.h>
#define MAXV 10       //最大顶点数
typedef int EdgeType; //边上权值类型

typedef int VertexType; //顶点类型

//边表类型
typedef struct EdgeNode
{
    VertexType tailvex;//弧尾 在顶点表的下标
    VertexType headvex;//弧头 在顶点表的下标
    struct EdgeNode * headLink;//入边表指针域，指向以headvex为弧头的下一条边
    struct EdgeNode * tailLink;//出边表指针域，指向以tailvex为弧尾的下一边边
} EdgeNode;

//顶点表类型
typedef struct VertexNode
{
    VertexType data;    //数据域，顶点信息
    EdgeNode * firstin;//入边 头指针
    EdgeNode * firstout;//出边，头指针
} VertexNode, TenList[MAXV];

//图的邻接表
typedef struct {
    TenList tenList;//十字链表
    int numVertex,numEdges;//图中顶点数，边数
}GraghTenList;

int main(void){

    getchar();
    getchar();
    return 0;
}
