#include <L_Link.h>


#ifndef __FLYTASK_H__

#define __FLYTASK_H__

//״̬ö��
typedef enum 
{
	pointStay,		//����
	followLine,		//Ѱ��
	followLine2,
	left,					//����Ѱ��
	right,				//����Ѱ��
	forward,			//��ǰѰ��
	back,					//���Ѱ��
	back2,
	ctrlOff,			//������
	yawTurn	,			//ƫ������
	blindFly	,		//ä�ɹ���
	yawTurn2
}stateEnum;


//����ö��
typedef enum
{
	A,	//
	B,	//
	C,	//
	D,	//
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N
}taskEnum;

typedef struct 
{
	int timerCNT;
	stateEnum state;
	taskEnum task;
	postureAngle targetAngle;
	
	//λ�����ݽӿڣ����ݲ�ͬ����״̬�ı�λ������
	int posInterfaceX;
	int posInterfaceY;
	
	//�ٶ����ݽӿ�
	float speedInterfaceX;
	float speedInterfaceY;
	
}flyTask_DataStruct;


//init
void flyTast_Init();


//����������
void flyTask_CheckDuty_2ms_();


//�����������
void flyTask_AngleOutPutUpdate_2ms_();


//���Ŀ�긩����
float flyTask_TargetAngleOut_Pitch();


//���Ŀ������
float flyTask_TargetAngleOut_Roll();


//���Ŀ��ƫ����
float flyTask_TargetAngleOut_Yaw();


//�л�������
void flyTask_ChangeTo_pointStay();


//�л���Ѱ��
void flyTask_ChangeTo_followLine();


//�л���������
void flyTask_ChangeTo_ctrlOff();



#endif 
