/*
    ����������С������
    ʱ�䣺2020��6��22��16:23:31
    ���ߣ����ing
*/
#include <stdio.h>
#define MAXV 10//��󶥵����
#define INFINITY 65535//�����
typedef int InfoType;
typedef struct{
    int no;//������
    InfoType info;//����������Ϣ
}VertexType;//��������

typedef struct{
    int edges[MAXV][MAXV];//�ڽӾ���ı�����
    int numVertex,numEdges;//�������ͱ���
    VertexType vexs[MAXV];//�����
}MGraph;//������ͼ�ڽӾ���



/*
    �����ڽӾ���  ������ͼ
*/
void CreateMGraph(MGraph * G){
    int i,j,k,w;
    printf("���붥�������ͱ�����");
    scanf("%d %d",&G->numVertex,&G->numEdges);
    for ( i = 0; i < G->numVertex; i++)
    {
        printf("���붥����Ϣ����%d��:",i+1);
        scanf("%d",&G->vexs[i].no);//д�붥����Ϣ
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
            
            G->edges[i][j] = INFINITY;//��ʼ�� �ڽӾ���
        }
    }

    for ( k = 0; k < G->numEdges; k++)
    {
        printf("����ߣ�vi,vj���ϵ��±�i��j��Ȩֵ��");
        scanf("%d %d %d",&i,&j,&w);
        G->edges[i][j] = w;
        G->edges[j][i] = w;//����ͼ������Գ�
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
void Prim(MGraph g,int v){
    int lowcost[MAXV],adjvex[MAXV];//lowcost[j]Ϊ �洢����j�ıߵ�Ȩֵ��adjvex[i]��ʾ��Ӧ�Ķ���
    int min,i,j,k;//minΪȨֵ��С��ֵ��kΪ ����ĳ������ڽӵ�
    for ( i = 0; i < g.numVertex; i++)
    {
        lowcost[i] = g.edges[v][i];//��ʼ����lowcost��ֵΪ v����v���ڽӵ��Ȩֵ
        adjvex[i] = v;//adjvex Ĭ�϶�Ϊv����
    }

    for ( i = 1; i < g.numVertex; i++)//�ҳ���n-1��������
    {
        min = INFINITY;//��ֵΪ����ֵ
        for ( j = 0; j < g.numVertex; j++)
        {
            if (lowcost[j] != 0 && lowcost[j] < min)    //�ų��Ѿ�������С�������еĶ��㣬���ҳ���U����Ķ���k
            {
                //min �����µ���СȨֵ
                min = lowcost[j];
                k = j;//k��¼��СȨֵ�Ķ���λ�� 
            }
        }
        printf("�ߣ�%d,%d��ȨΪ��%d\n",adjvex[k],k,min);//adjvex[k]��ʼ���㣬kΪ�ն˶���
        lowcost[k] = 0;//�� k����Ķ������ ��С������,   
        for ( j = 0; j < g.numVertex; j++)//����k���㵽���ߵ�Ȩֵ����lowcost����k���㵽j��Ȩֵ�� ֮ǰ ���㵽j��Ȩֵ ҪС�����滻ԭ����lowcost[j]
        {
            //���� lowcost��adjvex���飬��Ϊ �¼���k����
            if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j])//��ǰ�ߴ��ڣ��� ��ǰ��ȨֵС�ڶ�Ӧ ֮ǰ���㵽j��Ȩֵ���滻֮
            {
                lowcost[j] = g.edges[k][j];//��k��j�� ��ֵ�滻��ԭ�ȶ��㣬j����ֵ
                adjvex[j] = k;  //����ʼ���㸳ֵ
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