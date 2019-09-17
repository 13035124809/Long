#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"



void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
extern int q,w,e;
typedef struct {
    int step;      //��ǰ����
    int target;    //Ŀ�경��
    int div;       //Ƶ��
} StepMotor;

extern StepMotor motor[4];
//�����ⲿ������ȫ�ֱ���ͨ����.h�ļ��ж���extern�ⲿ����������������.c�ļ��е��ã��ı�StepMotor motor[2]��ֵ
void Motor_0(u32 timer);
void Motor_1(u32 timer);
void Motor_2(u32 timer);
void Motor_3(u32 timer);
void Correct_or(void);
void front_stop(void);
void front_stop1(void);
void front_stop2(void);
void back_stop(void);
void back_stop1(void);
void right_stop(void);
void SetpMotor_SetStep(int id, int steps);      //���Ʋ���
void SetpMotor_SetSpeed(int id, int speed);     //�����ٶ�
void MOTOR_IRQHandler(void);
#endif
