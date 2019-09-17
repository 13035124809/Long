#include "timer.h"
#include "led.h"
#include "usart.h"
#include "sys.h"
#include "math.h"
#include "wave.h"
#include "step.h"
#include "delay.h"
extern float Left_dist;
extern float Front_dist;
extern float Right_dist;
extern float BackLeft_dist;
extern float BackRight_dist;

StepMotor motor[4];
u32 timer=0;
u8 corr=1;
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设

}

void SetpMotor_SetStep(int id, int steps)
{
    motor[id].target=motor[id].step+steps*2;

}

void SetpMotor_SetSpeed(int id, int speed)
{
    motor[id].div=speed;//每隔div一段时间，执行内容一次
}

void Correct_or(void)
{
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {
        if(motor[0].target==motor[0].step)
        {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            corr=0;
        }
    }

}
void front_stop(void)
{
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {
        if(PFin(5)==0)
        {   delay_ms(5);
            if(PFin(5)==0)
            {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            corr=0;
            }
        }
    }
}
void front_stop1(void)
{
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {
        if(PFin(1)==0||PFin(2)==0)
        {   delay_ms(5);
            if(PFin(1)==0||PFin(2)==0)
            {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            corr=0;
            }
        }
    }
}
void front_stop2(void)
{
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {
        if(PFin(3)==1&&PFin(4)==1)
        {   delay_ms(5);
            if(PFin(3)==1&&PFin(4)==1)
            {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            corr=0;
            }
        }
    }
}
void back_stop(void)
{
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {   if(PFin(6)==0)
        {   delay_ms(5);
            if(PFin(6)==0)
            {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            corr=0;
            }
        }
    }
}
void back_stop1(void)
{
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {   if(PFin(3)==0||PFin(4)==0)
        {   delay_ms(5);
            if(PFin(3)==0||PFin(4)==0)
            {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            corr=0;
            }
        }
    }
}
void right_stop(void)
{   s32 step;s32 runspeed=40;
    int g=0;
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {   if(PFin(7)==0)
        {   delay_ms(5);
            if(PFin(7)==0)
            {   step=motor[0].step;
                g=1;
                motor[0].target=motor[0].step=0;
            }
        }
        if(motor[0].target==motor[0].step)
        {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            corr=0;
            if(g==1) {
                auto_trans(2);auto_trans(0);
                speed_up(-1600,45,1600,45,-1600,45,1600,45);
                Correct_or();
                run(-(13400-step),runspeed,(13400-step),runspeed,-(13400-step),runspeed,(13400-step),runspeed);
                Correct_or();
            }
        }
    }
}
void Motor_0(u32 timer)
{
    if(timer%motor[0].div==0)
    {
        if(motor[0].step<motor[0].target)
        {
            PBout(0)=0;
            PAout(0)=timer/motor[0].div&1;
            motor[0].step++;
        }
        else if(motor[0].step>motor[0].target)
        {
            PBout(0)=1;
            PAout(0)=timer/motor[0].div&1;
            motor[0].step--;
        }
//				printf("\r\n0%d      %d\r\n",motor[0].step,motor[0].target);
    }

}
void Motor_1(u32 timer)
{
    if(timer%motor[1].div==0)
    {
        if(motor[1].step<motor[1].target)
        {
            PBout(1)=0;
            PAout(1)=timer/motor[1].div&1;
            motor[1].step++;
        }
        else if(motor[1].step>motor[1].target)
        {
            PBout(1)=1;
            PAout(1)=timer/motor[1].div&1;
            motor[1].step--;
        }
//				printf("1%d      %d\r\n",motor[1].step,motor[1].target);
    }

}
void Motor_2(u32 timer)
{
    if(timer%motor[2].div==0)
    {
        if(motor[2].step<motor[2].target)
        {
            PBout(2)=0;
            PAout(4)=timer/motor[2].div&1;
            motor[2].step++;
        }
        else if(motor[2].step>motor[2].target)
        {
            PBout(2)=1;
            PAout(4)=timer/motor[2].div&1;
            motor[2].step--;
        }
//				printf("2%d      %d\r\n",motor[2].step,motor[2].target);
    }

}
void Motor_3(u32 timer)
{
    if(timer%motor[3].div==0)
    {
        if(motor[3].step<motor[3].target)
        {
            PCout(5)=0;
            PAout(5)=timer/motor[3].div&1;
            motor[3].step++;
        }
        else if(motor[3].step>motor[3].target)
        {
            PCout(5)=1;
            PAout(5)=timer/motor[3].div&1;
            motor[3].step--;
        }
//				printf("3%d      %d\r\n",motor[3].step,motor[3].target);
    }

}
void MOTOR_IRQHandler(void)
{
    Motor_0(timer);
    Motor_1(timer);
    Motor_2(timer);
    Motor_3(timer);
}

void TIM2_IRQHandler(void)//中断服务函数，每隔一段时间进入一次函数
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)       //判断使能
    {
        MOTOR_IRQHandler();
        timer++;
    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}
//减速电机驱动
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设

}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源
        LED1=!LED1;
    }
}




//TIM3 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//使用PB4，必须加上这个函数

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5

    //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4; //TIM_CH2....采用PB4和PB5

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO

    //初始化TIM3
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM3 Channel2 PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制PWM模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);//产生第二个PWM波

    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//产生第二个PWM波

    TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}



