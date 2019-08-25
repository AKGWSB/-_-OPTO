#ifndef __POSTURECTRL_H_

#define __POSTURECTRL_H_

#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

#define moto1 0
#define moto2 1
#define moto3 2
#define moto4 3

typedef   signed short     int int16_t;
typedef int16_t s16;

typedef struct
{
	//��̬��
	float YAW;
	float PITCH;
	float ROLL;
	
	//Ŀ��Ƕ�
	float target_angle_PITCH;
	float target_angle_ROLL;
	float target_angle_YAW;	
	float target_angle_ref;
	
	//�Ƕ����
	float err_angle_YAW;
	float err_angle_PITCH;
	float err_angle_ROLL;
	
	//������ٶ�
	float angle_speed_YAW;
	float angle_speed_PITCH;
	float angle_speed_ROLL;
	
	float last_angle_speed_PITCH;
	float last_angle_speed_ROLL;
	float last_angle_speed_YAW;
	
	//Ŀ����ٶ�
	float target_angleSpeed_YAW;
	float target_angleSpeed_PITCH;
	float target_angleSpeed_ROLL;
	
	//���ٶ����
	float err_angleSpeed_YAW;
	float err_angleSpeed_PITCH;
	float err_angleSpeed_ROLL;
	
	//���ٶ�������
	float errSum_angleSpeed_YAW;
	float errSum_angleSpeed_PITCH;
	float errSum_angleSpeed_ROLL;
	
	//���������
	float outPITCH;
	float outROLL;
	float outYAW;
	
}postureCtrl_DataStruct;

//init
void postureCtrl_Init();

//��̬���ƻ�ȡ����--����:�����ںϽǶ�,���ٶ�
void postureCtrl_GetData_2ms_(float PITCH, float ROLL, float YAW, float angleSpeed_PITCH, float angleSpeed_ROLL, float angleSpeed_YAW);

//��̬�����ĵ�����--����:
// 2 1 :��ͷ��
// 3 4 :������
void postureCtrl_Out4Moto_2ms_(float* moto);

#endif




