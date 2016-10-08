#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

#define HZ    100

void cpuio_bound(int last, int cpu_time, int io_time);

int main(int argc, char * argv[])
{
    pid_t subp1,subp2,subp3;
    /*
    fork����ֵ<0ʱ�������½��̴���
	fork����ֵ=0ʱ��������Ϊ�ӽ�����ִ��
	fork����ֵ>0ʱ��������Ϊ��������ִ��
	*/
	subp1 = fork();
	if(subp1 < 0) {
		printf("Fail to create new process!\n");
	} else if(subp1 == 0){
		cpuio_bound(10,0,5);
	} else {
		printf("New process created:%d\n",subp1);
		waitpid(subp1,NULL,0);
	}
	subp2 = fork();
	if(subp2 < 0) {
		printf("Fail to create new process!\n");
	} else if(subp2 == 0){
		cpuio_bound(10,4,0);
	} else {
		printf("New process created:%d\n",subp2);
		waitpid(subp2,NULL,0);
	}
	subp3 = fork();
	if(subp3 < 0) {
		printf("Fail to create new process!\n");
	} else if(subp3 == 0){
		cpuio_bound(10,2,3);
	} else {
		printf("New process created:%d\n",subp3);
		waitpid(subp3,NULL,0);
	}
    return 0;
}

/*
 * �˺������ղ���ռ��CPU��I/Oʱ��
 * last: ����ʵ��ռ��CPU��I/O����ʱ�䣬�����ھ��������е�ʱ�䣬>=0�Ǳ����
 * cpu_time: һ������ռ��CPU��ʱ�䣬>=0�Ǳ����
 * io_time: һ��I/O���ĵ�ʱ�䣬>=0�Ǳ����
 * ���last > cpu_time + io_time�����������ռ��CPU��I/O
 * ����ʱ��ĵ�λΪ��
 */
void cpuio_bound(int last, int cpu_time, int io_time)
{
    struct tms start_time, current_time;
    clock_t utime, stime;
    int sleep_time;

    while (last > 0)
    {
        /* CPU Burst */
        times(&start_time);
        /* ��ʵֻ��t.tms_utime����������CPUʱ�䡣����������ģ��һ��
         * ֻ���û�״̬���е�CPU�󻧣�����for(;;);�������԰�t.tms_stime
         * ���Ϻܺ���*/
        do
        {
            times(&current_time);
            utime = current_time.tms_utime - start_time.tms_utime;
            stime = current_time.tms_stime - start_time.tms_stime;
        } while ( ( (utime + stime) / HZ )  < cpu_time );
        last -= cpu_time;

        if (last <= 0 )
            break;

        /* IO Burst */
        /* ��sleep(1)ģ��1���ӵ�I/O���� */
        sleep_time=0;
        while (sleep_time < io_time)
        {
            sleep(1);
            sleep_time++;
        }
        last -= sleep_time;
    }
}
