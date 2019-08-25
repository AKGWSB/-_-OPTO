#ifndef __POSFILTER_H__

#define __POSFILTER_H__

typedef struct
{
	//posXYZ
	int posX_real_value;
	int posY_real_value;
	int posZ_real_value;
	float posX_filter_value;
	float posY_filter_value;
	float posZ_filter_value;
	float posX_predict_value;
	float posY_predict_value;
	float posZ_predict_value;
	
	//speedXYZ
	float speedX_d_value;
	float speedY_d_value;
	float speedZ_d_value;
	float speedX_predict_value;
	float speedY_predict_value;
	float speedZ_predict_value;
	
	//accXYZ
	float accX_real_value;
	float accY_real_value;
	float accZ_real_value;
	float accX_filter_value;
	float accY_filter_value;
	float accZ_filter_value;
	
	
}posFilter_DataStruct;

//-----------------------------------------------------------------------//

//���ݳ�ʼ��
void posFilter_DataInit();

//�ٶȽ���
void posFilter_GetXYZSpeed_2ms_();

//λ�ý��������˲�����
void posFilter_DataDispose_5ms_();

//λ�ý������ݽӿ�
void posFilter_GetData_10ms_(int posX_real_value, int posY_real_value, int posZ_real_value, float accX_real_value, float accY_real_value, float accZ_real_value);

#endif

