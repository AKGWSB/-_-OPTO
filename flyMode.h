#include <L_Link.h>

#ifndef __FLYMOD_H__

#define __FLYMOD_H__

typedef enum 
{
	Mode_Lock,
	Mode_Ready,
	Mode_AutoHightCtrl_TakeOff,
	Mode_AutoHightCtrl_Down,
	Mode_AutoTrace,
	Mode_mod1,
	Mode_mod2
}ModeEnum;

typedef struct
{
	float thr_out[4];
	ModeEnum Mode;
	
}flyMode_DataStruct;

//init
void flyMode_Init();

//�л�������ģʽ
void flyMode_ChangeTo_Lock();

//�л�������ģʽ
void flyMode_ChangeTo_Ready();

//�л�������ģʽ-���
void flyMode_ChangeTo_AutoHightCtrl_TakeOff();

//�л�������ģʽ-����
void flyMode_ChangeTo_AutoHightCtrl_Down();

//�л�������ģʽ
void flyMode_ChangeTo_AutoTrace();

//
void flyMode_ChangeTo_mod1();

//
void flyMode_ChangeTo_mod2();

//���������,δ�޷�
void flyMode_Thr4Out_2ms_(float* thr);

//�õ���ǰģʽ
int flyMode_GetMode();

#endif





