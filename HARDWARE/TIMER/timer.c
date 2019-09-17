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

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����

}

void SetpMotor_SetStep(int id, int steps)
{
    motor[id].target=motor[id].step+steps*2;

}

void SetpMotor_SetSpeed(int id, int speed)
{
    motor[id].div=speed;//ÿ��divһ��ʱ�䣬ִ������һ��
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

void TIM2_IRQHandler(void)//�жϷ�������ÿ��һ��ʱ�����һ�κ���
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)       //�ж�ʹ��
    {
        MOTOR_IRQHandler();
        timer++;
    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}
//���ٵ������
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����

}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ
        LED1=!LED1;
    }
}




//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//ʹ��PB4����������������

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5

    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4; //TIM_CH2....����PB4��PB5

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO

    //��ʼ��TIM3
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM3 Channel2 PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���PWMģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);//�����ڶ���PWM��

    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//�����ڶ���PWM��

    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}



