#ifndef __SKZ_H__

#define __SKZ_H__

typedef   signed short     int int16_t;
typedef int16_t s16;

typedef struct
{
	char tempData[17];
	int tempDistance;
	s16 distance;
	int recStep;
	int recFinishFlag;
	int dis_ref_flag;
	
}skz_DataStruct;

//init
void skz_DataInit();

//���ڽ���һ���ַ�
void skz_DataRecive_It(char data);

//�������ݽ���
void skz_DataDecode_10ms_();

#endif 




