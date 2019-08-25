#include <postureCtrl.h>
#include "L_math.h"
#include <posXYCtrl.h>
#include <flyTask.h>

postureCtrl_DataStruct postureCtrlData;

//init
void postureCtrl_Init()
{
	//��̬��
	//postureCtrlData.YAW = 0;
	postureCtrlData.PITCH = 0;
	postureCtrlData.ROLL = 0;
		
	//Ŀ��Ƕ�
	postureCtrlData.target_angle_PITCH = 0;
	postureCtrlData.target_angle_ROLL = 0;
	//postureCtrlData.target_angle_YAW = 0;
	
	//�Ƕ����
	postureCtrlData.err_angle_PITCH = 0;
	postureCtrlData.err_angle_ROLL = 0;
	postureCtrlData.err_angle_YAW = 0;

	//������ٶ�	
	postureCtrlData.angle_speed_YAW = 0;
	postureCtrlData.angle_speed_PITCH = 0;
	postureCtrlData.angle_speed_ROLL = 0;
	
	postureCtrlData.last_angle_speed_PITCH = 0;
	postureCtrlData.last_angle_speed_ROLL = 0;
	postureCtrlData.last_angle_speed_YAW = 0;
	
	//Ŀ����ٶ�
	postureCtrlData.target_angleSpeed_YAW = 0;
	postureCtrlData.target_angleSpeed_PITCH = 0;
	postureCtrlData.target_angleSpeed_ROLL = 0;

	//���ٶ����
	postureCtrlData.err_angleSpeed_YAW = 0;
	postureCtrlData.err_angleSpeed_PITCH = 0;
	postureCtrlData.err_angleSpeed_ROLL = 0;
	
	//���ٶ�������
	postureCtrlData.errSum_angleSpeed_YAW = 0;
	postureCtrlData.errSum_angleSpeed_PITCH = 0;
	postureCtrlData.errSum_angleSpeed_ROLL = 0;
	
	//���������
	postureCtrlData.outPITCH = 0;
	postureCtrlData.outROLL = 0;
	postureCtrlData.outYAW = 0;
}


//��̬���ƻ�ȡ����--����:�����ںϽǶ�,���ٶ�
void postureCtrl_GetData_2ms_(float PITCH, float ROLL, float YAW, float angleSpeed_PITCH, float angleSpeed_ROLL, float angleSpeed_YAW)
{
	postureCtrlData.YAW = YAW;
	postureCtrlData.PITCH = PITCH;
	postureCtrlData.ROLL = ROLL;
	
	postureCtrlData.angle_speed_YAW = angleSpeed_YAW;
	postureCtrlData.angle_speed_PITCH = angleSpeed_PITCH;
	postureCtrlData.angle_speed_ROLL = angleSpeed_ROLL;
}


