#include <stdio.h>
#define M 8
#define N 8
#define MaxSize 100

int mg[M+2][N+2] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};
typedef struct node
{
    int i;//当前方块的行号
    int j;//当前方块的列号
    int di;//可一个可走的相邻方块的方位号
}Box;

typedef struct stack
{
    Box data[MaxSize];
    int top;//栈顶指针
}StType;

/*
    求解迷宫算法：
        1.先将入口进栈，（初始方位设为-1）
        2.栈不空时循环
            ·取栈顶方块（不退栈）
                ·若方块是出口，这输出栈中所有的方块，即为路径
                ·否则找下一个可走的相邻方块
                    ·若不存在这样的方块，说明当前路径不可能走通，则回溯，也就是恢复当前方块为0后退栈
                    ·若存在这样的方块，则将这个可走的相邻方块进栈（其初始方位设置为 -1）
*/
bool mgpath(int xi,int yi, int xe,int ye){//求解路径 ：（xi，yi） -> （xe，ye）
    int i,j,k,di,find;
    StType st;//定义栈
    st.top = -1;//初始化栈顶指针
    st.top++;//初始化方块进栈
    st.data[st.top].i = xi;
    st.data[st.top].j = yi;
    st.data[st.top].di = -1;
    mg[xi][yi] = -1;
    while (st.top > -1)//栈不空时循环
    {
        i = st.data[st.top].i;
        j = st.data[st.top].j;
        di = st.data[st.top].di;
        if(i == xe && j == ye){//找到入口，输出路径
            printf("迷宫路径如下：\n");
            for(k = 0; k <= st.top; k++){
                printf("\t(%d, %d)",st.data[k].i,st.data[k].j);
                if((k+1) % 5 == 0)
                    printf("\n");

            }
                printf("\n");
                return true;//找到一条路径后返回true
        }
        find = 0;
        while (di < 4 && find == 0)
        {
            di++;
            switch (di)
            {
                case 0:
                    i = st.data[st.top].i-1;j = st.data[st.top].j;
                    break;
                case 1:
                    i = st.data[st.top].i;j = st.data[st.top].j+1;
                break;
                case 2:
                    i = st.data[st.top].i+1;j = st.data[st.top].j;
                break;
                case 3:
                    i = st.data[st.top].i;j = st.data[st.top].j-1;
                break;
            }
            if(mg[i][j] == 0)
                find = 1;//找到下一个可走相邻方块
        }
        if(find == 1)
        {
            st.data[st.top].di = di;//修改原栈顶元素的di值
            st.top++;//下一个可走方块进栈
            st.data[st.top].i = i;
            st.data[st.top].j = j;
            st.data[st.top].di = -1;//避免重复走到该方块
            mg[i][j] = -1;
        }
        else
        {
            mg[st.data[st.top].i][st.data[st.top].j] = 0;//让该位置变为其他路径可走
            st.top--;//该方块退栈
        }
    }
    return false;//表示没有可走路径，返回false    

}

int mgpath1(int xi,int yi,int xe,int ye)	//求解路径为:(xi,yi)->(xe,ye)
{
	int i,j,k,di,find;
	StType st;					//定义栈st
	st.top=-1;					//初始化栈顶指针
	st.top++;      				//初始方块进栈
	st.data[st.top].i=xi; st.data[st.top].j=yi;	st.data[st.top].di=-1;
	mg[xi][yi]=-1; 
	while (st.top>-1)			//栈不空时循环
	{
		i=st.data[st.top].i;j=st.data[st.top].j;di=st.data[st.top].di;  //取栈顶方块
		if (i==xe && j==ye)		//找到了出口,输出路径
		{ 
			printf("迷宫路径如下:\n");
			for (k=0;k<=st.top;k++)
			{
				printf("\t(%d,%d)",st.data[k].i,st.data[k].j);
				if ((k+1)%5==0)	//每输出每5个方块后换一行
					printf("\n");  
			}
			printf("\n");
			return(1);		//找到一条路径后返回1
		}
		find=0;
		while (di<4 && find==0)		//找下一个可走方块
		{	
			di++;
			switch(di)
			{
			case 0:i=st.data[st.top].i-1;j=st.data[st.top].j;break;
			case 1:i=st.data[st.top].i;j=st.data[st.top].j+1;break;
			case 2:i=st.data[st.top].i+1;j=st.data[st.top].j;break;
			case 3:i=st.data[st.top].i,j=st.data[st.top].j-1;break;
			}
			if (mg[i][j]==0) find=1;	//找到下一个可走相邻方块
		}
		if (find==1)					//找到了下一个可走方块
		{	
			st.data[st.top].di=di;		//修改原栈顶元素的di值
			st.top++;					//下一个可走方块进栈
			st.data[st.top].i=i; st.data[st.top].j=j; st.data[st.top].di=-1;
			mg[i][j]=-1;				//避免重复走到该方块
		}
		else							//没有路径可走,则退栈
		{	
			mg[st.data[st.top].i][st.data[st.top].j]=0;//让该位置变为其他路径可走方块
			st.top--;					//将该方块退栈
		}
	}
	return(0);							//表示没有可走路径,返回0
}

int main(void){
    if(!mgpath1(1,1,M,N))
        printf("该迷宫问题没有解！");


    getchar();
    getchar();
    return 0;
}