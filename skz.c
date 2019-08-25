#include <skz.h>

skz_DataStruct skzData;

//init
void skz_DataInit()
{
	skzData.distance = 0;
	skzData.dis_ref_flag = 0;
	skzData.recFinishFlag = 0;
	skzData.recStep = 0;
	skzData.tempDistance = 0;
}

//�������ݽ���
void skz_DataDecode_10ms_()
{
	//���û���ڽ����У�������һ���Ѿ��������
	if(skzData.recFinishFlag)
	{
		int i;
		for(i=0; i<4; i++)
		{
			//���������
			if(skzData.tempData[i+9] >= '0' 
			&& skzData.tempData[i+9] <= '9')
			{
				skzData.distance = skzData.distance*16 + (skzData.tempData[i+9]-48);
			}
			//�������ĸ
			else if(skzData.tempData[i+9] >= 'A' 
					 && skzData.tempData[i+9] <= 'Z')
			{
				skzData.distance = skzData.distance*16 + (skzData.tempData[i+9]-(int)('A')+10);
			}
		}
		skzData.dis_ref_flag = 0;
	}
	else
	{
		return;
	}
}


//���ڽ�������
void skz_DataRecive_It(char data)
{
	//���հ�ͷ
	if(data == '~' && skzData.recStep == 0)
	{
		skzData.recFinishFlag = 0;				//�����־λ
		skzData.tempData[skzData.recStep] = data;
		skzData.recStep++;
	}
	//����Э������
	else if( skzData.recStep <=16 && skzData.recStep >= 1)
	{
		skzData.tempData[skzData.recStep] = data;
		skzData.recStep++;
	}
	else if( skzData.recStep == 17 && data == '\r')
	{
		skzData.recStep++;
	}
	//��������
	else if( skzData.recStep == 18 && data == '\n')
	{
		skzData.recStep = 0;
		skzData.recFinishFlag = 1;	
	}
}

