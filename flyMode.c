#include "flyMode.h"

flyMode_DataStruct flyModeData;

//init
void flyMode_Init()
{
	flyModeData.thr_out[0] = 0;
	flyModeData.thr_out[1] = 0;
	flyModeData.thr_out[2] = 0;
	flyModeData.thr_out[3] = 0;
	
	//��������
	flyModeData.Mode = Mode_Lock;
}


//�л�������ģʽ
void flyMode_ChangeTo_Lock()
{
	flyModeData.Mode = Mode_Lock;
}


//�л�������ģʽ
void flyMode_ChangeTo_Ready()
{
	flyModeData.Mode = Mode_Ready;
}


//�л�������ģʽ-���
void flyMode_ChangeTo_AutoHightCtrl_TakeOff()
{
	flyModeData.Mode = Mode_AutoHightCtrl_TakeOff;
}


//�л�������ģʽ-����
void flyMode_ChangeTo_AutoHightCtrl_Down()
{
	flyModeData.Mode = Mode_AutoHightCtrl_Down;
}


//�л�������ģʽ
void flyMode_ChangeTo_AutoTrace()
{
	flyModeData.Mode = Mode_AutoTrace;
}


//
void flyMode_ChangeTo_mod1()
{
	flyModeData.Mode = Mode_mod1;
}


//
void flyMode_ChangeTo_mod2()
{
	flyModeData.Mode = Mode_mod2;
}


//���������,δ�޷�
void flyMode_Thr4Out_2ms_(float* thr)
{
	//---------------------------------------------------------//
	//���������״̬
	if(flyModeData.Mode == Mode_Lock)
	{
		for(int i=0; i<4; i++)
		{
			//�����
			hightCtrl_DataInit();
			postureCtrl_Init();
			thr[i] = 0;
		}
		return;
	}
	//---------------------------------------------------------//
	//����Ǿ���״̬
	else if(flyModeData.Mode == Mode_Ready)
	{
		//�����
		hightCtrl_DataInit();
		postureCtrl_Init();
		for(int i=0; i<4; i++)
		{
			thr[i] = 150;
		}
		//��¼��ǰƫ����
		postureCtrlData.target_angle_YAW = postureCtrlData.YAW;
		return;
	}
	//---------------------------------------------------------//
	//������Զ�����ģʽ-���
	else if(flyModeData.Mode == Mode_AutoHightCtrl_TakeOff)
	{
		if(hightCtrlData.hightTarget <= 1000)
		{
			hightCtrlData.hightTarget += 2.0;
		}
	}
	//---------------------------------------------------------//
	//������Զ�����ģʽ-����
	else if(flyModeData.Mode == Mode_AutoHightCtrl_Down)
	{
		if(hightCtrlData.hightTarget >= -440)
		{
			hightCtrlData.hightTarget -= 1.0;
		}
		
		//����Ѿ�����,�������߿���,��������
		if(hightCtrlData.hight < 250 && hightCtrlData.hightTarget <= -440)
		{
			//�������
			hightCtrl_DataInit();
			postureCtrl_Init();
			flyMode_ChangeTo_Lock();
			return;
		}
	}
	//---------------------------------------------------------//
	//�����ģʽ1
	else if(flyModeData.Mode == Mode_mod1)
	{
		
	}
	//---------------------------------------------------------//
	//�����ģʽ2
	else if(flyModeData.Mode == Mode_mod2)
	{
		
	}
	
	//---------------------------------------------------------//

	//���㶨�߿�������
	float thr_value = LIMIT(hightCtrlOutput_2ms_(), 0, 799);
		
	//������̬��������
	float posture_value[4];
	postureCtrl_Out4Moto_2ms_(posture_value);
		
	//����������
	float all_thr_ave = (posture_value[0]+posture_value[1]+posture_value[2]+posture_value[3])/4;
	for(int i=0; i<4; i++)
	{
		thr[i] = thr_value + LIMIT(posture_value[i], -200, 200) - all_thr_ave;
	}
}


//�õ���ǰģʽ
int flyMode_GetMode()
{
	return flyModeData.Mode;
}