//��̬�����ĵ�����--����:
// 2 1 :��ͷ��
// 3 4 :������
void postureCtrl_Out4Moto_2ms_(float* moto)
{
	//����Ƕ����
	postureCtrlData.err_angle_PITCH = postureCtrlData.target_angle_PITCH + flyTask_TargetAngleOut_Pitch() - postureCtrlData.PITCH;
	postureCtrlData.err_angle_ROLL = postureCtrlData.target_angle_ROLL + flyTask_TargetAngleOut_Roll() - postureCtrlData.ROLL;
	postureCtrlData.err_angle_YAW = postureCtrlData.target_angle_YAW + flyTask_TargetAngleOut_Yaw() - postureCtrlData.YAW;
	
	//�õ�Ŀ����ٶ�
	postureCtrlData.target_angleSpeed_PITCH = postureCtrlData.err_angle_PITCH * 43;
	postureCtrlData.target_angleSpeed_ROLL = postureCtrlData.err_angle_ROLL * 43;
	postureCtrlData.target_angleSpeed_YAW = postureCtrlData.err_angle_YAW * 33;
	
	//������ٶ����
	postureCtrlData.err_angleSpeed_PITCH = postureCtrlData.target_angleSpeed_PITCH - postureCtrlData.angle_speed_PITCH;
	postureCtrlData.err_angleSpeed_ROLL = postureCtrlData.target_angleSpeed_ROLL - postureCtrlData.angle_speed_ROLL;
	postureCtrlData.err_angleSpeed_YAW = postureCtrlData.target_angleSpeed_YAW - postureCtrlData.angle_speed_YAW;
	
	//���ٶ�������
	postureCtrlData.errSum_angleSpeed_PITCH += postureCtrlData.err_angleSpeed_PITCH * 0.002;
	postureCtrlData.errSum_angleSpeed_ROLL += postureCtrlData.err_angleSpeed_ROLL * 0.002;
	postureCtrlData.errSum_angleSpeed_YAW += postureCtrlData.err_angleSpeed_YAW * 0.002;
	
	//���ٶ��������޷�
	postureCtrlData.errSum_angleSpeed_PITCH = LIMIT(postureCtrlData.errSum_angleSpeed_PITCH, 0, 4000);
	postureCtrlData.errSum_angleSpeed_ROLL = LIMIT(postureCtrlData.errSum_angleSpeed_ROLL, 0, 4000);
	postureCtrlData.errSum_angleSpeed_YAW = LIMIT(postureCtrlData.errSum_angleSpeed_YAW, 0, 4000);
	
	//ֱ�Ӳ�ּ���Ǽ��ٶ�
	float accPITCH = postureCtrlData.angle_speed_PITCH - postureCtrlData.last_angle_speed_PITCH;
	float accROLL = postureCtrlData.angle_speed_ROLL - postureCtrlData.last_angle_speed_ROLL;
	float accYAW = postureCtrlData.angle_speed_YAW - postureCtrlData.last_angle_speed_YAW;
		
	//�����ϴν��ٶ�
	postureCtrlData.last_angle_speed_PITCH = postureCtrlData.angle_speed_PITCH;
	postureCtrlData.last_angle_speed_ROLL = postureCtrlData.angle_speed_ROLL;
	postureCtrlData.last_angle_speed_YAW = postureCtrlData.angle_speed_YAW;
	
	moto[0] = 0;
	moto[1] = 0;
	moto[2] = 0;
	moto[3] = 0;
	
	//���㸩�����--Ŀ��Ƕ�Ϊ�����12+ , 34-
	postureCtrlData.outPITCH = postureCtrlData.err_angleSpeed_PITCH * 0.0964 + postureCtrlData.errSum_angleSpeed_PITCH * 0.3933 - accPITCH*4.7;
	postureCtrlData.outPITCH = LIMIT(postureCtrlData.outPITCH, -80, 80);
	moto[0] += postureCtrlData.outPITCH;
	moto[1] += postureCtrlData.outPITCH;
	moto[2] += -1*postureCtrlData.outPITCH;
	moto[3] += -1*postureCtrlData.outPITCH;
	
	//���������--Ŀ��Ƕ�Ϊ�����23+ , 14-
	postureCtrlData.outROLL = postureCtrlData.err_angleSpeed_ROLL * 0.0965 + postureCtrlData.errSum_angleSpeed_ROLL * 0.3933 - accROLL*4.7;
	postureCtrlData.outROLL = LIMIT(postureCtrlData.outROLL, -80, 80);
	moto[0] += -1*postureCtrlData.outROLL;
	moto[1] += postureCtrlData.outROLL;
	moto[2] += postureCtrlData.outROLL;
	moto[3] += -1*postureCtrlData.outROLL;
	
	//����ƫ�����
	postureCtrlData.outYAW = postureCtrlData.err_angleSpeed_YAW * 0.64 + postureCtrlData.errSum_angleSpeed_YAW * 0.0016 -  accYAW*0.16;
	postureCtrlData.outYAW = LIMIT(postureCtrlData.outYAW, -80, 80);
	moto[0] += postureCtrlData.outYAW;
	moto[1] += -1*postureCtrlData.outYAW;
	moto[2] += postureCtrlData.outYAW;
	moto[3] += -1*postureCtrlData.outYAW;
}




