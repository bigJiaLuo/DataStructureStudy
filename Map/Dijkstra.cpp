/*
    �ҿ�˹�����㷨
    ʱ�䣺2020��7��7��10:39:12
    ���ߣ����ing
*/

#include <stdio.h>
#define MAXV 7        //��󶥵����
#define MaxEdges 12 //������
#define INFINITY 65535 //�����
typedef int InfoType;
typedef struct
{
    int no;        //������
    InfoType info; //����������Ϣ
} VertexType;      //��������

typedef struct
{
    int edges[MAXV][MAXV];   //�ڽӾ���ı�����
    int numVertex, numEdges; //�������ͱ���
    VertexType vexs[MAXV];   //�����
} MGraph;                    //������ͼ�ڽӾ���

/*
    �����ڽӾ���  ������ͼ
*/
void CreateMGraph(MGraph *G)
{
    int i, j, k, w;
    printf("���붥�������ͱ�����");
    scanf("%d %d", &G->numVertex, &G->numEdges);
    for (i = 0; i < G->numVertex; i++)
    {
        printf("���붥����Ϣ����%d��:", i + 1);
        scanf("%d", &G->vexs[i].no); //д�붥����Ϣ
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

            G->edges[i][j] = INFINITY; //��ʼ�� �ڽӾ���
        }
    }

    for (k = 0; k < G->numEdges; k++)
    {
        printf("����ߣ�vi,vj���ϵ��±�i��j��Ȩֵ��");
        scanf("%d %d %d", &i, &j, &w);
        G->edges[i][j] = w;
        G->edges[j][i] = w; //����ͼ������Գ�
    }
}
void Dispath(MGraph g, int dist[],int path[],int S[],int v){
    //����Ӷ��� v�������������·��
    int i,j,k;
    int apath[MAXV],d;//���һ�����·�������򣩼��䶥�����
    for ( i = 0; i < g.numVertex; i++)
    {
        if (S[i] == 1 && i != v)
        {
            printf("    �Ӷ���%d������%d·������Ϊ��%d\t·��Ϊ:",v,i,dist[i]);
            d = 0;
            apath[d] = i;//���·���ϵ��յ�
            k = path[i];//k ���� i ��ǰһ��������
            if (k == -1)
            {
                printf("��·��\n");
            }else
            {
                while (k != v)
                {
                    d++;
                    apath[d] = k;
                    k = path[k];//k��ǰѰ��ǰһ������

                }
                d++;
                apath[d] = v;//���·���ϵ����
                printf("%d",apath[d]);//��������
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
    ˼�룺
        �Ͽ�˹������˼��Ϊ��ͨ��ԭ��v �ҵ�һ����֮ ���·����һ���ڽӵ㣬��ͨ ֮ǰ���ڽӵ��ҵ���һ��Ȩֵ��С���ڽӵ㣬
        �ڴ��ڼ䣬ÿ�ҵ�һ���µ��ڽӵ㶼Ҫ��U����������Ƚ�Ȩֵ���޸ģ��������Լ��뵽S�еĶ��㣩����������������·���Ļ����ϣ���һ����v��u��������������·��

    ���裺
        ����ʼ����S={v},U������v������������㣬v��U�ж���ľ�����ϵ�Ȩ
        ����U��ѡȡһ��������СȨֵ�Ķ���u��������뵽S�У���ѡ���ľ������v��u�����·����
        ���Զ���uΪ�¿��ǵ��м�㣬�޸Ĺ̶�����v��U�и�����ľ��루 Cvj < Cvu+Wuj ��
        ���ظ�2,3����
*/
void Dijkstra(MGraph G,int v){
    int dist[MAXV],path[MAXV];//dist ��ǰԭ��v������i�����·����path[i]��ŵ�ǰ���·����ǰһ������ı��
    int s[MAXV];//��� ����i�Ƿ��Ѿ�����S�У��ҵ����·��
    int mindis,i,j,u;//mindis  Ȩֵ��С���
    for ( i = 0; i < G.numVertex; i++)
    {
        dist[i] = G.edges[v][i];//�����ʼ��
        s[i] = 0;//s[] �ÿ�
        if (G.edges[v][i] < INFINITY)
        {
            path[i] = v;//����v������i�б�ʱ���ö���i��ǰһ������Ϊv
        }else
        {
            path[i] = -1;//�����ڱߣ�����i��ǰһ�� ����Ϊ -1
        }
    }

    s[v] = 1;path[v] = 0;//��ԭ��v����S�в���ǣ�path�� ԭ��v��ǰһ������û�У�����Ϊ0
    for ( i = 0; i < G.numVertex; i++)
    {
        mindis = INFINITY; //Ȩֵ��С ��ֵΪ ����
        for (j = 0; j < G.numVertex; j++)//ѡȡ����S�еĶ����Ҿ�����С����Ķ���u
        {
            if (s[j] == 0 && dist[j] < mindis)
            {
                u = j;
                mindis = dist[j];
            }
        }
        s[u] = 1;//��ѡ���ľ�����С����Ķ���u ���뵽 S��
        for ( j = 0; j < G.numVertex; j++)//�޸Ĳ���S�еĶ������
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
    Dispath(G,dist,path,s,v);//������·��
    
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