#include "timer.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "sys.h"
#include "delay.h"
#include "step.h"
#include "stdio.h"
#include "wave.h"
extern float Left_dist;
extern float Front_dist;
extern float Right_dist;
extern float BackLeft_dist;
extern float BackRight_dist;
s32 runspeed=30;
s32 value[]=
{
    3571,3571,3571,3571,3571,3571,3571,3571,3125,3125,
    3125,3125,3125,3125,3125,2778,2778,2778,2778,2778,
    2500,2500,2500,2500,2273,2273,2273,2083,2083,2083,
    1923,1923,1923,1786,1786,1667,1667,1562,1562,1471,
    1471,1389,1316,1316,1250,1190,1190,1136,1087,1042,
    1000,962,926,893,862,833,806,781,758,714,
    694,658,641,625,595,568,556,532,510,490,
    472,455,439,424,410,397,385,368,357,342,
    333,321,312,301,291,281,272,263,258,250,
    240,234,227,221,216,210,205,198,194,189,
    184,180,176,172,168,164,161,158,155,152,
    150,146,144,142,140,137,135,133,131,130,
    128,126,124,123,121,120,119,118,117,116,
    115,114,113,112,111,110,109,108,108,107,
    106,106,105,105,104,104,103,103,102,102,
    102,101,101,100,100,100,100,99,99,99,
    98,98,98,98,98,98,97,97,97,97,
    97,97,97,97,96,96,96,96,96,96,
    96,95,95,95,95,95,95,95,95,95,
    95,95,95,95,95,95,95,95,95,95,
    95,95,95,94,93,92,91,90,89,88,
    87,86,85,84,82,80,78,76,74,72,
    70,68,66,64,62,60,58,56,54,53,
    52,51,50,49,48,47,46,45,45,45
};
s32 value1[]=
{   3571,3571,3571,3571,3571,3571,3571,3571,3125,3125,
    3125,3125,3125,3125,3125,2778,2778,2778,2778,2778,
    2500,2500,2500,2500,2273,2273,2273,2083,2083,2083,
    1923,1923,1923,1786,1786,1667,1667,1562,1562,1471,
    1471,1389,1316,1316,1250,1190,1190,1136,1087,1042,
    1000,962,926,893,862,833,806,781,758,714,
    694,658,641,625,595,568,556,532,510,490,
    472,455,439,424,410,397,385,368,357,342,
    333,321,312,301,291,281,272,263,258,250,
    240,234,227,221,216,210,205,198,194,189,
    184,180,176,172,168,164,161,158,155,152,
    150,146,144,142,140,137,135,133,131,130,
    128,126,124,123,121,120,119,118,117,116,
    115,114,113,112,111,110,109,108,108,107,
    106,106,105,105,104,104,103,103,102,102,
    102,101,101,100,100,100,100,99,99,99,
    98,98,98,98,98,98,97,97,97,97,
    97,97,97,97,96,96,96,96,96,96,
    96,95,95,95,95,95,95,95,95,95,
    95,95,95,95,95,95,95,95,95,95,
    95,95,95,94,93,92,91,90,89,88,
    87,86,85,84,82,80,78,76,74,72,
    70,68,66,64,62,60,58,56,54,53,
    52,51,50,49,48,47,46,45,45,45,
    44,44,44,44,43,43,43,43,43,43,
    42,42,42,42,42,42,42,41,41,41,
    41,41,41,41,40,40,40,40,40,40,
    40,40,39,39,39,39,39,39,39,39,
    39,38,38,38,38,38,38,38,38,38,
    38,37,37,37,37,37,37,37,37,37,
    37,37,36,36,36,36,36,36,36,36,
    36,36,36,36,35,35,35,35,35,35,
    35,35,35,35,35,35,35,34,34,34,
    34,34,34,34,34,34,34,34,34,34,
    34,33,33,33,33,33,33,33,33,33,
    33,33,33,33,33,33,32,32,32,32,
    32,32,32,32,32,32,32,32,32,32,
    32,32,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,30,
    30,30,30,30,30,30,30,30,30,30,
    30,30,30,30,30,30,30,30,29,29,
    29,29,29,29,29,29,29,29,29,29,
    29,29,29,29,29,29,29,28,28,28,
    28,28,28,28,28,28,28,28,28,28,
    28,28,28,28,28,28,28,27,27,27,
    27,27,27,27,27,27,27,27,27,27,
    27,27,27,27,27,27,27,27,26,26,
    26,26,26,26,26,26,26,26,26,26,
    26,26,26,26,26,26,26,26,26,26,
    26,25,25,25,25,25,25,25,25,25,
    25,25,25,25,25,25,25,25,25,25

};
s32 value2[]=
{
    1163,1111,1064,1020,980,943,909,877,833,806,
    769,735,704,676,649,625,595,575,549,526,
    500,481,459,439,420,400,385,368,350,336,
    321,305,292,279,266,255,244,233,222,212,
    202,194,185,177,169,161,154,147,141,135,
    129,123,118,113,108,103,98,94,90,86,
    83,79,76,73,70,67,64,61,59,57,
    54,52,50,48,46,45,43,41,40,38,
    37,36,34,33,32,31,30,29,28,27,
    26,26,25,24,23,23,22,22,21,20,
    20,19,19,19,18,18,17,17,17,16,
    16,16,15,15,15,15,14,14,14,14,
    14,13,13,13,13,13,13,13,12,12,
    12,12,12,12,12,12,12,12,11,11,
    11,11,11,11,11,11,11,11,11,11,
    11,11,11,11,11,11,11,11,11,11,
    10,10,10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,10,10
};

