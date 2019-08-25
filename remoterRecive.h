#include <L_Link.h>

#ifndef __REMOTERRECIVER_H__

#define __REMOTERRECIVER_H__

typedef   signed short     int int16_t;
typedef int16_t s16;

typedef struct
{
	//�����ǽ�����־λ
	short Gyro_ref_flag;
	//ȫ���������
	short all_out_ctrl;
	
	//�Ƿ����
	short isLock;
	int lockCounter;
	
	//ң����ͨ������������,�ۼӺ�
	s16 remoterCorrectCounter;
	s16 remoterCorrectFlag;
	s16 PITCH_Correct;
	s16 ROLL_Correct;
	
	//ͨ���������ֵ
	s16 ch0_correct;
	s16 ch1_correct;
	
	//���ջ�ͨ��
	s16 remoterCH[8];
	s16 remoterCH_filter[8];
}remoterRecive_DataStruct;

//init
void remoterRecive_Init();

//���ջ��ź�����
void remoterRecive_GetData_2ms_(s16* CH_In);

//���ջ��ź��˲�
void remoterRecive_CH_filter_1ms_();

//��鵱ǰģʽ
void remoterRecive_FlyModDuty_2ms_();

//�Ƿ����ͣ��
short remoterRecive_Emergency_out_();

//��������
short remoterRecive_IsLock_out_();

//����ң����PITCH/ROLL����
void remoterRecive_remoterCorrect();

#endif
