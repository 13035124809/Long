#include "pid.h"
#include "usart.h"
#include "sys.h"
#include "math.h"

struct _pid {
    float SetGoal;//定义设定值
    float ActualGoal;//定义实际值
    float err;//定义偏差值
    float err_last;//定义上一个偏差值
    float Kp,Ki,Kd;//定义比例、积分、微分系数
    float voltage;//定义电压值（控制执行器的变量）
    float integral;//定义积分值
    float umax;
    float umin;
} pid;

float PID_realize(float Goal) {
    int index;
    pid.SetGoal=Goal;
    pid.err=pid.SetGoal-pid.ActualGoal;

    if(pid.ActualGoal>pid.umax) //灰色底色表示抗积分饱和的实现
    {

        if(fabs(pid.err)>200)//蓝色标注为积分分离过程
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
        if(fabs(pid.err)>200)//积分分离过程
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
        if(fabs(pid.err)>200)//积分分离过程
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
    pid.Ki=0.1; //注意，和上几次相比，这里加大了积分环节的值
    pid.Kd=0.2;
    pid.umax=400;
    pid.umin=-200;
    printf("PID_init end \n");
}
