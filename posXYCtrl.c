#include <posXYCtrl.h>

posXYCtrl_DataStruct posXYCtrlData;

//init
void posXYCtrl_DataInit()
{
	posXYCtrlData.posXYCtrlStartFlag = 0;
	
	posXYCtrlData.posX = 0;
	posXYCtrlData.posY = 0;
	posXYCtrlData.targetSpeedX = 0;
	posXYCtrlData.targetSpeedY = 0;
	posXYCtrlData.speedX = 0;
	posXYCtrlData.speedY = 0;
	posXYCtrlData.err_speedX = 0;
	posXYCtrlData.err_speedY = 0;
	posXYCtrlData.target_roll = 0;
	posXYCtrlData.target_pitch = 0;
}


//λ�ÿ������ݽӿ�--����:posFilterData.posX_filter_value, -1*posFilterData.posY_filter_value, posFilterData.speedX_predict_value*0.0099, posFilterData.speedY_predict_value*0.0099
void posXYCtrl_GetData_2ms_(float posX, float posY, float speedX, float speedY)
{
	posXYCtrlData.posX = posX;
	posXYCtrlData.posY = posY;
	posXYCtrlData.speedX = speedX;
	posXYCtrlData.speedY = speedY;
}


//���Ŀ������
float posXYCtrl_outputTargetAngle_Roll()
{
	return posXYCtrlData.target_roll;
}


//���Ŀ�긩����
float posXYCtrl_outputTargetAngle_Pitch()
{
	return posXYCtrlData.target_pitch;
}

float last_err = 0;

//����Ŀ��Ƕ�--�⻷P�ڻ�P
void posXYCtrl_targetAngleCaculate_2ms_()
{
	//����Ŀ���ٶ�
	posXYCtrlData.targetSpeedX = 0.064 * (0 - posXYCtrlData.posX);
	posXYCtrlData.targetSpeedY = 0.121 * (0 - posXYCtrlData.posY);
//	
//	//����Ŀ���ٶ�
//	posXYCtrlData.targetSpeedX = 0;
//	posXYCtrlData.targetSpeedY = 0;
	
	//Ŀ���ٶ��޷�
	posXYCtrlData.targetSpeedX = LIMIT(posXYCtrlData.targetSpeedX, -5, 5);
	posXYCtrlData.targetSpeedY = LIMIT(posXYCtrlData.targetSpeedY, -5, 5);
	
	//�����ٶ����
	posXYCtrlData.err_speedX = posXYCtrlData.targetSpeedX - posXYCtrlData.speedX;
	posXYCtrlData.err_speedY = posXYCtrlData.targetSpeedY - posXYCtrlData.speedY;
	
	float err_d = posXYCtrlData.err_speedX - last_err;
	
	//����Ŀ��Ƕ�
	posXYCtrlData.target_roll = (posXYCtrlData.err_speedX)*1.4 + err_d*2.2;
	posXYCtrlData.target_pitch = (posXYCtrlData.err_speedY*-1);
	
	//Ŀ��Ƕ��޷�
	posXYCtrlData.target_roll = LIMIT(posXYCtrlData.target_roll, -6, 6);
	posXYCtrlData.target_pitch = LIMIT(posXYCtrlData.target_pitch, -5, 5);
	
	last_err = posXYCtrlData.err_speedX;
}


