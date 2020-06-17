/*
    �ڽӾ���
    ʱ�䣺2020��6��15��19:55:40
    ���ߣ���
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

bool visited[MAXV];//��¼�����Ƿ񱻷��ʹ�
/*
    ������ȱ���
    ˼·��
        1.���˶������ϱ�ǣ������
        2.�Դ˶�����ڽӵ� ��һʹ�� ������ȱ���
        3.һֱ�ݹ飬֪���Դ˶���������ڽӵ�������
        4.����ݹ��Լ����ж� ����v�Ƿ���δ���ʵ��ڽӵ㣬��������ݹ�
    ʱ�临�Ӷȣ�O(n^2)
*/
void DFS(MGraph G,int v){
    visited[v] = 1;//��Ϊ�Ѿ�����
    printf("%d\t",G.vexs[v].no);//������ʵĶ���
    for (int i = 0; i < G.numVertex; i++)
    {
        if(!visited[v] && G.edges[v][i] == 1)//�ö���δ�����ʣ��Ҷ��ڵıߴ���
        {
            DFS(G,i);
        }
    }
}
/*
    ����������ȱ���
    ˼·��
        1.����ѭ��
            ��ͼ��G��ÿһ���������������ȱ���
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
    ������ȱ���
    �������ʽ �� �������� ��α�������
    ˼·��
        1.����һ�� ����
        2.�Է��ʷ��������ʶ���г�ʼ��
        3.���ʸö��㣬����ʶ�ѷ���
        4.���ö������
        5.�Ըö��������һ�н��б����ظ�ִ��
            ���ж�ջ�Ƿ�Ϊ��
                �����գ�����
                ���жϸö����Ƿ��ѷ���
                ��������ö��㣬������
        6.ֱ������Ϊ��
*/
void BFS(MGraph G, int v)
{
    int queue[MAXV];
    int front = 0, rear = 0; //����һ��ѭ������
    int w, i;
    for (int i = 0; i < G.numVertex; i++)
    {
        visited[i] = 0; //��ʼ������
    }

    for (int j = 0; j < G.numVertex; j++)//��ÿһ��������з���
    {
        if (!visited[j])
        {
            printf("%d\t", G.vexs[j]); //�������
            visited[j] = 1;            //�ѷ���
            rear = (rear + 1) % MAXV;
            queue[rear] = j; //���������

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