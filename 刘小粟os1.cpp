#include <iostream>
#include <queue>
using namespace std;

struct proc{
	char name;			  //进程名
	int pri;			  //优先级
	int come;			  //到达时间
	int time;			  //需要运行时间
	int cpu;			  //已用cpu的时间
	char status;		  //进程状态
	friend operator < (const proc& a,const proc& b) {
		if(a.pri == b.pri) return a.come < b.come;
		return a.pri < b.pri;
	}					  //结合priority_queue定义何为“优先”
} PCB[10];

proc curproc;			  //当前运行进程序号

priority_queue<proc>ready;//进程的就绪队列
priority_queue<proc>backup;//由于受到数据结构的限制，打印的时候需要一个后备队列来保存就绪队列的信息

void print_pcb(proc x)	  //打印name为x的进程pcb
{
	cout<<"name  :"<<x.name<<endl;
	cout<<"pri   :"<<x.pri<<endl;
	cout<<"come  :"<<x.come<<endl;
	cout<<"time  :"<<x.time<<endl;
	cout<<"cpu   :"<<x.cpu<<endl;
	cout<<"status:"<<x.status<<endl;
	cout<<"----------------------------"<<endl;
}

void print()			  //打印当前的进程状态
{
	proc tmp;
	/*当前运行进程的序号和pcb*/
	cout<<"The procedure being running is:# "<<curproc.name<<endl;
	print_pcb(curproc);
	/*就绪队列的进程序号和各自的pcb*/
	cout<<"The procedure being ready are as follows:"<<endl;
	int num = 0;		   //就绪队列剩余进程的数量
	while(!ready.empty()) {
		num++;
		tmp = ready.top();
		ready.pop();
		backup.push(tmp);  //将ready队列的进程暂时保存在backup队列中，以备后续恢复
		print_pcb(tmp);
	}
	if(!num) cout<<"The ready queue is empty!"<<endl;
	while(!backup.empty()) {
		tmp = backup.top();
		backup.pop();
		ready.push(tmp);
	}						//恢复之前的ready优先队列
}

void schedule()
{
	proc tmp;
	while(!ready.empty()) {
		tmp = ready.top();
		ready.pop();		//提取出当前优先级最高的元素
		/*模拟进程的调度运行*/
		curproc = tmp;
		tmp.status = 'R';
		tmp.cpu++;
		print();
		/*进行运行的后续处理*/
		if(tmp.cpu == tmp.time) {
			tmp.status = 'F';
		}
		if(tmp.cpu < tmp.time) {
			tmp.pri--;
			tmp.status = 'W';
			ready.push(tmp);
		}
	}
}

int main()
{
	cout<<"Please input the procedures:"<<endl;
	for(int i = 1;i <= 7;i++) {
		/*输入所有进程的基本信息*/
		cout<<"The #"<<i<<" proc's information:"<<endl;
		cin>>PCB[i].name;
		cin>>PCB[i].pri;
		cin>>PCB[i].come;
		cin>>PCB[i].time;
		cin>>PCB[i].cpu;
		cin>>PCB[i].status;
		/*将新创建的进程压入队列*/
		ready.push(PCB[i]);
	}
	/*运行调度算法*/
	schedule();
	return 0;
}
