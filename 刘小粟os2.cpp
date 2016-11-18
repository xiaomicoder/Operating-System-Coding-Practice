#include <iostream>
#include <cstring>
#define N 6			 //一共5个进程,从1开始计数
#define	M 5			 //一共4个资源,从1开始计数
using namespace std;

int Max[N][M];		 //最大需求资源
bool finish[N];		 //是否完成
int work[M];		 //当前可利用的资源
int need[N][M];		 //尚需的资源
int allocation[N][M];//每个进程已经分配到的资源
int available[M];	 //每个资源现在剩余的数量
int CNT = 0;		 //总共的可能性
int ans[N];			 //记录每次的答案

bool judge()
{
	int i;
	int cnt = 0;
	for(i = 1;i < N;i++)
		if(finish[i])
			cnt++;
	if(cnt == 5) return true;
	else return false;
}

void output()
{
	cout<<"-----------------------"<<endl;
	cout<<"No."<<CNT<<" possible answer is as follows:\n";
	for(int i = 1;i < N;i++)
		cout<<"#"<<i<<" process:"<<ans[i]<<endl;
}

void dfs(int x,int q) //查找x号进程作为第q个输出是否合适
{
	int i;
	//step 1
	if(finish[x]) return;
	//step 2
	int cnt = 0;
	for(i = 1;i < M;i++) 
		if(need[x][i] <= work[i])
			cnt++;
	if(cnt != 4) return ;
	//process
	for(i = 1;i < M;i++)
		work[i] += allocation[x][i];
	finish[x] = true;
	ans[q] = x;
	//judge if it's already finished
	if(q == 5) {
		CNT++;
		output();
		finish[x] = false;
		//before returning to last level,restore the value
		for(i = 1;i < M;i++)
			work[i] -= allocation[x][i];
		return ;
	}
	for(i = 1;i < N;i++) 
		dfs(i,q+1);
	//before returning to last level,restore the value
	finish[x] = false;
	for(i = 1;i < M;i++)
		work[i] -= allocation[x][i];
}

int main()
{
	int i,j;
	cout<<"Please input the max requirement of each process:"<<endl;
	for(i = 1;i < N;i++) {
		cout<<"#"<<i<<":";
		cin>>Max[i][1];
		cin>>Max[i][2];
		cin>>Max[i][3];
		cin>>Max[i][4];
		cout<<endl;
	}
	cout<<"Please input the resources each process already had:"<<endl;
	for(i = 1;i < N;i++) {
		cout<<"#"<<i<<":";
		cin>>allocation[i][1];
		cin>>allocation[i][2];
		cin>>allocation[i][3];
		cin>>allocation[i][4];
		cout<<endl;
	}
	cout<<"The total amount of each resources:";
	for(i = 1;i < M;i++) {
		cin>>available[i];
		available[i] -= (allocation[1][i]+allocation[2][i]+allocation[3][i]+allocation[4][i]+allocation[5][i]);
		work[i] = available[i];
	} 
	//calculate need
	for(i = 1;i < N;i++)
		for(j = 1;j < M;j++) 
			need[i][j] = Max[i][j]-allocation[i][j];
	//dfs
	for(i = 1;i < N;i++) {
		for(j = 1;j < N;j++)
			finish[j] = false;
		dfs(i,1);
	}
	return 0;
}

