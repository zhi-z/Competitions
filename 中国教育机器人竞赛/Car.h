#ifndef	__car_H_
#define	__car_H_
#include"reg52.h"
#include"intrins.h"

sbit left  = P1^0;	    //左边
sbit right = P1^1;	    //右边

sbit Left_1_led=P2^6;	 //左循迹红外传感器       
sbit Right_1_led=P2^4;	 //右循迹红外传感器  
sbit Centre_1_led=P2^5;	  //中间
sbit Left_led = P2^3;
sbit Right_led = P2^2;

sbit Left_2_led=P2^0;	  //灯不亮为高，有黑线
sbit Right_2_led= P2^7;	


 /************************************************************************************
 -
 -		函数名称：		   Delay1ms
 -	    作用：             延时函数
 -		
 -
 ************************************************************************************/

void Delay1ms(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;
	while(x--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}


 /************************************************************************************
 -
 -		函数名称：		   delay
 -	    作用：             电机驱动延时
 -		解释：	           x为延时时间             y，z为电机转向控制  
 -		x，y的控制：	   132~151为顺时针         152为电机停止             153~172为逆时针
 -
 ************************************************************************************/

 void delay(unsigned int z)
 {
	 while(z--)
	 ;

 }

 /***************************************************************************************************
 -
 -	 函数名称：	    	machine
 -   作用：             电机驱动程序
 -	 解释：	            x为延时时间                y，z为电机转向控制  
 -   x，y的控制：	    132~151为顺时针                152为电机停止             153~172为逆时针
 -   说明：            （x，172,132）为前进x   	  （x，132,172）为后退x          (x,152,132)为左转
 -        
 ***************************************************************************************************/

 void machine(unsigned int x,unsigned int y,unsigned int z)
 {
    while(x--)
	{
		left=1;
	 	delay(y);            //左边电机控制	 
	 	left=0;

		right=1;
		delay(z);		    //右边电机控制	 
		right=0;

	   delay(1740);
 	}
 }

/*******************************************************************************
* 功能描述 : 校准
* 函数属性 : 外部
* 输入参数 : unsigned int z
* 返回参数 : 无
* 函数详解 : 调用该函数,编译程序并下载,之后用螺丝刀扭转连续舵机的调零旋钮,进行调零

*******************************************************************************/

void calibration(unsigned int z)
{
	while(z--)
    {
        left = 1;	   //左轮
    	delay(152);		  // 132 后退最快  152 不动  172 前进最快		  
    	left = 0;	  //左轮	  
    	
    	right = 1;  //右轮
    	delay(152);	 	  // 172 后退最快  152 不动  132 前进最快   	   
    	right = 0;  //右轮
    	
    	delay (1740) ;	   //1740
    }	   
}

/*******************************************************************************
* 功能描述 : 左转
* 函数属性 : 外部
* 输入参数 : unsigned int z
* 返回参数 : 无
* 函数详解 : 
*******************************************************************************/

void turn_left(unsigned int z )
{
    while(z--)
    {
        left = 1;
    	delay(132);		 //1.3ms 132 后退最快  152 不动  172 前进最快   		  
    	left = 0;		  
    	
    	right = 1;
    	delay(132);	 	 // 172 后退最快  152 不动  132 前进最快	   	   
    	right = 0;
    	
    	delay (1740) ;	   //1740

    }		
}

/*******************************************************************************
* 功能描述 : 右转
* 函数属性 : 外部
* 输入参数 : unsigned int z
* 返回参数 : 无
* 函数详解 : 
*******************************************************************************/

void turn_right(unsigned int z )
{
	while(z--)
    {   
		
        left = 1;
    	delay(172);	     //1.7ms 132 后退最快  152 不动  172 前进最快	   		  
    	left = 0;		  
    	
    	right = 1;
    	delay(172);	 	 //1.7ms 172 后退最快  152 不动  132 前进最快	   	   
    	right = 0;
    	
    	delay (1740) ;	   //20ms 1740

    }			
}


/*******************************************************************************
* 功能描述 : 前进
* 函数属性 : 外部
* 输入参数 : unsigned int z
* 返回参数 : 无
* 函数详解 : 
*******************************************************************************/

void go_forward(unsigned int z)
{
	while(z--)
    {   
        left = 1;
    	delay(158);	       //1.7ms   132 后退最快  152 不动  172 前进最快	   		  
    	left = 0;		  
   
    	right = 1;
    	delay(146);	 	   // 172 后退最快  152 不动  132 前进最快	   	   
    	right = 0;
    	
    	delay (1740) ;	   //20ms   1740
    }	   
}

/*******************************************************************************
* 功能描述 : 后退
* 函数属性 : 外部
* 输入参数 : unsigned int z
* 返回参数 : 无
* 函数详解 : 
*******************************************************************************/

void draw_back(unsigned int z)
{
    while(z--)
    {
        left = 1;
    	delay(146);		   //1.3ms 132 后退最快  152 不动  172 前进最快   		  
    	left = 0;		  
    	
    	right = 1;
    	delay(158);	 	  //17ms 172 后退最快  152 不动  132 前进最快	   	   
    	right = 0;
    	
    	delay (1740) ;	   //1740
    }	
}


#endif