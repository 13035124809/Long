#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "step.h"
#include "wave.h"
#include "pid.h"
int main(void)
{
    s32 Speed0=30;
    s32 Speed1=30;
    s32 Speed2=30;
    s32 Speed3=30;
    s32 Speed=30;
    s32 loa_Speed=45;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init();
    uart_init(115200);
    LED_Init();
    TIM2_Int_Init(12,10);
    TIM6_Int_Init(999,71);
    left_run(1600);

    speed_up(-2500,loa_Speed,-2500,loa_Speed,2500,loa_Speed,2500,loa_Speed);
    Correct_or();
//    run(-4600,35,-4600,35,4600,35,4600,35);
//    front_stop1();
    speed_down(-200,loa_Speed,-200,loa_Speed,200,loa_Speed,200,loa_Speed);
//    Correct_or();
    Self_tuning(1,-134000,Speed0,-134000,Speed1,134000,Speed2,134000,Speed3);

///////////////////////////////////////////////////////////////////////////
    //后退
    speed_up(1600,loa_Speed,1600,loa_Speed,-1600,loa_Speed,-1600,loa_Speed);
    Correct_or();
    run(4600,45,4600,45,-4600,45,-4600,45);
    back_stop1();//huan
    speed_down(200,loa_Speed,400,loa_Speed,-400,loa_Speed,-400,loa_Speed);
    Self_tuning(0,49000,Speed0,49000,Speed1,-49000,Speed2,-49000,Speed3);
    auto_trans(0);

///////////////////////////////////////////////////////////////////////////
    //二次左移
    left_run1(2100);

    speed_up(-2000,loa_Speed,-2000,loa_Speed,2000,loa_Speed,2000,loa_Speed);
    Correct_or();
    run(-16000,loa_Speed,-16000,loa_Speed,16000,loa_Speed,16000,loa_Speed);
    front_stop1();
    speed_down(-300,loa_Speed,-300,loa_Speed,300,loa_Speed,300,loa_Speed);

    //Self_tuning(1,-1400,Speed0,-1400,Speed1,1400,Speed2,1400,Speed3);
    Self_tuning(1,-49000,Speed0,-49000,Speed1,49000,Speed2,49000,Speed3);
    auto_trans(1);
///////////////////////////////////////////////////////////////////////////
    //三次左移
    left_run2(2100);
    speed_up(2000,loa_Speed,2000,loa_Speed,-2000,loa_Speed,-2000,loa_Speed);
    Correct_or();
    run(20000,loa_Speed,20000,loa_Speed,-20000,loa_Speed,-20000,loa_Speed);
    back_stop1();
    speed_down(300,loa_Speed,300,loa_Speed,-300,loa_Speed,-300,loa_Speed);

    // Self_tuning(0,1400,Speed0,1400,Speed1,-1400,Speed2,-1400,Speed3);
    Self_tuning(0,49000,Speed0,49000,Speed1,-49000,Speed2,-49000,Speed3);
    auto_trans(0);
///////////////////////////////////////////////////////////////////////////
    //四次左移
    left_run1(1600);

    speed_up(-2000,loa_Speed,-2000,loa_Speed,2000,loa_Speed,2000,loa_Speed);
    Correct_or();
    run(-16000,loa_Speed,-16000,loa_Speed,16000,loa_Speed,16000,loa_Speed);
    front_stop1();
    speed_down(-300,loa_Speed,-300,loa_Speed,300,loa_Speed,300,loa_Speed);

    //Self_tuning(1,-1400,Speed0,-1400,Speed1,1400,Speed2,1400,Speed3);
    Self_tuning(1,-49000,Speed0,-49000,Speed1,49000,Speed2,49000,Speed3);
    auto_trans(1);
///////////////////////////////////////////////////////////////////////////
    //五次左移
    left_run2(1800);
    //后退
    speed_up(2500,loa_Speed,2500,loa_Speed,-2500,loa_Speed,-2500,loa_Speed);
    Correct_or();
    run(20000,loa_Speed,20000,loa_Speed,-20000,loa_Speed,-20000,loa_Speed);
    back_stop1();
    speed_down(300,loa_Speed,300,loa_Speed,-300,loa_Speed,-300,loa_Speed);

    //Self_tuning(2,2400,Speed0,2400,Speed1,-2400,Speed2,-2400,Speed3);
    Self_tuning(0,49000,Speed0,49000,Speed1,-49000,Speed2,-49000,Speed3);
    auto_trans(0);
////////////////////////////////////////////////////////////////////
    //右移
    //auto_trans(2);//平移自调
    speed_up(-1600,Speed0,1600,Speed1,-1600,Speed2,1600,Speed3);
    Correct_or();
    run(-15000,Speed,15000,Speed,-15000,Speed,15000,Speed);
    Correct_or();
    //right_stop();
    speed_down(-200,Speed0,200,Speed1,-200,Speed2,200,Speed3);




}


