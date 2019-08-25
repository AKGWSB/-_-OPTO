#ifndef __POSXYCTRL_H__

#define __POSXYCTRL_H__

#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

typedef struct 
{
	int posXYCtrlStartFlag;
	
	float posX;
	float posY;
	float targetSpeedX;
	float targetSpeedY;
	float speedX;
	float speedY;
	float err_speedX;
	float err_speedY;
	float target_roll;
	float target_pitch;
	short startFlag;
	
}posXYCtrl_DataStruct;

//init
void posXYCtrl_DataInit();

//λ�ÿ������ݽӿ�
void posXYCtrl_GetData_2ms_(float posX, float posY, float speedX, float speedY);

//�õ����Ŀ������
float posXYCtrl_outputTargetAngle_Roll();

//�õ����Ŀ�긩����
float posXYCtrl_outputTargetAngle_Pitch();

//����Ŀ��Ƕ�
void posXYCtrl_targetAngleCaculate_2ms_();

//��ʼ
void posXYCtrl_Start();

//����
void posXYCtrl_Eng();

#endif




