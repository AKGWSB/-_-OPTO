#include <remoterRecive.h>
#include "L_math.h"
#include "posFilter.h"

remoterRecive_DataStruct remoterReciveData;

//init
void remoterRecive_Init()
{
	remoterReciveData.Gyro_ref_flag = 0;
	remoterReciveData.all_out_ctrl = 1;
	
	remoterReciveData.isLock = 1;
	remoterReciveData.lockCounter = 0;
	
	remoterReciveData.remoterCorrectCounter = 0;
	remoterReciveData.remoterCorrectFlag = 0;
	remoterReciveData.PITCH_Correct = 0;
	remoterReciveData.ROLL_Correct = 0;
	
	remoterReciveData.ch0_correct = 0;
	remoterReciveData.ch1_correct = 0;
}


//���ջ��ź�����--����:��ͨ������PWMԭʼ����
void remoterRecive_GetData_2ms_(s16* CH_In)
{
	for(int i=0; i<8; i++)
	{
		remoterReciveData.remoterCH[i] = CH_In[i];
	}
}


//���ջ��ź��˲�
void remoterRecive_CH_filter_1ms_()
{
	for(int i=0; i<8; i++)
	{
		remoterReciveData.remoterCH_filter[i] += (s16)( 6 * (remoterReciveData.remoterCH[i] - remoterReciveData.remoterCH_filter[i]) * 0.002);
	}
}


//��鵱ǰģʽ
void remoterRecive_FlyModDuty_2ms_()
{
	//6050����
	if(remoterReciveData.remoterCH[0] > 1800 && remoterReciveData.remoterCH[1] > 1800 && postureCaculateData.gyroCorrectFlag == 0)
	{
		//����λ:��1
		postureCaculate_SetGyroCorrect();
	}
	
	//����:����Ѿ����������ҽ�����6050
	if(remoterReciveData.remoterCH[2] < 1200 && remoterReciveData.remoterCH[3] > 1800 && remoterReciveData.isLock == 1 && postureCaculateData.gyroCorrectFlag == 2)
	{
		remoterReciveData.lockCounter ++;
		//����500ms,����
		if(remoterReciveData.lockCounter > 250)
		{
			remoterReciveData.isLock = 0;
		}
	}		
	
	
	//����Ѿ���������û�н���ң����
	if(remoterReciveData.isLock == 0 && remoterReciveData.remoterCorrectFlag == 0)
	{
		//��������ң����
		remoterRecive_remoterCorrect();
	}
	//����������,һֱ����ͨ��ֵ
	else if(remoterReciveData.remoterCorrectFlag == 1)
	{
		remoterReciveData.ch0_correct = remoterReciveData.remoterCH[0] + remoterReciveData.ROLL_Correct;
		remoterReciveData.ch1_correct = remoterReciveData.remoterCH[1] + remoterReciveData.PITCH_Correct;
		
		//����������,����û�з������ָ��,�л�������ģʽ
		if(flyMode_GetMode() == Mode_Lock && remoterReciveData.remoterCH[6] < 1500)
		{
			flyMode_ChangeTo_Ready();
		}
	}
	
	
	//����������,�Ѿ�����,ӳ��Ŀ��Ƕȿ���+-30��,+-180��
	if(remoterReciveData.remoterCorrectFlag == 1 && remoterReciveData.isLock == 0)
	{
		postureCtrlData.target_angle_PITCH = LIMIT((1500-remoterReciveData.ch1_correct)*0.1, -30, 30);
		postureCtrlData.target_angle_ROLL  = LIMIT((remoterReciveData.ch0_correct-1500)*0.1, -30, 30);
		//postureCtrlData.target_angle_YAW = LIMIT((remoterReciveData.remoterCH[3]-1500)*0.02, -20, 20);
		//����
		if(remoterReciveData.remoterCH[3] < 1400 || remoterReciveData.remoterCH[3] > 1600)
		{
			postureCtrlData.target_angle_YAW += LIMIT((remoterReciveData.remoterCH[3]-1500), -400, 400)*0.001;
		}
	}
	
	
	//����ʶ��
	if(remoterReciveData.remoterCH[4] > 1900 && posFilterData.posZ_real_value > 300)
	{
		posXYCtrlData.posXYCtrlStartFlag = 1;
	}
	else
	{
		posXYCtrlData.posXYCtrlStartFlag = 0;
	}
	
	
	//����:���--����״̬�����
	if((remoterReciveData.remoterCH[6] > 1500) && flyMode_GetMode() == Mode_Ready)
	{
		flyMode_ChangeTo_AutoHightCtrl_TakeOff();
	}	
	//����Ѿ���ɣ����˴��£��л�������
	else if((remoterReciveData.remoterCH[6] < 1500) && flyModeData.Mode == Mode_AutoHightCtrl_TakeOff)
	{
		flyMode_ChangeTo_AutoHightCtrl_Down();
	}
	
	
	//����ͣ��
	if(remoterReciveData.remoterCH[5] > 1500)
	{
		remoterReciveData.all_out_ctrl = 0;
	}
	else
	{
		remoterReciveData.all_out_ctrl = 1;
	}
	
}


//�Ƿ����ͣ��--���
short remoterRecive_Emergency_out_()
{
	return remoterReciveData.all_out_ctrl;
}


//��������,˫����
short remoterRecive_IsLock_out_()
{
	return (1-remoterReciveData.isLock);
}


//����ң����PITCH/ROLL����
void remoterRecive_remoterCorrect()
{
	//���û�н���ң����
	if(remoterReciveData.remoterCorrectFlag == 0)
	{
		remoterReciveData.remoterCorrectCounter++;
		remoterReciveData.PITCH_Correct += 1500 - remoterReciveData.remoterCH[1];
		remoterReciveData.ROLL_Correct += 1500 - remoterReciveData.remoterCH[0];
		
		//����10��
		if(remoterReciveData.remoterCorrectCounter >10)
		{
			remoterReciveData.remoterCorrectFlag = 1;
			remoterReciveData.PITCH_Correct /= 10;
			remoterReciveData.ROLL_Correct /= 10;
		}
	}
}