void speed_up(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{
    int Count;

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);

    for(Count = 0; Count<240; Count++)//¼ÓËÙ
    {
        Speed0=value[Count];
        Speed1=value[Count];
        Speed2=value[Count];
        Speed3=value[Count];
        delay_ms(4);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }
}
void speed_up3(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{
    int Count;

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);

    for(Count = 0; Count<510; Count++)//¼ÓËÙ
    {
        Speed0=value1[Count];
        Speed1=value1[Count];
        Speed2=value1[Count];
        Speed3=value1[Count];
        delay_ms(4);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }
}
void speed_up1(int count,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{   int Count;
    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);

    for(Count = 0; Count<count; Count++)//¼ÓËÙ
    {
        Speed0=value[Count];
        Speed1=value[Count];
        Speed2=value[Count];
        Speed3=value[Count];
        delay_us(2);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }
}
void speed_up2(int count,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{   int Count;
    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);

    for(Count = 0; Count<count; Count++)//¼ÓËÙ
    {
        Speed0=value[Count];
        Speed1=value[Count];
        Speed2=value[Count];
        Speed3=value[Count];
        delay_us(2);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }
}
void speed_down(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{
    int Count;

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);

    for(Count = 239; Count>=0; Count--)//¼õËÙ
    {
        Speed0=value[Count];
        Speed1=value[Count];
        Speed2=value[Count];
        Speed3=value[Count];
        delay_us(100);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }


}
void speed_down3(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{
    int Count;

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);

    for(Count = 505; Count>=0; Count--)//¼õËÙ
    {
        Speed0=value1[Count];
        Speed1=value1[Count];
        Speed2=value1[Count];
        Speed3=value1[Count];
        delay_ms(3);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }


}
void speed_down1(int count,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{
    int Count;

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);

    for(Count = count; Count>=0; Count--)//¼õËÙ
    {
        Speed0=value[Count];
        Speed1=value[Count];
        Speed2=value[Count];
        Speed3=value[Count];
        delay_ms(2);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }


}
void run2(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{   int Count;

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);


    for(Count = 29; Count>=0; Count--)//¼õËÙ
    {
        Speed0=value1[Count];
        Speed1=value1[Count];
        Speed2=value1[Count];
        Speed3=value1[Count];
        delay_ms(30);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }

}
void run1(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{   int Count;

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);


    for(Count = 0; Count<30; Count++)//¼ÓËÙ
    {
        Speed0=value1[Count];
        Speed1=value1[Count];
        Speed2=value1[Count];
        Speed3=value1[Count];
        delay_ms(30);

        SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
        SetpMotor_SetSpeed(1,Speed1);
        SetpMotor_SetSpeed(2,Speed2);
        SetpMotor_SetSpeed(3,Speed3);
    }

}

