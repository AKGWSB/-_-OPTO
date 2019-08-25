#ifndef __POSTURECACULATE_H__

#define __POSTURECACULATE_H__

//��ά����
typedef struct
{
	float x;
	float y;
	float z;
	
}Vec3;

//��̬��
typedef struct
{
	float PITCH;
	float ROLL;
	float YAW;
	
}postureAngle;


typedef struct
{
	//���ٶȼ�
	Vec3 acc_real_value;
	Vec3 acc_filter_value;
	Vec3 acc_withoutGravity;
	
	//�����ǽ��ٶ�
	Vec3 gyro_real_value;
	Vec3 gyro_filter_value;
	
	//��������
	Vec3 mag_real_value;
	Vec3 mag_filter_value;
	
	//���ٶȼ�Ԥ����̬��
	postureAngle acc_postureAngle;
	
	//������̬��
	postureAngle postureAngle;
	
	//�����ǽ�����־λ
	short gyroCorrectFlag;
	short gyroCorrectCounter;
	
	//������,���ٶȼ�ƫ��
	Vec3 gyroCorrectErrSum;
	Vec3 accCorrectErrSum;
	Vec3 gyroCorrectErr;
	Vec3 accCorrectErr;
	
}postureCaculate_DataStruct;


//init
void postureCaculate_Init();


//��̬�������ݻ�ȡ--����������ٶ�,���ٶ�ԭʼ����
//�������������+-2000��/s
//�Ӽ��������+-8G -- +-32768
void postureCaculate_GetData_2ms_(float gyroX, float gyroY, float gyroZ, float acc_x_real_value, float acc_y_real_value, float acc_z_real_value, float magX, float magY, float magZ);


//��̬���������˲�--����1ms
void postureCaculate_DataFilter_1ms_();


//�����˲���̬����
void postureCaculate_CaculatePosture_2ms_();

//�����ǽ���
void postureCaculate_SetGyroCorrect();

#endif


