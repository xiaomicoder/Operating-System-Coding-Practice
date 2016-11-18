#include <iostream>
#include <cstring>
#define N 6			 //һ��5������,��1��ʼ����
#define	M 5			 //һ��4����Դ,��1��ʼ����
using namespace std;

int Max[N][M];		 //���������Դ
bool finish[N];		 //�Ƿ����
int work[M];		 //��ǰ�����õ���Դ
int need[N][M];		 //�������Դ
int allocation[N][M];//ÿ�������Ѿ����䵽����Դ
int available[M];	 //ÿ����Դ����ʣ�������
int CNT = 0;		 //�ܹ��Ŀ�����
int ans[N];			 //��¼ÿ�εĴ�

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

void dfs(int x,int q) //����x�Ž�����Ϊ��q������Ƿ����
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

