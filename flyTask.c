#include <flyTask.h>

flyTask_DataStruct flyTaskData;


//init
void flyTast_Init()
{
	flyTaskData.timerCNT = 0;
	flyTaskData.state = ctrlOff;
	flyTaskData.task = A;
	flyTaskData.targetAngle.PITCH = 0;
	flyTaskData.targetAngle.ROLL = 0;
	flyTaskData.targetAngle.YAW = 0;
	flyTaskData.posInterfaceX = 0;
	flyTaskData.posInterfaceY = 0;
	flyTaskData.speedInterfaceX = 0;
	flyTaskData.speedInterfaceY = 0;
}


//����������
void flyTask_CheckDuty_2ms_()
{
	//������°�����δ����������δ���(����A�������
	if(remoterReciveData.remoterCH[4] > 1900 && flyMode_GetMode() == Mode_Ready && flyTaskData.task == A)
	{
		//��ռ�����
		flyTaskData.timerCNT = 0;
		//�л�������ʶ��
		flyTaskData.state = followLine;
		//������һ������
		flyTaskData.task = B;
		//�������
		flyMode_ChangeTo_AutoHightCtrl_TakeOff();
		
		return;
	}
	
	
	//����B����
	if(flyTaskData.task == B)
	{
		if(remoterReciveData.remoterCH[4] <= 1900)
		{
			flyTaskData.state = ctrlOff;
			flyTaskData.task = H;
			return;
		}
		
		flyTaskData.timerCNT ++;
		//flyTaskData.timerCNT ++;flyTaskData.timerCNT > 3000
		
		//�������ֱ��ֱ�Ӷ���
		if(openmv.circle_flag == 1 && flyTaskData.timerCNT > 2000)
		{
			//��ռ�����
			flyTaskData.timerCNT = 0;
			//�л�������
			flyTaskData.state = back;
			//������һ������
			flyTaskData.task = C;
			//����
			//flyMode_ChangeTo_AutoHightCtrl_Down();
			return;
		}

		
		return;
	}
	
	
	//����Cɲ��
	if(flyTaskData.task == C)
	{
		flyTaskData.timerCNT ++;
		//flyTaskData.timerCNT ++;flyTaskData.timerCNT > 3000
		
		//1s
		if(flyTaskData.timerCNT > 500)
		{
			//��ռ�����
			flyTaskData.timerCNT = 0;
			//�л���ת��
			flyTaskData.state = yawTurn;
			//������һ������
			flyTaskData.task = D;
			return;
		}
		return;
	}
	
	//����Dת��
	if(flyTaskData.task == D)
	{
			if(remoterReciveData.remoterCH[4] <= 1900)
		{
			flyTaskData.state = ctrlOff;
			flyTaskData.task = H;
			return;
		}
		//flyTaskData.timerCNT ++;
		
		//ת90��
		if(flyTaskData.targetAngle.YAW <= -89)
		{
			//��ռ�����
			flyTaskData.timerCNT = 0;
			//ä��
			flyTaskData.state = blindFly;
			//������һ������
			flyTaskData.task = E;
		}
		
		return;
	}
	
	
	//����Eä��
	if(flyTaskData.task == E)
	{
			if(remoterReciveData.remoterCH[4] <= 1900)
		{
			flyTaskData.state = ctrlOff;
			flyTaskData.task = H;
			return;
		}
		flyTaskData.timerCNT ++;
		
		//�������ֱ��,2s
		if(openmv.circle_flag == 1 && flyTaskData.timerCNT > 100)
		{
			//��ռ�����
			flyTaskData.timerCNT = 0;
			//�л�������
			flyTaskData.state = back2;
			//������һ������
			flyTaskData.task = F;
		}
	}
	
		
	if(flyTaskData.task == F)
	{
		flyTaskData.timerCNT ++;
		//flyTaskData.timerCNT ++;flyTaskData.timerCNT > 3000
		
		//1s
		if(flyTaskData.timerCNT > 150)
		{
			//��ռ�����
			flyTaskData.timerCNT = 0;
			//�л���ת��
			flyTaskData.state = yawTurn;
			//������һ������
			flyTaskData.task = G;
			return;
		}
		return;
	}
		
	//����Gת��
	if(flyTaskData.task == G)
	{
			if(remoterReciveData.remoterCH[4] <= 1900)
		{
			flyTaskData.state = ctrlOff;
			flyTaskData.task = H;
			return;
		}
		//flyTaskData.timerCNT ++;
		
		//ת90��
		if(flyTaskData.targetAngle.YAW <= -198)
		{
			//��ռ�����
			flyTaskData.timerCNT = 0;
			//Ѱ��
			flyTaskData.state = followLine2;
			//������һ������
			flyTaskData.task = H;
		}
		
		return;
	}
	
	//����H
	if(flyTaskData.task == H)
	{
		flyTaskData.timerCNT ++;
		
		//
		if(flyTaskData.timerCNT > 2000)
		{
			//��ռ�����
			flyTaskData.timerCNT = 0;
			//�л���Ѱ��
			flyTaskData.state = followLine2;
			//����
			flyMode_ChangeTo_AutoHightCtrl_Down();
			//������һ������
			flyTaskData.task = I;
		}
		
		return;
	}
	

}

