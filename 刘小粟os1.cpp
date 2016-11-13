#include <iostream>
#include <queue>
using namespace std;

struct proc{
	char name;			  //������
	int pri;			  //���ȼ�
	int come;			  //����ʱ��
	int time;			  //��Ҫ����ʱ��
	int cpu;			  //����cpu��ʱ��
	char status;		  //����״̬
	friend operator < (const proc& a,const proc& b) {
		if(a.pri == b.pri) return a.come < b.come;
		return a.pri < b.pri;
	}					  //���priority_queue�����Ϊ�����ȡ�
} PCB[10];

proc curproc;			  //��ǰ���н������

priority_queue<proc>ready;//���̵ľ�������
priority_queue<proc>backup;//�����ܵ����ݽṹ�����ƣ���ӡ��ʱ����Ҫһ���󱸶���������������е���Ϣ

void print_pcb(proc x)	  //��ӡnameΪx�Ľ���pcb
{
	cout<<"name  :"<<x.name<<endl;
	cout<<"pri   :"<<x.pri<<endl;
	cout<<"come  :"<<x.come<<endl;
	cout<<"time  :"<<x.time<<endl;
	cout<<"cpu   :"<<x.cpu<<endl;
	cout<<"status:"<<x.status<<endl;
	cout<<"----------------------------"<<endl;
}

void print()			  //��ӡ��ǰ�Ľ���״̬
{
	proc tmp;
	/*��ǰ���н��̵���ź�pcb*/
	cout<<"The procedure being running is:# "<<curproc.name<<endl;
	print_pcb(curproc);
	/*�������еĽ�����ź͸��Ե�pcb*/
	cout<<"The procedure being ready are as follows:"<<endl;
	int num = 0;		   //��������ʣ����̵�����
	while(!ready.empty()) {
		num++;
		tmp = ready.top();
		ready.pop();
		backup.push(tmp);  //��ready���еĽ�����ʱ������backup�����У��Ա������ָ�
		print_pcb(tmp);
	}
	if(!num) cout<<"The ready queue is empty!"<<endl;
	while(!backup.empty()) {
		tmp = backup.top();
		backup.pop();
		ready.push(tmp);
	}						//�ָ�֮ǰ��ready���ȶ���
}

void schedule()
{
	proc tmp;
	while(!ready.empty()) {
		tmp = ready.top();
		ready.pop();		//��ȡ����ǰ���ȼ���ߵ�Ԫ��
		/*ģ����̵ĵ�������*/
		curproc = tmp;
		tmp.status = 'R';
		tmp.cpu++;
		print();
		/*�������еĺ�������*/
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
		/*�������н��̵Ļ�����Ϣ*/
		cout<<"The #"<<i<<" proc's information:"<<endl;
		cin>>PCB[i].name;
		cin>>PCB[i].pri;
		cin>>PCB[i].come;
		cin>>PCB[i].time;
		cin>>PCB[i].cpu;
		cin>>PCB[i].status;
		/*���´����Ľ���ѹ�����*/
		ready.push(PCB[i]);
	}
	/*���е����㷨*/
	schedule();
	return 0;
}
