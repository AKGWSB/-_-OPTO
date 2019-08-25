#include <posFilter.h>
#include "L_math.h"

posFilter_DataStruct posFilterData;

//���ݳ�ʼ��
void posFilter_DataInit()
{
	//posXYZ
	posFilterData.posX_real_value = 0;
	posFilterData.posY_real_value = 0;
	posFilterData.posZ_real_value = 0;
	posFilterData.posX_filter_value = 0;
	posFilterData.posY_filter_value = 0;
	posFilterData.posZ_filter_value = 0;
	posFilterData.posX_predict_value = 0;
	posFilterData.posY_predict_value = 0;
	posFilterData.posZ_predict_value = 0;
	
	//speedXYZ
	posFilterData.speedX_d_value = 0;
	posFilterData.speedY_d_value = 0;
	posFilterData.speedZ_d_value = 0;
	posFilterData.speedX_predict_value = 0;
	posFilterData.speedY_predict_value = 0;
	posFilterData.speedZ_predict_value = 0;
	
	//accXYZ
	posFilterData.accX_real_value = 0;
	posFilterData.accY_real_value = 0;
	posFilterData.accZ_real_value = 0;
	posFilterData.accX_filter_value = 0;
	posFilterData.accY_filter_value = 0;
	posFilterData.accZ_filter_value = 0;
}


//λ�ý������ݽӿ�--���룺XYZλ��ԭʼ����,XYZ���ٶ�ԭʼ����
void posFilter_GetData_10ms_(int posX_real_value, int posY_real_value, int posZ_real_value, float accX_real_value, float accY_real_value, float accZ_real_value)
{
	//XYZλ����ʵ����
	posFilterData.posX_real_value = posX_real_value;
	posFilterData.posY_real_value = posY_real_value;
	posFilterData.posZ_real_value = LIMIT(posZ_real_value, 0, 1500);
	
	//XYZ���ٶȼ�ȥ����ֵ
	posFilterData.accX_real_value = accX_real_value;
	posFilterData.accY_real_value = accY_real_value;
	posFilterData.accZ_real_value = accZ_real_value;
}


//λ�ý��������˲�����
void posFilter_DataDispose_5ms_()
{
	//λ�������˲�
	posFilterData.posX_filter_value += 3.14f * 3 * (posFilterData.posX_real_value - posFilterData.posX_filter_value) * 0.005;
	posFilterData.posY_filter_value += 3.14f * 3 * (posFilterData.posY_real_value - posFilterData.posY_filter_value) * 0.005;
	posFilterData.posZ_filter_value += 3.14f * 3 * (posFilterData.posZ_real_value - posFilterData.posZ_filter_value) * 0.005;
	
	//���ٶȼ������˲�
	posFilterData.accX_filter_value += 3.14f * 3 * (posFilterData.accX_real_value - posFilterData.accX_filter_value) * 0.005;
	posFilterData.accY_filter_value += 3.14f * 3 * (posFilterData.accY_real_value - posFilterData.accY_filter_value) * 0.005;
	posFilterData.accZ_filter_value += 3.14f * 3 * (posFilterData.accZ_real_value - posFilterData.accZ_filter_value) * 0.005;
}


//�����˲�xyz�ٶȽ��� 
/*-- ���û��������ͺ������λ�����ߴӶ����в�ֵõ��ٶ�,�ü��ٶȼƵõ��ٶ�ȥ�����ڲ���ٶ� --*/
void posFilter_GetXYZSpeed_2ms_()
{
	//�������λ��
	posFilterData.posX_predict_value += 3.14f * 2 * (posFilterData.posX_filter_value - posFilterData.posX_predict_value) * 0.002;
	posFilterData.posY_predict_value += 3.14f * 2 * (posFilterData.posY_filter_value - posFilterData.posY_predict_value) * 0.002;
	posFilterData.posZ_predict_value += 3.14f * 3 * (posFilterData.posZ_filter_value - posFilterData.posZ_predict_value) * 0.002;
	
	//��ּ�������ٶȣ�ʵ��-Ԥ�⣨�ͺ� = �ٶȣ��ͺ�
	posFilterData.speedX_d_value = posFilterData.posX_filter_value - posFilterData.posX_predict_value;
	posFilterData.speedY_d_value = posFilterData.posY_filter_value - posFilterData.posY_predict_value;
	posFilterData.speedZ_d_value = posFilterData.posZ_filter_value - posFilterData.posZ_predict_value;
	
	//���ּ�������ٶ�
	posFilterData.speedX_predict_value += 3.14f * 3 * posFilterData.accX_filter_value * 0.002;
	posFilterData.speedY_predict_value += 3.14f * 3 * posFilterData.accY_filter_value * 0.002;
	posFilterData.speedZ_predict_value += 3.14f * 3 * posFilterData.accZ_filter_value * 0.002;
	
	//���������ٶ�Ȩֵ
	float weightX = LIMIT(L_abs(posFilterData.accX_filter_value*0.01), 0.01, 1);
	float weightY = LIMIT(L_abs(posFilterData.accY_filter_value*0.01), 0.01, 1);
	float weightZ = LIMIT(L_abs(posFilterData.accZ_filter_value*0.01), 0.01, 1);
	
	//����->�ٶ�  ������  ���->�ٶ�
	posFilterData.speedX_predict_value += 3.14f * 4 * (posFilterData.speedX_d_value*38*weightX - posFilterData.speedX_predict_value) * 0.002;
	posFilterData.speedY_predict_value += 3.14f * 4 * (posFilterData.speedY_d_value*38*weightY - posFilterData.speedY_predict_value) * 0.002;
	posFilterData.speedZ_predict_value += 3.14f * 2 * (posFilterData.speedZ_d_value*14*1 - posFilterData.speedZ_predict_value) * 0.002;
}






