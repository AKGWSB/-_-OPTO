#include "postureCaculate.h"
#include "L_math.h"

postureCaculate_DataStruct postureCaculateData;

//init
void postureCaculate_Init()
{
	//������־λ,������
	postureCaculateData.gyroCorrectFlag = 0;
	postureCaculateData.gyroCorrectCounter = 0;
	
	//acc
	postureCaculateData.acc_real_value.x = 0;
	postureCaculateData.acc_real_value.y = 0;
	postureCaculateData.acc_real_value.z = 0;
	postureCaculateData.acc_filter_value.x = 0;
	postureCaculateData.acc_filter_value.y = 0;
	postureCaculateData.acc_filter_value.z = 0;
	postureCaculateData.acc_withoutGravity.x = 0;
	postureCaculateData.acc_withoutGravity.y = 0;
	postureCaculateData.acc_withoutGravity.z = 0;
	
	//gyro
	postureCaculateData.gyro_real_value.x = 0;
	postureCaculateData.gyro_real_value.y = 0;
	postureCaculateData.gyro_real_value.z = 0;
	postureCaculateData.gyro_filter_value.x = 0;
	postureCaculateData.gyro_filter_value.y = 0;
	postureCaculateData.gyro_filter_value.z = 0;
	
	//mag
	postureCaculateData.mag_real_value.x = 0;
	postureCaculateData.mag_real_value.y = 0;
	postureCaculateData.mag_real_value.z = 0;
	postureCaculateData.mag_filter_value.x = 0;
	postureCaculateData.mag_filter_value.y = 0;
	postureCaculateData.mag_filter_value.z = 0;
	
	//���ٶȼƷ����Ǽ���Ƕ�acc->postureAngle
	postureCaculateData.acc_postureAngle.PITCH = 0;
	postureCaculateData.acc_postureAngle.ROLL = 0;
	postureCaculateData.acc_postureAngle.YAW = 0;
	
	//�����ǻ��ּ���Ƕ�final->postureAngle
	postureCaculateData.postureAngle.PITCH = 0;
	postureCaculateData.postureAngle.ROLL = 0;
	postureCaculateData.postureAngle.YAW = 0;
	
	//��������
	postureCaculateData.gyroCorrectErrSum.x = 0;
	postureCaculateData.gyroCorrectErrSum.y = 0;
	postureCaculateData.gyroCorrectErrSum.z = 0;
	postureCaculateData.accCorrectErrSum.x = 0;
	postureCaculateData.accCorrectErrSum.y = 0;
	postureCaculateData.accCorrectErrSum.z = 0;
	
	//�������
	postureCaculateData.gyroCorrectErr.x = 0;
	postureCaculateData.gyroCorrectErr.y = 0;
	postureCaculateData.gyroCorrectErr.z = 0;
	postureCaculateData.accCorrectErr.x = 0;
	postureCaculateData.accCorrectErr.x = 0;
	postureCaculateData.accCorrectErr.z = 0;
}


//��̬�������ݻ�ȡ--����������ٶ�,���ٶ�ԭʼ����
//�������������+-2000��/s
//�Ӽ��������+-8G -- +-32768
void postureCaculate_GetData_2ms_(float gyroX, float gyroY, float gyroZ, float acc_x_real_value, float acc_y_real_value, float acc_z_real_value, float magX, float magY, float magZ)
{
	postureCaculateData.gyro_real_value.x = gyroX;
	postureCaculateData.gyro_real_value.y = gyroY;
	postureCaculateData.gyro_real_value.z = gyroZ;
	
	postureCaculateData.acc_real_value.x = acc_x_real_value;
	postureCaculateData.acc_real_value.y = acc_y_real_value;
	postureCaculateData.acc_real_value.z = acc_z_real_value;
	
	postureCaculateData.mag_real_value.x = magX;
	postureCaculateData.mag_real_value.y = magY;
	postureCaculateData.mag_real_value.z = magZ;
}