float anglePitch = -0.6;
void foward(float* angle)
{
	float angle_ = *angle;
	if(angle_ == -0.6)
	{
		angle_ = 0.5;
	}
	else if(angle_ == 0.5)
	{
		angle_ = -0.6;
	}
}

//�����������
void flyTask_AngleOutPutUpdate_2ms_()
{
	if(flyTaskData.state == ctrlOff)
	{
//		flyTaskData.posInterfaceX = 0;
//		flyTaskData.posInterfaceY = 0;
		flyTaskData.targetAngle.PITCH = 0;
		flyTaskData.targetAngle.ROLL = 0;
//	flyTaskData.targetAngle.YAW = 0;
		return ;
	}
	
	if(flyTaskData.state == pointStay)
	{	
		//�л����ݽӿ�
		flyTaskData.posInterfaceX = -1*openmv.circle_x+80;
		flyTaskData.posInterfaceY = openmv.circle_y-20;
		flyTaskData.speedInterfaceX = posFilterData.speedX_d_value;					//�����ٶ�
		flyTaskData.speedInterfaceY = posFilterData.speedY_d_value;	
		
		posXYCtrl_GetData_2ms_(flyTaskData.posInterfaceX, flyTaskData.posInterfaceY, flyTaskData.speedInterfaceX, flyTaskData.speedInterfaceY);
		
		//����ʶ����и߶�����
		if(posFilterData.posZ_real_value > 300)
		{
			flyTaskData.targetAngle.PITCH = posXYCtrl_outputTargetAngle_Pitch();
			flyTaskData.targetAngle.ROLL = posXYCtrl_outputTargetAngle_Roll();
			//flyTaskData.targetAngle.YAW = 0;
			return;
		}	
		else
		{
			flyTaskData.targetAngle.PITCH = 0;
			flyTaskData.targetAngle.ROLL = 0;
			flyTaskData.targetAngle.YAW = 0;
			return;
		}
		return;
	}
	
	if(flyTaskData.state == followLine)
	{
		//�л����ݽӿ�
		flyTaskData.posInterfaceX = -1*openmv.mid_x+80;											//��������
		flyTaskData.posInterfaceY = -20;																		//��Ŀ��λ��=Ŀ����ٶ�	
		flyTaskData.speedInterfaceX = posFilterData.speedX_predict_value*0.03;					//�����ٶ�
		flyTaskData.speedInterfaceY = OF_Data.speedY_filter_value*0.025;		//�����ٶ�
		
		posXYCtrl_GetData_2ms_(flyTaskData.posInterfaceX, flyTaskData.posInterfaceY, flyTaskData.speedInterfaceX, flyTaskData.speedInterfaceY);
		
		//Ѱ�߾��и߶�����
		if(posFilterData.posZ_real_value > 400)
		{	
			//flyTaskData.targetAngle.PITCH = posXYCtrl_outputTargetAngle_Pitch();
			flyTaskData.targetAngle.PITCH = -0.10;
			flyTaskData.targetAngle.ROLL = posXYCtrl_outputTargetAngle_Roll()-0.0;
			//flyTaskData.targetAngle.YAW = 0;
			return;
		}
		else
		{
			flyTaskData.targetAngle.PITCH = -2.40;
			flyTaskData.targetAngle.ROLL = 0;
			//flyTaskData.targetAngle.YAW = 0;
			return;
		}
		
		
		return;
	}
	
	if(flyTaskData.state == followLine2)
	{
		//�л����ݽӿ�
		flyTaskData.posInterfaceX = -1*openmv.mid_x+80;											//��������
		flyTaskData.posInterfaceY = -20;																		//��Ŀ��λ��=Ŀ����ٶ�	
		flyTaskData.speedInterfaceX = posFilterData.speedX_predict_value*0.03;					//�����ٶ�
		flyTaskData.speedInterfaceY = OF_Data.speedY_filter_value*0.025;		//�����ٶ�
		
		posXYCtrl_GetData_2ms_(flyTaskData.posInterfaceX, flyTaskData.posInterfaceY, flyTaskData.speedInterfaceX, flyTaskData.speedInterfaceY);
		
		//Ѱ�߾��и߶�����
		if(posFilterData.posZ_real_value > 400)
		{	
			//flyTaskData.targetAngle.PITCH = posXYCtrl_outputTargetAngle_Pitch();
			flyTaskData.targetAngle.PITCH = -1.0;
			flyTaskData.targetAngle.ROLL = posXYCtrl_outputTargetAngle_Roll()-0.0;
			//flyTaskData.targetAngle.YAW = 0;
			return;
		}
		else
		{
			flyTaskData.targetAngle.PITCH = -2.40;
			flyTaskData.targetAngle.ROLL = 0;
			//flyTaskData.targetAngle.YAW = 0;
			return;
		}
		
		
		return;
	}
	
	if(flyTaskData.state == yawTurn)
	{
		flyTaskData.targetAngle.PITCH = 0;
		flyTaskData.targetAngle.ROLL = -0;
		flyTaskData.targetAngle.YAW -= 0.25;
		
		return;
	}
	
	
	if(flyTaskData.state == blindFly)
	{
		//�л����ݽӿ�
		flyTaskData.posInterfaceX = -1*openmv.mid_x+80;											//
		flyTaskData.posInterfaceY = -20;																		//��Ŀ��λ��=Ŀ����ٶ�	
		flyTaskData.speedInterfaceX = posFilterData.speedX_predict_value*0.03;					//
		flyTaskData.speedInterfaceY = 0;		
		
		posXYCtrl_GetData_2ms_(flyTaskData.posInterfaceX, flyTaskData.posInterfaceY, flyTaskData.speedInterfaceX, flyTaskData.speedInterfaceY);
		
		foward(&anglePitch);
		//flyTaskData.targetAngle.PITCH = posXYCtrl_outputTargetAngle_Pitch();
		flyTaskData.targetAngle.PITCH = -1.0;
		flyTaskData.targetAngle.ROLL = posXYCtrl_outputTargetAngle_Roll();
//		flyTaskData.targetAngle.YAW -= 0.5;
		
		return;
	}
	
	if(flyTaskData.state == left)
	{
		flyTaskData.targetAngle.PITCH = 0;
		flyTaskData.targetAngle.ROLL = -2.5;
		flyTaskData.targetAngle.YAW = 0;
		return;
	}
	
	if(flyTaskData.state == right)
	{
		flyTaskData.targetAngle.PITCH = posXYCtrl_outputTargetAngle_Pitch();
		flyTaskData.targetAngle.ROLL = 2.5;
		flyTaskData.targetAngle.YAW = 0;
		return;
	}
	
	if(flyTaskData.state == forward)
	{
		flyTaskData.targetAngle.PITCH = -2.5;
		flyTaskData.targetAngle.ROLL = posXYCtrl_outputTargetAngle_Roll();
		flyTaskData.targetAngle.YAW = 0;
		return;
	}
	
	if(flyTaskData.state == back)
	{
		//�л����ݽӿ�
		flyTaskData.posInterfaceX = -1*openmv.mid_x+80;											//��������
		flyTaskData.posInterfaceY = -20;																		//��Ŀ��λ��=Ŀ����ٶ�	
		flyTaskData.speedInterfaceX = posFilterData.speedX_predict_value*0.03;					//�����ٶ�
		flyTaskData.speedInterfaceY = OF_Data.speedY_filter_value*0.025;		//�����ٶ�
		
		posXYCtrl_GetData_2ms_(flyTaskData.posInterfaceX, flyTaskData.posInterfaceY, flyTaskData.speedInterfaceX, flyTaskData.speedInterfaceY);
		
		flyTaskData.targetAngle.PITCH = 3.0;
		flyTaskData.targetAngle.ROLL = posXYCtrl_outputTargetAngle_Roll();
		//flyTaskData.targetAngle.YAW = 0;
		return;
	}
	
	if(flyTaskData.state == back2)
	{
		//�л����ݽӿ�
		flyTaskData.posInterfaceX = -1*openmv.mid_x+80;											//��������
		flyTaskData.posInterfaceY = -20;																		//��Ŀ��λ��=Ŀ����ٶ�	
		flyTaskData.speedInterfaceX = posFilterData.speedX_predict_value*0.03;					//�����ٶ�
		flyTaskData.speedInterfaceY = OF_Data.speedY_filter_value*0.025;		//�����ٶ�
		
		posXYCtrl_GetData_2ms_(flyTaskData.posInterfaceX, flyTaskData.posInterfaceY, flyTaskData.speedInterfaceX, flyTaskData.speedInterfaceY);
		
		flyTaskData.targetAngle.PITCH = 6.5;
		flyTaskData.targetAngle.ROLL = posXYCtrl_outputTargetAngle_Roll()-0.5;
		//flyTaskData.targetAngle.YAW = 0;
		return;
	}

}


//���Ŀ�긩����
float flyTask_TargetAngleOut_Pitch()
{
	return flyTaskData.targetAngle.PITCH;
}


//���Ŀ������
float flyTask_TargetAngleOut_Roll()
{
	return flyTaskData.targetAngle.ROLL;
}


//���Ŀ��ƫ����
float flyTask_TargetAngleOut_Yaw()
{
	return flyTaskData.targetAngle.YAW;
}