void run(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{

    SetpMotor_SetStep(0,step0);	//  motor[id].target=motor[0].step+steps*2;
    SetpMotor_SetStep(1,step1);
    SetpMotor_SetStep(2,step2);
    SetpMotor_SetStep(3,step3);


    SetpMotor_SetSpeed(0,Speed0);	// motor[id].div=speed;
    SetpMotor_SetSpeed(1,Speed1);
    SetpMotor_SetSpeed(2,Speed2);
    SetpMotor_SetSpeed(3,Speed3);


}
void left_run(s32 step)
{   int corr;
    speed_up(step,45,-step,45,step,45,-step,45);
    Correct_or();
    run(10000,35,-10000,35,10000,35,-10000,35);
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {
        if(PFin(5)==0)
        {   delay_ms(5);
            {   if(PFin(5)==0)
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
    }
    run(1500,35,-1500,35,1500,35,-1500,35);
    Correct_or();
    speed_down(350,45,-350,45,350,45,-350,45);
}
void left_run1(s32 step)
{   int corr;
    speed_up(step,45,-step,45,step,45,-step,45);
    Correct_or();
    run(10000,35,-10000,35,10000,35,-10000,35);
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {
        if(PFin(5)==0)
        {   delay_ms(5);
            {   if(PFin(5)==0)
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
    }
    run(1200,35,-1200,35,1200,35,-1200,35);
    Correct_or();
    speed_down(350,45,-350,45,350,45,-350,45);
}
void left_run2(s32 step)
{   int corr; 
    speed_up(step,45,-step,45,step,45,-step,45);
    Correct_or();
    run(10000,35,-10000,35,10000,35,-10000,35);
    if(motor[0].target!=motor[0].step) corr=1;
    while(corr)
    {
        if(PFin(6)==0)
        {   delay_ms(5);
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
    }
    run(1200,35,-1200,35,1200,35,-1200,35);
    Correct_or();
    speed_down(200,45,-200,45,200,45,-200,45);
}
void auto_trans(int x)
{   int corr=1;
    s32 step;float L,R;
    if(x==0)
    {
        while(corr)
        {
            delay_ms(6);
            UWaveBackRight_Send();
            if(BackRight_dist>=0&&BackRight_dist<=400)
            {   delay_ms(6);
                UWaveBackRight_Send();
                if(BackRight_dist>=0&&BackRight_dist<=400)
                {   UWaveBackRight_Send();
                    delay_ms(6);
                    if(BackRight_dist>=30&&BackRight_dist<=400)
                    {
                        step=(BackRight_dist-30)*5;
                        speed_up1(200,step,75,step,75,-step,75,-step,75);
                        Correct_or();
                        if(BackRight_dist>=30&&BackRight_dist<=70)
                        {
                            corr=0;
                        }
                    }
                    if(BackRight_dist<30)
                    {
                        speed_up1(200,-80,95,-80,95,80,95,80,95);
                        Correct_or();
                        //corr=0;
                    }
                }
            }
        }
        /*speed_up1(200,300,95,300,95,-300,95,-300,95);
                        Correct_or();corr=0;}*/
    }
    if(x==1)
    {
        while(corr)
        {
            /*   delay_ms(6);
               UWaveCenter_Send();
               if(Front_dist>25&&Front_dist<200)
               {
                   step=(Front_dist-80)*3.6;
                   speed_up1(200,-step,95,-step,95,step,95,step,95);
                   Correct_or();
                   if(Front_dist>70&&Front_dist<80)
                   {
                       corr=0;
                   }
               }
               if(Front_dist<40||Front_dist>400)
               {
                   speed_up1(200,90,95,90,95,-90,95,-90,95);
                   Correct_or();
                   corr=0;
               }*/
            delay_ms(6);
            UWaveCenter_Send();
            if(Front_dist>=0&&Front_dist<=400)
            {   delay_ms(6);
                UWaveCenter_Send();
                if(Front_dist>=0&&Front_dist<=400)
                {
                    if(Front_dist>=30&&Front_dist<=400)
                    {
                        step=(Front_dist-80)*3.6;
                        speed_up1(200,-step,75,-step,75,step,75,step,75);
                        Correct_or();
                        if(Front_dist>=30&&Front_dist<=95)
                        {
                            corr=0;
                        }
                    }
                    if(Front_dist<30)
                    {
                        speed_up1(200,50,95,50,95,-50,95,-50,95);
                        Correct_or();
                    }
                }
            }
        }
    }
    if(x==2)
    {   while(corr)
        {
            delay_ms(6);
            UWaveBackLeft_Send();
            UWaveBackRight_Send();
            if(BackLeft_dist>=0&&BackLeft_dist<=400)
            {
                delay_ms(6);
                UWaveBackLeft_Send();
                UWaveBackRight_Send();
                if(BackRight_dist>=0&&BackRight_dist<=400)
                {       if(BackRight_dist>80&&BackLeft_dist>90)
                   {   step=(BackRight_dist-40)*1.2;
                       speed_up1(200,step,95,step,95,-step,95,-step,95);
                       Correct_or();  
                   }
                   if(BackRight_dist<40&&BackLeft_dist<50)
                   {   if((BackRight_dist-BackLeft_dist)>20)
                       {
                       step=(50-BackLeft_dist)*1.2;
                       speed_up1(200,step,95,step,95,step,95,step,95);
                       Correct_or(); 
                       }else
                       {
                       speed_up1(200,-step,95,-step,95,-step,95,-step,95);
                       Correct_or();  
                       }
                       step=(40-BackRight_dist)*1.2;
                       speed_up1(200,-step,95,-step,95,step,95,step,95);
                       Correct_or();  
                   }
                    delay_ms(6);
                    UWaveBackLeft_Send();
                    UWaveBackRight_Send();
                    if(BackLeft_dist>=50&&BackLeft_dist<=90)
                    {
                        delay_ms(6);
                        UWaveBackLeft_Send();
                        UWaveBackRight_Send();
                        if(BackRight_dist>=40&&BackRight_dist<=80)
                        {   L=BackLeft_dist;R=BackRight_dist;
                            if((L>(R-10))&&(L<(R+5))){corr=0;}
                            if(L>R)
                            {
                                step=(L-R)*0.9;
                                //if(step<25)step=25;
                                speed_up1(200,step,95,step,95,step,95,step,95);
                                Correct_or();
                                
                            }
                            if(R>L)
                            {
                                step=(R-L)*0.9;
                                //if(step<25)step=25;
                                speed_up1(200,-step,95,-step,95,-step,95,-step,95);
                                Correct_or();
                                
                            }
                        }
                    }
                    L=BackLeft_dist;R=BackRight_dist;
                    if((L-R)>40)
                    {
                                step=(L-R)*0.9;
                                speed_up1(200,step,95,step,95,step,95,step,95);
                                Correct_or();
                    }
                    if((R-L)>40)
                    {
                                step=(R-L)*0.9;
                                speed_up1(200,-step,95,-step,95,-step,95,-step,95);
                                Correct_or();
                    }
                }
            }
        }
    }
}
void Self_tuning(int x,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3)
{   int num=0,f,num1=0,num2=0;
    int corr;
    s32 step;
    s32 loa_Speed=95;
    int flag=0;
    //printf("¿ªÊ¼µ÷½Ú\r\n");
    while(1)
    {
        if(PFin(1)==0&&PFin(2)==1&&PFin(3)==0&&PFin(4)==1)//1ÁÁ2Ãð3ÁÁ4Ãð
        {   //printf("ÓÒ´ó×óÐ¡£¬ÐèÒªÕýÐý\r\n");
            speed_up1(200,-160,loa_Speed,-160,loa_Speed,-160,loa_Speed,-160,loa_Speed);
            Correct_or();
            /*speed_down1(200,-30,loa_Speed,-30,loa_Speed,-30,loa_Speed,-30,loa_Speed);
            Correct_or();*/
            f=0;
        }
////////////////////////
        if(PFin(1)==0&&PFin(2)==1&&PFin(3)==1&&PFin(4)==0)//1ÁÁ2Ãð3Ãð4ÁÁ
        {
            printf("×óÒÆ\r\n");
            UWaveRight_Send();
            delay_ms(12);
            step=(Right_dist-110)*5.6;
            //printf("%f\r\n",Right_dist);
            //printf("%d\r\n",step);
            if(Right_dist>=110&&Right_dist<=250)
            {   speed_up1(200,step,loa_Speed,-step,loa_Speed,step,loa_Speed,-step,loa_Speed);
                Correct_or();
                /*speed_down1(200,35,loa_Speed,-35,loa_Speed,35,loa_Speed,-35,Speed3);
                Correct_or();*/
            }
            else {
                speed_up1(200,80,loa_Speed,-80,loa_Speed,80,loa_Speed,-80,loa_Speed);
                Correct_or();
                /*speed_down1(200,35,loa_Speed,-35,loa_Speed,35,loa_Speed,-35,loa_Speed);
                Correct_or();*/
            }
            if(f==3) {
                num++;
            }
            f=1;

        }
////////////////////////
        if(PFin(1)==1&&PFin(2)==0&&PFin(3)==1&&PFin(4)==0)//1Ãð2ÁÁ3Ãð4ÁÁ
        {   //printf("×ó´óÓÒÐ¡£¬ÐèÒªÄæÐý\r\n");
            speed_up1(200,160,loa_Speed,160,loa_Speed,160,loa_Speed,160,loa_Speed);
            Correct_or();
            f=2;

        }
/////////////////
        if(PFin(1)==1&&PFin(2)==0&&PFin(3)==0&&PFin(4)==1)//1Ãð2ÁÁ3ÁÁ4Ãð
        {
            //printf("ÓÒÒÆ\r\n");
            UWaveLeft_Send();
            delay_ms(12);
            step=(Left_dist-115)*5.6;
            //printf("%f\r\n",Left_dist);
            //printf("%d\r\n",step);
            if(Left_dist>=110&&Left_dist<=250)
            {   speed_up1(200,-step,loa_Speed,step,loa_Speed,-step,loa_Speed,step,loa_Speed);
                Correct_or();
                /*speed_down1(200,-35,loa_Speed,35,loa_Speed,-35,loa_Speed,35,loa_Speed);
                Correct_or();*/
            }
            else {
                speed_up1(200,-80,loa_Speed,80,loa_Speed,-80,loa_Speed,80,loa_Speed);
                Correct_or();
                /*speed_down1(200,-35,loa_Speed,35,loa_Speed,-35,loa_Speed,35,loa_Speed);
                Correct_or();*/
            }
            if(f==1) {
                num++;
            }
            f=3;

        }
/////////////////
        if(PFin(1)==0&&PFin(2)==0&&PFin(3)==0&&PFin(4)==0)//1ÁÁ2ÁÁ3ÁÁ4ÁÁ
        {   delay_ms(25);
            if(PFin(1)==0&&PFin(2)==0&&PFin(3)==0&&PFin(4)==0)
            {   delay_ms(25);
                if(PFin(1)==0&&PFin(2)==0&&PFin(3)==0&&PFin(4)==0)
                {        
                    //printf("Ð£×¼/r/n");
                    if(x==0)
                    { 
                        speed_up3(6000,25,6000,25,-6000,25,-6000,25);
                        Correct_or();
                        run(step0,25,step1,25,step2,25,step3,25);
                        if(motor[0].target!=motor[0].step) {
                            corr=1;
                        }
                        while(corr)
                        {
                            if(PFin(1)==1&&PFin(2)==1)
                            {   delay_ms(10);
                                {   if(PFin(1)==1&&PFin(2)==1)
                                    {   delay_ms(10);
                                        if(PFin(1)==1&&PFin(2)==1)
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
                        }
                         run(200,30,200,30,-200,30,-200,30);
                         Correct_or();
                         run(200,35,200,35,-200,35,-200,35);
                         Correct_or(); 
                         run(200,40,200,40,-200,40,-200,40);
                         Correct_or(); 
                         run(200,43,200,43,-200,43,-200,43);
                         Correct_or(); 
                        run(7000,45,7000,45,-7000,45,-7000,45);
                        back_stop();
                        f=4;
                        speed_down(350,45,350,45,-350,45,-350,45);
                        //Correct_or();
                        break;
                    }
                    if(x==1)
                    {    
                         speed_up3(-6000,25,-6000,25,6000,25,6000,25);
                         Correct_or(); 
                        run(step0,25,step1,25,step2,25,step3,25);
                        if(motor[0].target!=motor[0].step) {
                            corr=1;
                        }
                        while(corr)
                        {
                            if(PFin(3)==1&&PFin(4)==1)
                            {   delay_ms(10);
                                {   if(PFin(3)==1&&PFin(4)==1)
                                    {   delay_ms(10);
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
                        }
                         run(-200,30,-200,30,200,30,200,30);
                         Correct_or();
                         run(-200,35,-200,35,200,35,200,35);
                         Correct_or(); 
                         run(-200,40,-200,40,200,40,200,40);
                         Correct_or(); 
                         run(-200,43,-200,43,200,43,200,43);
                         Correct_or();     
                        run(-7000,45,-7000,45,7000,45,7000,45);
                        front_stop();
                        f=4;
                        speed_down(-350,45,-350,45,350,45,350,45);
                        //Correct_or();
                        break;
                    }
                    if(x==2)
                    {
                        speed_up3(2600,25,2600,25,-2600,25,-2600,25);
                        Correct_or();
                        run(step0,25,step1,25,step2,25,step3,25);
                        f=4;
                        Correct_or();
                        speed_down3(250,25,250,25,-250,25,-250,25);
                        break;
                    }
                }
            }
        }
/////////////////
        if(PFin(1)==1&&PFin(2)==0&&PFin(3)==0&&PFin(4)==0)//1Ãð2ÁÁ3ÁÁ4ÁÁ
        {   delay_ms(10);
            if(PFin(1)==1&&PFin(2)==0&&PFin(3)==0&&PFin(4)==0)//1Ãð2ÁÁ3ÁÁ4ÁÁ
            {
                if(flag<5)
                {   /*UWaveRight_Send();
                    delay_ms(12);
                    UWaveLeft_Send();
                    delay_ms(12);
                    if(Right_dist>=90&&Right_dist<=105)
                    {
                        if(Left_dist>=115&&Left_dist<=125)
                        {
                            printf("ÓÒÒÆ\r\n");
                            speed_up1(200,-80,loa_Speed,80,loa_Speed,-80,loa_Speed,80,loa_Speed);
                            Correct_or();
                        }
                    } else {*/
                    //printf("ÐèÒªÄæÐý\r\n");
                    speed_up1(200,56,loa_Speed,56,loa_Speed,56,loa_Speed,56,loa_Speed);
                    Correct_or();
                    /*speed_down1(200,16,loa_Speed,16,loa_Speed,16,loa_Speed,16,loa_Speed);
                    Correct_or();*/

                    if(f==8) {
                        num1++;
                        //printf("num1=%d\r\n",num1);
                    }
                    //}
                    f=5;
                    flag++;
                }
            }
        }

////////
        if(PFin(1)==0&&PFin(2)==1&&PFin(3)==0&&PFin(4)==0)//1ÁÁ2Ãð3ÁÁ4ÁÁ
        {   delay_ms(10);
            if(PFin(1)==0&&PFin(2)==1&&PFin(3)==0&&PFin(4)==0)//1ÁÁ2Ãð3ÁÁ4ÁÁ
            {
                if(flag<5)
                {   /*UWaveRight_Send();
                    delay_ms(12);
                    UWaveLeft_Send();
                    delay_ms(12);
                    if(Left_dist>=90&&Left_dist<=105)
                    {
                        if(Right_dist>=115&&Right_dist<=125)
                        {
                            printf("×óÒÆ\r\n");
                            speed_up1(200,80,loa_Speed,-80,loa_Speed,80,loa_Speed,-80,loa_Speed);
                            Correct_or();
                        }
                    } else {*/
                    //printf("ÐèÒªÕýÐý\r\n");
                    speed_up1(200,-56,loa_Speed,-56,loa_Speed,-56,loa_Speed,-56,loa_Speed);
                    Correct_or();
                    /*speed_down1(200,-16,loa_Speed,-16,loa_Speed,-16,loa_Speed,-16,loa_Speed);
                    Correct_or();*/
                    if(f==7) {
                        num2++;
                        //printf("num2=%d\r\n",num2);
                    }
                    //}
                    f=6;
                    flag++;
                }
            }
        }
////////
        if(PFin(1)==0&&PFin(2)==0&&PFin(3)==1&&PFin(4)==0)//1ÁÁ2ÁÁ3Ãð4ÁÁ
        {   delay_ms(10);
            if(PFin(1)==0&&PFin(2)==0&&PFin(3)==1&&PFin(4)==0)//1ÁÁ2ÁÁ3Ãð4ÁÁ
            {
                if(flag<5)
                {   /*UWaveRight_Send();
                    delay_ms(12);
                    UWaveLeft_Send();
                    delay_ms(12);
                    if(Left_dist>=90&&Left_dist<=105)
                    {
                        if(Right_dist>=115&&Right_dist<=125)
                        {
                            printf("×óÒÆ\r\n");
                            speed_up1(200,80,loa_Speed,-80,loa_Speed,80,loa_Speed,-80,loa_Speed);
                            Correct_or();
                        }
                    } else {*/
                    printf("ÐèÒªÄæÐý\r\n");
                    speed_up1(200,56,loa_Speed,56,loa_Speed,56,loa_Speed,56,loa_Speed);
                    Correct_or();
                    /*speed_down1(200,16,loa_Speed,16,loa_Speed,16,loa_Speed,16,loa_Speed);
                    Correct_or();*/

                    if(f==6) {
                        num2++;
                        //printf("num2=%d\r\n",num2);
                    }
                    //}
                    f=7;
                    flag++;
                }
            }
        }
////////
        if(PFin(1)==0&&PFin(2)==0&&PFin(3)==0&&PFin(4)==1)//1ÁÁ2ÁÁ3ÁÁ4Ãð
        {   delay_ms(10);
            if(PFin(1)==0&&PFin(2)==0&&PFin(3)==0&&PFin(4)==1)//1ÁÁ2ÁÁ3ÁÁ4Ãð
            {
                if(flag<5)
                {   /*UWaveRight_Send();
                    delay_ms(12);
                    UWaveLeft_Send();
                    delay_ms(12);
                    if(Right_dist>=90&&Right_dist<=105)
                    {
                        if(Left_dist>=115&&Left_dist<=125)
                        {
                            printf("ÓÒÒÆ\r\n");
                            speed_up1(200,-80,loa_Speed,80,loa_Speed,-80,loa_Speed,80,loa_Speed);
                            Correct_or();
                        }
                    } else {*/
                    //printf("ÐèÒªÕýÐý\r\n");
                    speed_up1(200,-56,loa_Speed,-56,loa_Speed,-56,loa_Speed,-56,loa_Speed);
                    Correct_or();
                    /*speed_down1(200,-16,loa_Speed,-16,loa_Speed,-16,loa_Speed,-16,loa_Speed);
                    Correct_or();*/
                    if(f==5) {
                        num1++;
                        //printf("num1=%d\r\n",num1);
                    }
                    //}
                    f=8;
                    flag++;
                }
            }
        }
//////////////////
        if(flag==5)
        {   
            if(x==0)
            { 
                        speed_up3(6000,25,6000,25,-6000,25,-6000,25);
                        Correct_or();
                        run(step0,25,step1,25,step2,25,step3,25);
                        if(motor[0].target!=motor[0].step) {
                            corr=1;
                        }
                        while(corr)
                        {
                            if(PFin(1)==1&&PFin(2)==1)
                            {   delay_ms(10);
                                {   if(PFin(1)==1&&PFin(2)==1)
                                    {   delay_ms(10);
                                        if(PFin(1)==1&&PFin(2)==1)
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
                        }
                         run(200,30,200,30,-200,30,-200,30);
                         Correct_or();
                         run(200,35,200,35,-200,35,-200,35);
                         Correct_or(); 
                         run(200,40,200,40,-200,40,-200,40);
                         Correct_or(); 
                         run(200,43,200,43,-200,43,-200,43);
                         Correct_or(); 
                        run(7000,45,7000,45,-7000,45,-7000,45);
                        back_stop();
                        f=4;
                        speed_down(350,45,350,45,-350,45,-350,45);
                        //Correct_or();
                        break;
                    }
            if(x==1)
            {    
                         speed_up3(-6000,25,-6000,25,6000,25,6000,25);
                         Correct_or(); 
                        run(step0,25,step1,25,step2,25,step3,25);
                        if(motor[0].target!=motor[0].step) {
                            corr=1;
                        }
                        while(corr)
                        {
                            if(PFin(3)==1&&PFin(4)==1)
                            {   delay_ms(10);
                                {   if(PFin(3)==1&&PFin(4)==1)
                                    {   delay_ms(10);
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
                        }
                         run(-200,30,-200,30,200,30,200,30);
                         Correct_or();
                         run(-200,35,-200,35,200,35,200,35);
                         Correct_or(); 
                         run(-200,40,-200,40,200,40,200,40);
                         Correct_or(); 
                         run(-200,43,-200,43,200,43,200,43);
                         Correct_or();     
                        run(-7000,45,-7000,45,7000,45,7000,45);
                        front_stop();
                        f=4;
                        speed_down(-350,45,-350,45,350,45,350,45);
                        //Correct_or();
                        break;
                    }
            if(x==2)
            {
                speed_up3(2600,25,2600,25,-2600,25,-2600,25);
                Correct_or();
                run(step0,25,step1,25,step2,25,step3,25);
                f=4;
                Correct_or();
                speed_down3(200,25,200,25,-200,25,-200,25);
                break;
            }
        }
//////////////////
        /*        if(num==3)
                {
                    num=0;
                    printf("°Ú\r\n");
                    speed_up(-160,Speed0,160,Speed1,-160,Speed2,160,Speed3);
                    Correct_or();
                    speed_up(-160,Speed0,-160,Speed1,160,Speed2,160,Speed3);
                    Correct_or();
                }
                if(num1==3)
                {
                    num1=0;
                    printf("°Ú1\r\n");
                     speed_up(-80,Speed0,80,Speed1,-80,Speed2,80,Speed3);
                            Correct_or();
                }
                if(num2==3)
                {
                    num2=0;
                    printf("°Ú2\r\n");
                    speed_up(80,Speed0,-80,Speed1,80,Speed2,-80,Speed3);
                    Correct_or();
                }*/
/////////////
    }
}