//��̬���������˲�--����1ms
void postureCaculate_DataFilter_1ms_()
{
	//�Ӽ��˲�
	postureCaculateData.acc_filter_value.x += 3.14f * 2 * (postureCaculateData.acc_real_value.x - postureCaculateData.acc_filter_value.x) * 0.001;
	postureCaculateData.acc_filter_value.y += 3.14f * 2 * (postureCaculateData.acc_real_value.y - postureCaculateData.acc_filter_value.y) * 0.001;
	postureCaculateData.acc_filter_value.z += 3.14f * 2 * (postureCaculateData.acc_real_value.z - postureCaculateData.acc_filter_value.z) * 0.001;
	
	//�������˲�
	postureCaculateData.gyro_filter_value.x += 3.14f * 2 * (postureCaculateData.gyro_real_value.x + postureCaculateData.gyroCorrectErr.x - postureCaculateData.gyro_filter_value.x) * 0.001;
	postureCaculateData.gyro_filter_value.y += 3.14f * 2 * (postureCaculateData.gyro_real_value.y + postureCaculateData.gyroCorrectErr.y - postureCaculateData.gyro_filter_value.y) * 0.001;
	postureCaculateData.gyro_filter_value.z += 3.14f * 2 * (postureCaculateData.gyro_real_value.z + postureCaculateData.gyroCorrectErr.z - postureCaculateData.gyro_filter_value.z) * 0.001;
	
	//���������˲�
	postureCaculateData.mag_filter_value.x += 3.14f * 20 * (postureCaculateData.mag_real_value.x - postureCaculateData.mag_filter_value.x) * 0.001;
	postureCaculateData.mag_filter_value.y += 3.14f * 20 * (postureCaculateData.mag_real_value.y - postureCaculateData.mag_filter_value.y) * 0.001;
	postureCaculateData.mag_filter_value.z += 3.14f * 20 * (postureCaculateData.mag_real_value.z - postureCaculateData.mag_filter_value.z) * 0.001;
}


