#include "pid.h"
#include "usart.h"
#include "sys.h"
#include "math.h"

struct _pid {
    float SetGoal;//�����趨ֵ
    float ActualGoal;//����ʵ��ֵ
    float err;//����ƫ��ֵ
    float err_last;//������һ��ƫ��ֵ
    float Kp,Ki,Kd;//������������֡�΢��ϵ��
    float voltage;//�����ѹֵ������ִ�����ı�����
    float integral;//�������ֵ
    float umax;
    float umin;
} pid;

float PID_realize(float Goal) {
    int index;
    pid.SetGoal=Goal;
    pid.err=pid.SetGoal-pid.ActualGoal;

    if(pid.ActualGoal>pid.umax) //��ɫ��ɫ��ʾ�����ֱ��͵�ʵ��
    {

        if(fabs(pid.err)>200)//��ɫ��עΪ���ַ������
        {
            index=0;
        } else {
            index=1;
            if(pid.err<0)
            {
                pid.integral+=pid.err;
            }
        }
    } else if(pid.ActualGoal<pid.umin) {
        if(fabs(pid.err)>200)//���ַ������
        {
            index=0;
        } else {
            index=1;
            if(pid.err>0)
            {
                pid.integral+=pid.err;
            }
        }
    } else {
        if(fabs(pid.err)>200)//���ַ������
        {
            index=0;
        } else {
            index=1;
            pid.integral+=pid.err;
        }
    }

    pid.voltage=pid.Kp*pid.err+index*pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);

    pid.err_last=pid.err;
    pid.ActualGoal=pid.voltage*1.0;
    return pid.ActualGoal;
}
void PID_init(void) {
    printf("PID_init begin \n");
    pid.SetGoal=0.0;
    pid.ActualGoal=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=0.2;
    pid.Ki=0.1; //ע�⣬���ϼ�����ȣ�����Ӵ��˻��ֻ��ڵ�ֵ
    pid.Kd=0.2;
    pid.umax=400;
    pid.umin=-200;
    printf("PID_init end \n");
}
