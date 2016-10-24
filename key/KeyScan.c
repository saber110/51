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
                0x00,  //熄灭
                0x00  //自定义
 
                         };
void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}


uchar KeyScan()	//带返回值的子函数
{
	uchar cord_l,cord_h;//声明列线和行线的值的储存变量
	P3 = 0x0f;//0000 1111
	if( (P3 & 0x0f) != 0x0f)//判断是否有按键按下
	{
		delay(5);//软件消抖
		if( (P3 & 0x0f) != 0x0f)//判断是否有按键按下
		{
			  cord_h = P3 & 0x0f;// 储存行线值
			  P3 = cord_l | 0xf0;
			  cord_l = P3 & 0xf0;// 储存列线值
			  while( (P3 & 0xf0) != 0xf0 );//松手检测
			  return (cord_l + cord_h);//返回键值码
		}	
	}
		
}

void KeyPro()
{
	switch( KeyScan() )
	{
	 	//第一行键值码
		case 0xee: P0 = leddata[0];		break;
		case 0xde: P0 = leddata[1];		break;
		case 0xbe: P0 = leddata[2];		break;
		case 0x7e: P0 = leddata[3];		break;
		
		//第二行键值码
		case 0xed: P0 = leddata[4];		break;
		case 0xdd: P0 = leddata[5];		break;
		case 0xbd: P0 = leddata[6];		break;
		case 0x7d: P0 = leddata[7];		break;

		//第三行键值码
		case 0xeb: P0 = leddata[8];		break;
		case 0xdb: P0 = leddata[9];		break;
		case 0xbb: P0 = leddata[10];	break;
		case 0x7b: P0 = leddata[11];	break;

		//第四行键值码
		case 0xe7: P0 = leddata[12];	break;
		case 0xd7: P0 = leddata[13];	break;
		case 0xb7: P0 = leddata[14];	break;
		case 0x77: P0 = leddata[15];	break;
		//独立键盘
		case 0xfe: P0 = leddata[16];	break;
		case 0xfd: P0 = leddata[17];	break;
		case 0xfb: P0 = leddata[18];	break;
		case 0xf7: P0 = leddata[19];	break;
	}	
}

void main()
{
	we = 1;//打开位选
	P0 = 0;//八位数码管全显示
	we = 0;//锁存位选

	du = 1;//打开段选端
	P0 = leddata[22];
	while(1)
	{
		
	 	KeyPro();//提取键值码并且送不同数值给数码管显示
	}
}