/*
    ���������㷨
    ʱ�䣺2020��7��8��20:16:34
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

void Dispath(MGraph g,int A[][MAXV],int path[][MAXV]){
    int i,j;//ѭ������
    int k;//��ʱ��� ǰ�����
    int apath[MAXV],d;//apath������·��,d Ϊ apath�Ǳ�
    for ( i = 0; i < g.numVertex; i++)
    {
        for ( j = 0; j < g.numVertex; j++)
        {
            if (A[i][j] < INFINITY && i != j)
            {
                printf("    ��%d��%d�����·��Ϊ��",i,j);
                k = path[i][j];//j��ǰ������
                d = 0;
                apath[d] = j;//����յ�
                while (k != -1 && k != i)//·��������м��
                {
                    d++;
                    apath[d] = k;
                    k = path[i][k];
                }
                d++;
                apath[d] = i;//������
                printf("    %d",apath[d]);
                for (int s = d-1; s >= 0; s--)
                {
                    printf(",%d",apath[s]);
                }
                printf("  ·������Ϊ��%d\n",A[i][j]);

            }
            
        }
        
    }
    
}

/*
    A[i][j]��Ŷ���i ��j�ĵ�ǰ���·�����ȣ�
    path�����Ƶ������ж���֮������·������i�б�ʾ ����i��������������·������path[i][j]��Ŷ���j��ǰ������
    ˼�룺
        ��ʼ��ԭ�ڽӾ���ÿ������A[i][j]������ i��j �����м��k���ӣ� A[i][j] = MIN{A[i][j] ,A[i][k]+A[k][j]},���޸Ķ�Ӧ��·������
        ֱ�����о���k���������·�����Ƚ���ϣ��ڴ�����k����Ļ����ϵõ���ӦA��path���ٴ��� ���� ��������
        �Դ����Ƶõ����ж����֮������·�����������·��
*/
void Floyd(MGraph g){
    int A[MAXV][MAXV],path[MAXV][MAXV];
    int i,j,k;//kΪ�м�㣬iΪ�ߵĿ�ʼ��㣬jΪ�ߵ��ն˽��
    for ( i = 0; i < g.numVertex; i++)//��ʼ��
    {
        for (j = 0; j < g.numVertex; j++)
        {
            A[i][j] = g.edges[i][j]; //Ĭ��Ϊԭ�ڽӾ���
            if (i != j && g.edges[i][j] < INFINITY)//<i,j>���ڣ��Ҳ��Ǳ���
            {
                path[i][j] = i;//����j��ǰ�����
            }else
            {
                path[i][j] = -1;//�ޱߣ����� ��Ϊ-1
            }
        }
    }

    for ( k = 0; k < g.numVertex; k++)
    {
        for ( i = 0; i < g.numVertex; i++)
        {
            for ( j = 0; j < g.numVertex; j++)//�޸����·��
            {
                if (A[i][j] > A[i][k] + A[k][j])//����i ������j������ ����i �趥��k �ٵ�����jʱ
                {
                    A[i][j] = A[i][k] + A[k][j];//<i,j>�滻��С��·������
                    path[i][j] = path[k][j];//��<i,j>�����·����ǰ����Ϊ ���һ�������ǰ����path[k][j]��
                }
                
            }
        }
        
    }
    Dispath(g,A,path);//������·��
    

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