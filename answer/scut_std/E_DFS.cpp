#include<cstdio>
using namespace std;

int v[100][2],map[10][10];

bool judge(int x,int y,int k)
{
	for(int i=0;i<9;i++)
		if(map[i][y]==k||map[x][i]==k)
			return false;
	int dx=x-x%3,dy=y-y%3;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(map[dx+i][dy+j]==k)
				return false;
	return true;
}

int dfs(int n)
{
	if(n<0) return 1;
	for(int i=1;i<=9;i++)
	{
		int x=v[n][0],y=v[n][1];
		if(judge(x,y,i))
		{
			map[x][y]=i;
			if(dfs(n-1)) return 1;
			map[x][y]=0;
		}
	}
	return 0;
}

int main()
{
	int num=0;
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
		{
			scanf("%d",&map[i][j]);
			if(map[i][j]==0)
			{
				v[num][0]=i;
				v[num++][1]=j;
			}
		}
	dfs(num-1);
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
			printf("%d ",map[i][j]);
		printf("%d\n",map[i][8]);
	}
	for(int j=0;j<8;j++)
		printf("%d ",map[8][j]);
	printf("%d",map[8][8]);
	return 0;
}
