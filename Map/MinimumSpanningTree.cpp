/*
    ����������С������
    ʱ�䣺2020��6��22��16:23:31
    ���ߣ����ing
*/
#include <stdio.h>
#define MAXV 6        //��󶥵����
#define MaxEdges 20 //������
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

/*
    Prim����ķ�㷨
    adjvex[j] Ϊ lowcost[j]����� ����㣬jΪ�յ㣬lowcost[j] Ϊ Ȩֵ    �磺(adjvex[j],j) = lowcost[j]
    lowcost[j]Ϊ(adjvex[j],j)��Ȩֵ
    lowcost[k] = 0,�����ҳ�����СȨֵ�ıߵ��յ������С������
    ˼·�� 
        1.��ʼ��U={v}����v��������������б�Ϊ��ѡ��
        2.�ظ�һ�²��裨n-1���Σ�ʹ��������n-1�������㱻���뵽U��
            ���Ӻ�ѡ����ѡȨֵ��С�ı߼���lowcost[]����ñ���V-U�ж�����k����k����U�У�
            �����쵱ǰV-U�����ж���j���޸ĺ�ѡ�ߣ����ߣ�k��j����ȨֵС��ԭ���Ͷ���j�����ĺ�ѡ�ߣ����ñߣ�k��j��ȡ��������Ϊ��ѡ��
    ʱ�临�Ӷȣ�numVertex^2��
*/
void Prim(MGraph g, int v)
{
    int lowcost[MAXV], adjvex[MAXV]; //lowcost[j]Ϊ �洢����j�ıߵ�Ȩֵ��adjvex[i]��ʾ��Ӧ�Ķ���
    int min, i, j, k;                //minΪȨֵ��С��ֵ��kΪ ����ĳ������ڽӵ�
    for (i = 0; i < g.numVertex; i++)
    {
        lowcost[i] = g.edges[v][i]; //��ʼ����lowcost��ֵΪ v����v���ڽӵ��Ȩֵ
        adjvex[i] = v;              //adjvex Ĭ�϶�Ϊv����
    }

    for (i = 1; i < g.numVertex; i++) //�ҳ���n-1��������
    {
        min = INFINITY; //��ֵΪ����ֵ
        for (j = 0; j < g.numVertex; j++)
        {
            if (lowcost[j] != 0 && lowcost[j] < min) //�ų��Ѿ�������С�������еĶ��㣬���ҳ���U����Ķ���k
            {
                //min �����µ���СȨֵ
                min = lowcost[j];
                k = j; //k��¼��СȨֵ�Ķ���λ��
            }
        }
        printf("�ߣ�%d,%d��ȨΪ��%d\n", adjvex[k], k, min); //adjvex[k]��ʼ���㣬kΪ�ն˶���
        lowcost[k] = 0;                                     //�� k����Ķ������ ��С������,
        for (j = 0; j < g.numVertex; j++)                   //����k���㵽���ߵ�Ȩֵ����lowcost����k���㵽j��Ȩֵ�� ֮ǰ ���㵽j��Ȩֵ ҪС�����滻ԭ����lowcost[j]
        {
            //���� lowcost��adjvex���飬��Ϊ �¼���k����
            if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j]) //��ǰ�ߴ��ڣ��� ��ǰ��ȨֵС�ڶ�Ӧ ֮ǰ���㵽j��Ȩֵ���滻֮
            {
                lowcost[j] = g.edges[k][j]; //��k��j�� ��ֵ�滻��ԭ�ȶ��㣬j����ֵ
                adjvex[j] = k;              //����ʼ���㸳ֵ
            }
        }
    }
}

typedef struct
{
    int u; //�ߵ����
    int v; //�ߵ��յ�
    int w; //�ߵ�Ȩֵ
} Edge;
/*
    ֱ�Ӳ�������
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
    Kruskal�㷨����
    ��������vset�������ж����������Ƿ���ͨ

    ˼·��
        1.��ʼ���߼�E����ͼg����
        2.�Ա߼�E������������
        3.ѭ���������ɵı�k ������ ͼ�Ķ�������
            ��ȡ�� �߼��е�j�����е� ͷβ����
            �����䶥�����ڵĸ��������е�ֵȡ��
            ���ж� sn1��sn2�Ƿ���ȣ��������ͨ������
                ������ȣ����ɱ߼�1����ӡ��·��
            j++���߼���һ
        4.ֱ��whileѭ������
*/
void Kruskal(MGraph g)
{
    int i, j, u1, v1, sn1, sn2, k;
    int vset[MAXV];
    Edge E[MaxEdges];                     //������б�
    k = 0;                            //E�����0�±꿪ʼ��
    for (i = 0; i < g.numVertex; i++) //��g�����ı߼�E
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

    insertSort(E, g.numEdges);// ����ֱ�Ӳ��������E���鰴Ȩֵ����
    for ( i = 0; i < g.numVertex; i++)//��ʼ�� ��������
    {
        vset[i] = i;
    }
    k = 1;// k��ʾ��ǰ�����������ĵڼ����ߣ���ֵΪ1
    j = 0;//E�бߵ��±�
    while (k < g.numVertex)//�������ı���С�ڶ�����ѭ��
    {
        u1 = E[j].u; v1 = E[j].v;//ȡһ���ߵ� ͷβ����
        sn1 = vset[u1];
        sn2 = vset[v1];
        if (sn1 != sn2)
        {
            printf("(%d, %d): %d\n",u1,v1,E[j].w);
            k++;//���ɱ�����1
            for ( i = 0; i < g.numVertex; i++)//������ͳһ���
            {
                if (vset[i] == sn2)//��sn2�����vset[i] ��Ϊ sn1
                {
                    vset[i] = sn1;
                }
                
            }
            
        }
        j++;//��һ����

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