//�����˲���̬����
void postureCaculate_CaculatePosture_2ms_()
{
	Vec3 acc_ref;
	Vec3 gyro_ref;
	//���ݽ����������������&�Ӽ�
	acc_ref.x = postureCaculateData.acc_filter_value.x + postureCaculateData.accCorrectErr.x;
	acc_ref.y = postureCaculateData.acc_filter_value.y + postureCaculateData.accCorrectErr.y;
	acc_ref.z = postureCaculateData.acc_filter_value.z + postureCaculateData.accCorrectErr.z;
	gyro_ref.x = postureCaculateData.gyro_real_value.x + postureCaculateData.gyroCorrectErr.x;
	gyro_ref.y = postureCaculateData.gyro_real_value.y + postureCaculateData.gyroCorrectErr.y;
	gyro_ref.z = postureCaculateData.gyro_real_value.z + postureCaculateData.gyroCorrectErr.z;
	
	
	//���ٶȼƹ�һ��
	float acc_vecMod = 0;
	acc_vecMod += acc_ref.x * acc_ref.x;
	acc_vecMod += acc_ref.y * acc_ref.y;
	acc_vecMod += acc_ref.z * acc_ref.z;
	acc_vecMod = L_sqrt(acc_vecMod);
	
	Vec3 acc_normalize;
	acc_normalize.x = acc_ref.x / acc_vecMod;
	acc_normalize.y = acc_ref.y / acc_vecMod;
	acc_normalize.z = acc_ref.z / acc_vecMod;
	
	//���ٶȼƼ���PITCH,��ȷ��0.1��
	if(acc_normalize.x < 0)
	{
		postureCaculateData.acc_postureAngle.PITCH = -0.1 * (float)L_arcTan(L_abs(acc_normalize.x), acc_normalize.z);
	}
	else if(acc_normalize.x >= 0)
	{
		postureCaculateData.acc_postureAngle.PITCH = 0.1 * (float)L_arcTan(acc_normalize.x, acc_normalize.z);
	}
	//���ٶȼƼ���ROLL,��ȷ��0.1��
	if(acc_normalize.y < 0)
	{
		postureCaculateData.acc_postureAngle.ROLL = -0.1 * (float)L_arcTan(L_abs(acc_normalize.y), acc_normalize.z);
	}
	else if(acc_normalize.y >= 0)
	{
		postureCaculateData.acc_postureAngle.ROLL = 0.1 * (float)L_arcTan(acc_normalize.y, acc_normalize.z);
	}
	
	
	//�����ǻ��ּ���Ƕ�
	postureCaculateData.postureAngle.PITCH -= 3.64 * (gyro_ref.y * 0.002) * PI / 180;
	postureCaculateData.postureAngle.ROLL += 3.64 * (gyro_ref.x * 0.002) * PI / 180;
	postureCaculateData.postureAngle.YAW += 3.64 * (gyro_ref.z * 0.002) * PI / 180;
	
	//����Ӽƿ��Ŷ�Ȩֵ
	float acc_weight = (4096/acc_vecMod)*(4096/acc_vecMod);
	//���ֽǶ������ڼӼƽǶ�
	postureCaculateData.postureAngle.PITCH += 3.14f * 0.15 * acc_weight * (postureCaculateData.acc_postureAngle.PITCH - postureCaculateData.postureAngle.PITCH) * 0.002;
	postureCaculateData.postureAngle.ROLL += 3.14f * 0.15 * acc_weight * (postureCaculateData.acc_postureAngle.ROLL - postureCaculateData.postureAngle.ROLL) * 0.002;  
	
	//����������ACC
	postureCaculateData.acc_withoutGravity.z = ((postureCaculateData.acc_real_value.z + postureCaculateData.accCorrectErr.z) / (L_cos(postureCaculateData.postureAngle.PITCH) * L_cos(postureCaculateData.postureAngle.ROLL)))-4096;
	postureCaculateData.acc_withoutGravity.x = postureCaculateData.acc_real_value.x + postureCaculateData.accCorrectErr.x - ((postureCaculateData.acc_withoutGravity.z+4096) * L_sin(postureCaculateData.postureAngle.PITCH));
	postureCaculateData.acc_withoutGravity.y = postureCaculateData.acc_real_value.y + postureCaculateData.accCorrectErr.y - ((postureCaculateData.acc_withoutGravity.z+4096) * L_sin(postureCaculateData.postureAngle.ROLL));
	
	//-------------------------------------------------------------------------------------------//
	//�����ʼ����,����50�ν���
	if(postureCaculateData.gyroCorrectFlag == 1 )
	{
		//����
		postureCaculateData.gyroCorrectCounter ++;
		
		//���ٶȼƽ���������
		postureCaculateData.accCorrectErrSum.x += 0.00 - postureCaculateData.acc_filter_value.x;
		postureCaculateData.accCorrectErrSum.y += 0.00 - postureCaculateData.acc_filter_value.y;
		postureCaculateData.accCorrectErrSum.z += 4096 - postureCaculateData.acc_filter_value.z;
		
		//�����ǽ���������
		postureCaculateData.gyroCorrectErrSum.x += 0 - postureCaculateData.gyro_real_value.x;
		postureCaculateData.gyroCorrectErrSum.y += 0 - postureCaculateData.gyro_real_value.y;
		postureCaculateData.gyroCorrectErrSum.z += 0 - postureCaculateData.gyro_real_value.z;
		
		//ֹͣ����
		if(postureCaculateData.gyroCorrectCounter > 50)
		{
			postureCaculateData.gyroCorrectFlag = 2;
			
			//�����ֵ
			postureCaculateData.accCorrectErr.x = postureCaculateData.accCorrectErrSum.x / 50;
			postureCaculateData.accCorrectErr.y = postureCaculateData.accCorrectErrSum.y / 50;
			postureCaculateData.accCorrectErr.z = postureCaculateData.accCorrectErrSum.z / 50;
			postureCaculateData.gyroCorrectErr.x = postureCaculateData.gyroCorrectErrSum.x / 50;
			postureCaculateData.gyroCorrectErr.y = postureCaculateData.gyroCorrectErrSum.y / 50;
			postureCaculateData.gyroCorrectErr.z = postureCaculateData.gyroCorrectErrSum.z / 50;
			
			//��������ǻ���
			postureCaculateData.postureAngle.PITCH = 0;
			postureCaculateData.postureAngle.ROLL = 0;
			postureCaculateData.postureAngle.YAW = 0;
		}
	}
	//-------------------------------------------------------------------------------------------//
}


//�����ǽ���
void postureCaculate_SetGyroCorrect()
{
	postureCaculateData.gyroCorrectFlag = 1;
}






