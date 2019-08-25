#include "PID.h"

PID_DataStruct PID_Data;


//init
void PID_InitOneGroup(PID_Group group)
{
	group.kp = 0;
	group.ki = 0;
	group.kd = 0;
}

//init
void PID_Init()
{
	PID_InitOneGroup(PID_Data.group01);
	PID_InitOneGroup(PID_Data.group02);
	PID_InitOneGroup(PID_Data.group03);
	PID_InitOneGroup(PID_Data.group04);
	PID_InitOneGroup(PID_Data.group05);
	PID_InitOneGroup(PID_Data.group06);
	PID_InitOneGroup(PID_Data.group07);
	PID_InitOneGroup(PID_Data.group08);
	PID_InitOneGroup(PID_Data.group09);
	PID_InitOneGroup(PID_Data.group10);
	PID_InitOneGroup(PID_Data.group11);
	PID_InitOneGroup(PID_Data.group12);
	PID_InitOneGroup(PID_Data.group13);
	PID_InitOneGroup(PID_Data.group14);
	PID_InitOneGroup(PID_Data.group15);
	PID_InitOneGroup(PID_Data.group16);
	
	PID_Data.OpenmvValue = 0;
	
	PID_Data.recStep = 0;
}


//���ڽ���һλ����
void PID_DataRecive_It(char data)
{
	//��ͷ����
	if(data == '#' && PID_Data.recStep == 0)
	{
		PID_Data.tempData[PID_Data.recStep] = data;
		PID_Data.recStep ++;
	}
	
	//Э�����ݽ���
	if(PID_Data.recStep >= 1)
	{
		PID_Data.tempData[PID_Data.recStep] = data;
		PID_Data.recStep ++;
	}
	
	//��β����
	if(PID_Data.recStep == '\r')
	{
		PID_Data.tempData[PID_Data.recStep] = data;
		PID_Data.recStep ++;
	}
	if(PID_Data.recStep == '\n')
	{
		PID_Data.tempData[PID_Data.recStep] = data;
		PID_Data.recStep = 0;
		
		//���ݴ���
		for(int i=0; i<30; i++)
		{
			PID_Data.usartData[i] = PID_Data.tempData[i];
		}
	}
}


//PID����Э����
void PID_SetAgreementDecode()
{
	if(PID_Data.usartData[0] == '#'
	&& PID_Data.usartData[1] == 'p'
	&& PID_Data.usartData[2] == 'i'
	&& PID_Data.usartData[3] == 'd')
	{
		switch(PID_Data.usartData[4]*10+PID_Data.usartData[5])
		{
			case 1:
			{
				
			}
			break;
			
			case 2:
			{
				
			}
			break;
			
			case 3:
			{
				
			}
			break;
			
			case 4:
			{
				
			}
			break;
			
			case 5:
			{
				
			}
			break;
			
			case 6:
			{
				
			}
			break;
			
			case 7:
			{
				
			}
			break;
			
			case 8:
			{
				
			}
			break;
			
			case 9:
			{
				
			}
			break;
			
			case 10:
			{
				
			}
			break;
			
			case 11:
			{
				
			}
			break;
			
			case 12:
			{
				
			}
			break;
			
			case 13:
			{
				
			}
			break;
			
			case 14:
			{
				
			}
			break;
			
			case 15:
			{
				
			}
			break;
			
			case 16:
			{
				
			}
			break;
		}
	}
}


