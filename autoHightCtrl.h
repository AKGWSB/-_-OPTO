#ifndef __AUTOHIGHTCTRL_H_

#define __AUTOHIGHTCTRL_H_

#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

typedef struct
{
	int modFlag;
	
	float speed_z;
	float hight;
	float acc_z;
	
	float hightTarget;
	float err_hight;
	float speedTarget;
	float err_speed;
	double err_sum_speed;
	float err_speed_last;
	float err_d_speed;
	float output;
	
}hightCtrl_DataStruct;

//-------------------------------------------//

//�������ݳ�ʼ��
void hightCtrl_DataInit();

//�������ݽӿ�
void hightCtrl_GetData_2ms_(float hight, float speed_z, float acc_z);

//�����������
float hightCtrlOutput_2ms_();

//-------------------------------------------//

//ģʽ״̬��־λ�ӿ�
int hightCtrl_GetModeFlag();

//ת�����ģʽ
void hightCtrl_ChangeTo_TakeOff();

//ת������ģʽ
void hightCtrl_ChangeTo_Down();

//ת������ģʽ
void hightCtrl_ChangeTo_Stay();

//ת������ģʽ
void hightCtrl_ChangeTo_Ready();

#endif
