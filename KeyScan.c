#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned int
sbit we = P2^7;
sbit du = P2^6;
uchar code leddata[]={ 
 
                0x3F,  //"0"
                0x06,  //"1"
                0x5B,  //"2"
                0x4F,  //"3"
                0x66,  //"4"
                0x6D,  //"5"
                0x7D,  //"6"
                0x07,  //"7"
                0x7F,  //"8"
                0x6F,  //"9"
                0x77,  //"A"
                0x7C,  //"B"
                0x39,  //"C"
                0x5E,  //"D"
                0x79,  //"E"
                0x71,  //"F"
                0x76,  //"H"
                0x38,  //"L"
                0x37,  //"n"
                0x3E,  //"u"
                0x73,  //"P"
                0x5C,  //"o"
                0x40,  //"-"
                0x00,  //Ϩ��
                0x00  //�Զ���
 
                         };
void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}


uchar KeyScan()	//������ֵ���Ӻ���
{
	uchar cord_l,cord_h;//�������ߺ����ߵ�ֵ�Ĵ������
	P3 = 0x0f;//0000 1111
	if( (P3 & 0x0f) != 0x0f)//�ж��Ƿ��а�������
	{
		delay(5);//�������
		if( (P3 & 0x0f) != 0x0f)//�ж��Ƿ��а�������
		{
			  cord_h = P3 & 0x0f;// ��������ֵ
			  P3 = cord_l | 0xf0;
			  cord_l = P3 & 0xf0;// ��������ֵ
			  while( (P3 & 0xf0) != 0xf0 );//���ּ��
			  return (cord_l + cord_h);//���ؼ�ֵ��
		}	
	}
		
}

void KeyPro()
{
	switch( KeyScan() )
	{
	 	//��һ�м�ֵ��
		case 0xee: P0 = leddata[0];		break;
		case 0xde: P0 = leddata[1];		break;
		case 0xbe: P0 = leddata[2];		break;
		case 0x7e: P0 = leddata[3];		break;
		
		//�ڶ��м�ֵ��
		case 0xed: P0 = leddata[4];		break;
		case 0xdd: P0 = leddata[5];		break;
		case 0xbd: P0 = leddata[6];		break;
		case 0x7d: P0 = leddata[7];		break;

		//�����м�ֵ��
		case 0xeb: P0 = leddata[8];		break;
		case 0xdb: P0 = leddata[9];		break;
		case 0xbb: P0 = leddata[10];	break;
		case 0x7b: P0 = leddata[11];	break;

		//�����м�ֵ��
		case 0xe7: P0 = leddata[12];	break;
		case 0xd7: P0 = leddata[13];	break;
		case 0xb7: P0 = leddata[14];	break;
		case 0x77: P0 = leddata[15];	break;
		//��������
		case 0xfe: P0 = leddata[16];	break;
		case 0xfd: P0 = leddata[17];	break;
		case 0xfb: P0 = leddata[18];	break;
		case 0xf7: P0 = leddata[19];	break;
	}	
}

void main()
{
	we = 1;//��λѡ
	P0 = 0;//��λ�����ȫ��ʾ
	we = 0;//����λѡ

	du = 1;//�򿪶�ѡ��
	P0 = leddata[22];
	while(1)
	{
		
	 	KeyPro();//��ȡ��ֵ�벢���Ͳ�ͬ��ֵ���������ʾ
	}
}