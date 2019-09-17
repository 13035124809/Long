#ifndef __STEP_H
#define __STEP_H
#include "sys.h"







void speed_up(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void speed_up3(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void speed_up1(int count,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void speed_up2(int count,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void speed_down(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void speed_down3(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void speed_down1(int count,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void run(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void Self_tuning(int x,s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void run1(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void run2(s32 step0,s32 Speed0,s32 step1,s32 Speed1,s32 step2,s32 Speed2,s32 step3,s32 Speed3);
void left_run1(s32 step);
void left_run(s32 step);
void left_run2(s32 step);
void auto_trans(int x);






#endif




