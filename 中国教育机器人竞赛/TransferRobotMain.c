/*******************************************************************************
* �ļ��� : main.c
* ʵ�ֹ���:
* �汾     ����            ����            ˵��
* V1.0     NJH             2015/08/10       ��ʼ�汾

* ����   : MCU: STC89C52     ����: 11.0592   MHz

* 		 ���������c�㷽��û���趨���������һ��������ұ�
           
*******************************************************************************/

 #include <reg52.h>
 #include "car.h"
 #include "ultrasonic.h"
 #include <BoeBot.h>
 #include <intrins.h>
 #include "uart.h"
 #include "TransferRobot.h"
	
 
 void main(void)
 {
	test_led();
	s0=1;//---------------------------------����1
	s1=1;	
//	UartInit();	
	T0_init();//----------------------------��ʱ����ʼ��
	Outside_Init();//-----------------------�ⲿ�жϳ�ʼ��
	
	go_forward(100); 

	while(1) //-----------------------------�ӳ���������ת��A�����
	{
		if(Left_2_led != 1) //--------------0��⵽
		{
			tracking();
		}
		else
		{
			calibration(1);
			go_forward(40);		 
			calibration(1);
			break;
		}
	}
	RotationAngle(90);//machine(2,132,132);//-��ת90�ȣ����A���Ƿ������
	calibration(50);

//-------------------�ж�A B C D �Ƿ�����飬����оͰ����Żس�������ǰ��ĺ����ϡ�	
//                 ��ȡ�����ĸ�����ʱ���˳���
	flag_1 = 0;
	while(1)
	{  			 
		JudgeWedges_1(); //--------------------�ж��Ƿ�����飬�������ȡȡ�����󷵻�
		if(Counter<=4)
		GetBodyChoice(Counter);	//-----------�жϴ��ĸ��㿪ʼ�ж�
		if(Counter>4)
			break;
	}


	while(Counter_Wedges>0)
	{

	   GetBlackLineWedges();//----------------�Ӻ��߽���ط�ȥȡ����ת�Ƶ����

		COLOUR = JudgeColour();
		while(COLOUR == 0)
			COLOUR = JudgeColour();

		WedgesAddressChoice(COLOUR);//-------������͵�ָ��������

		Counter_Wedges--;
	}

//	RotationAngle(-90);	//----------��ת90�Ⱥ�
	GetFGHIWedges_Right();   //------------��ȡ��������

	COLOUR = JudgeColour();//--------------�жϵ����������ɫ
	while(COLOUR == 0)
		COLOUR = JudgeColour();

	WedgesAddressChoice(COLOUR);//-------������͵�ָ��������
	GoHome();

	while(1)
		calibration(1000);
	return;		 //����˳�




while(1)
{
//	calibration(100);
//COLOUR = 	   
	JudgeColour(); Delay1ms(100);
//	if(COLOUR==COLOUR_BLACK)
//		go_forward(100);		
//   Return_E();
//JudgeWedges_1();
//ArrangeWedges(3);
//GetBlackLineWedges();
//	PlaceWedges();
//tracking();
//GetFGHIWedges_Left(); 
//RotationAngle(-45);
}
	
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	tracking
 *   ���ã�             ������ѭ��
 *        
 ***************************************************************************************************/

 void tracking(void)
 {
	if(Left_1_led==0&&Centre_1_led==0&&Right_1_led==0)	 //1
	{
		Go_Forward_Counter++;
		go_forward(1);	
	}	
	if(Left_1_led==0&&Centre_1_led==0&&Right_1_led==1)	 //2
		machine(1,146,146);   //��ת
	if(Left_1_led==0&&Centre_1_led==1&&Right_1_led==0)	 //3
		machine(1,158,158);     //��ת
	if(Left_1_led==0&&Centre_1_led==1&&Right_1_led==1)	 //4
		machine(1,146,146);     //��ת
	if(Left_1_led==1&&Centre_1_led==0&&Right_1_led==0)   //5
		machine(1,158,158); 	 //��ת
	if(Left_1_led==1&&Centre_1_led==0&&Right_1_led==1)   //6
	{
		Go_Forward_Counter++;
		go_forward(1);
	}
	if(Left_1_led==1&&Centre_1_led==1&&Right_1_led==0)   //7
		machine(1,158,158); 	 //��ת
	if(Left_1_led==1&&Centre_1_led==1&&Right_1_led==1)   //8
	{
		Go_Forward_Counter++;
		go_forward(1); 
	}
 }

  /***************************************************************************************************
 -
 -	 �������ƣ�	    	RotationAngle
 -   ���ã�             ��ת�Ƕȵ�ѡ��
 -   ������     		 30��45,90,180
 ***************************************************************************************************/
  void RotationAngle(int flag)
  {
		switch(flag)
		{	
			case  ANGLE_LEFT_30:  machine(3,146,146); break;
			
			case  ANGLE_LEFT_45:  machine(19,146,146); break;
			
			case  ANGLE_LEFT_90:  machine(38,146,146); break;
			                          	
			case  ANGLE_LEFT_135: machine(57,146,146); break;
	
			case  ANGLE_LEFT_180: machine(72,146,146); break;	
	
			case  ANGLE_RIGHT_30:  machine(3,158,158); break;
			
			case  ANGLE_RIGHT_45:  machine(16,158,158); break;
			
			case  ANGLE_RIGHT_90:  machine(33,158,158); break;
			                          	
			case  ANGLE_RIGHT_135: machine(48,158,158); break;	
										
			case  ANGLE_RIGHT_180: machine(65,158,158); break;
	
			default :  break;
		}	
  }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	JudgeWedges
 *   ���ã�             �жϻ������飬����н�ǰ��ȥ����飬�õ�����ת180�ȷ���
 *        
 ***************************************************************************************************/
 
 void JudgeWedges_1(void)
 {
    Go_Forward_Counter = 0;
 	while(1)
	{	
		Delay1ms(10);
		if(Counter == 2)		//�ж��Ƿ������
		{
			if(Counter >= 4)
			{
				Counter++;
				RotationAngle(-90);
				calibration(10);
				break;
			}
			else{

			  	RotationAngle(-45); //��ת45
				Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
				calibration(20);			
				
			}

		}	 
		else if(Counter == 0||Counter == 1||Counter == 3||Counter == 4/*||Counter == 2*/)
		{
			if(flag_1 == 0)
			{
				go_forward(25);
				flag_1++;
				LeftGetBlackLine();
			}
			while(1)
			{
				tracking();	  //ѭ��
				if(ultrasonic()<3/*&&ultrasonic()>=0*/)
				{
					if(Counter != 0/*||Counter != 3*/)	//������A���E���ʱ��
					{
						while(Go_Forward_Counter<115)
							tracking();	  //ѭ��
						Go_Forward_Counter = 0;
		
						RotationAngle(180);//��ת//��ת
						calibration(10);
						flag_1=0;
						break;
					}
					else{
						while(Go_Forward_Counter<115)
							tracking();	  //ѭ��
						Go_Forward_Counter = 0;
		
						RotationAngle(-180);//machine(2,132,132);��ת//��ת
						calibration(10);
						flag_1=0;
						break;					
					
					}
				} 
			}
			break;
	    }
   }
 }


 /***************************************************************************************************
 *
 *	 �������ƣ�	    	JudgeWedges
 *   ���ã�             �жϻ������飬����н�ǰ��ȥ����飬�õ�����ת180�ȷ���
 *        
 ***************************************************************************************************/
 
 void JudgeWedges(void)
 {
    Go_Forward_Counter = 0;
 	while(1)
	{	
		Delay1ms(10);
		if(ultrasonic()>25)		//�ж��Ƿ������
		{
			if(Counter >= 4)
			{
				Counter++;
				RotationAngle(-90);
				calibration(10);
				go_forward(10);
				calibration(10);
				break;
			}
			else{

			  	machine(13,172,172); //��ת45
				Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
				calibration(20);			
				
			}

		}	 
		else if(ultrasonic()<25)
		{
			if(flag_1 == 0)
			{
				go_forward(25);
				flag_1++;
			}
			while(1)
			{
				tracking();	  //ѭ��
				if(ultrasonic()<3/*&&ultrasonic()>=0*/)
				{
					if(Counter != 0/*||Counter != 3*/)	//������A���E���ʱ��
					{
						while(Go_Forward_Counter<82)
							tracking();	  //ѭ��
						Go_Forward_Counter = 0;
		
						machine(50,132,132);machine(2,132,132);//��ת//��ת
						calibration(10);
						flag_1=0;
						break;
					}
					else{
						while(Go_Forward_Counter<75)
							tracking();	  //ѭ��
						Go_Forward_Counter = 0;
		
						machine(50,172,172);//machine(2,132,132);��ת//��ת
						calibration(10);
						flag_1=0;
						break;					
					
					}
				} 
			}
			break;
	    }
   }
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	Return_A
 *   ���ã�             ȡ����A������Ժ�����Żس�����
 *        
 ***************************************************************************************************/
 void Return_A(void)
 {

	COLOUR = JudgeColour();	//�ж���ɫ
	while(COLOUR == 0)
		COLOUR = JudgeColour();

   if(COLOUR==COLOUR_YELLOW)//-------------------------����ǻ�ɫ
   {
   		calibration(10);
		RotationAngle(180);//-----------------------��ת180��ָ���ɫ����
		calibration(10);
		LeftGetBlackLine();//-----------------------��ת������ʱ��ͬ��΢ת��Ѱ�Һ���

		while(1)//-----------------------------------�����ŵ���ɫ����
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
//				go_forward(3);	 //��ǰ��һ���ľ��룬�Ѻ�ɫ�����ں�ɫ������
				calibration(1);	 
				break;
			}
		}
//-------------------------------------------------��������	����	
		draw_back(35);
		RotationAngle(-180);//	 machine(2,132,132); //��ת180��
		calibration(10); 
		RightGetBlackLine();//-------------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���
//------------------------------------------------ͨ��ѭ���ص����߽���ĵط�����ָ������������ĺ�����	  	
		
		while(1)
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
				go_forward(40);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
				calibration(10);
				Counter++;		 
				RotationAngle(135);//RotationAngle(45);	 //��ת135�ȣ�ָ��B��
				calibration(10);	 
				break;
			}
		}
   }
   else	//-------------------------������Ǻ�ɫ���Ͱ�����͵����߽��洦�������ж�
   {
		while(1)
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
				go_forward(40);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
				calibration(1);	 
				RotationAngle(-90);	 //��ת90�Ⱥ���ǰ��һ��
				go_forward(25);
				calibration(1);	 
				break;
			}
		}

		RightGetBlackLine();
		Counter_Wedges++;
		ArrangeWedges(Counter_Wedges);
    	RightGetBlackLine();  

		while(1) //�����Żص���������Ҫ���ص�ʮ��·��ͣ��
		{
			if(Left_2_led != 1)
			{
				tracking();
			}
			else
			{
				go_forward(40);		 
				calibration(1);
				break;
			}
		}

		Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
	 	RotationAngle(45);	//��ת��45���Ժ�ָ����B��
		calibration(10);	 

   }


 }


 /***************************************************************************************************
 *
 *	 �������ƣ�	    	Return_B
 *   ���ã�             ȡ����B������Ժ�����Żس�����
 *        
 ***************************************************************************************************/
 void Return_B(void)
 {
	LeftGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	COLOUR = JudgeColour();	//�ж���ɫ
	while(COLOUR == 0)
		COLOUR = JudgeColour();

   if(COLOUR==COLOUR_WHITE)//-------------------------����ǰ�ɫ
   {
   		calibration(10);
		RotationAngle(180);//-----------------------��ת180��ָ���ɫ����
		calibration(10);
		LeftGetBlackLine();//-----------------------��ת������ʱ��ͬ��΢ת��Ѱ�Һ���

		PlaceWedges(); //����飬Ȼ�󷵻غ��佻��ĵط�

		go_forward(20);	
		RotationAngle(45);
		RotationAngle(90);//-----------------------��ת90��ָ���ɫ����
		Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
		calibration(20);

   }
   else if(COLOUR==COLOUR_YELLOW){//���Ϊ��ɫ

		while(1)
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
				go_forward(50);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
				calibration(10);	 
				RotationAngle(-45);RotationAngle(-90);	
				go_forward(30);
				calibration(10);	 
				break;
			}
		}  
		
		LeftGetBlackLine();

		PlaceWedges(); //����飬Ȼ�󷵻غ��佻��ĵط�
		Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
		RotationAngle(90);	//��ת90��ָC��
		calibration(10);
   
   }
   else{

		while(1)
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
				go_forward(55);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
				calibration(10);	 
				RotationAngle(-45);	 //��ת45�Ⱥ���ǰ��һ��
				go_forward(30);
				calibration(10);	 
				break;
			}
		}
	
		LeftGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

		Counter_Wedges++;
	
		ArrangeWedges(Counter_Wedges); //����ת�Ƶ������ϵ�����
	
		RightGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���
			 	 
		while(1) //�����Żص���������Ҫ���ص�ʮ��·��ͣ��
		{
			if(Left_2_led != 1)
			{
				tracking();
			}
			else
			{
				go_forward(40);		 
				calibration(10);
				break;
			}
		}
		Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
		calibration(10);   
   
   }

 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	Return_C
 *   ���ã�             ȡ����C������Ժ�����Żس����� ������·�ں�ָ����D��
 *        
 ***************************************************************************************************/
 void Return_C(void)
 {
	
	LeftGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	COLOUR = JudgeColour();	//�ж���ɫ
	while(COLOUR == 0)
		COLOUR = JudgeColour();

   if(COLOUR==COLOUR_RED)//-------------------------����Ǻ�ɫ
   {
   		calibration(10);
		RotationAngle(180);//-----------------------��ת180��ָ���ɫ����
		calibration(10);
		LeftGetBlackLine();//-----------------------��ת������ʱ��ͬ��΢ת��Ѱ�Һ���

		PlaceWedges(); //����飬Ȼ�󷵻غ��佻��ĵط�

		go_forward(30);	
		RotationAngle(45); RotationAngle(90); //machine(2,132,132);//��תָ��D��
		Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
		calibration(10);

   }
	else{

		while(1)//--------------------------ͨ��ѭ���ص����߽���ĵط���Ȼ��ת���ɫ����C��
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
				go_forward(63);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
				calibration(10);	 
 
				break;
			}
		 }

		 if(COLOUR!=COLOUR_WHITE&&COLOUR!=COLOUR_YELLOW)
		 {
		  	go_forward(20);	

			LeftGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

			Counter_Wedges++;
		
			ArrangeWedges(Counter_Wedges); //����ת�Ƶ������ϵ�����
		
			RightGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���	

			while(1)//--------------------------ͨ��ѭ���ص����߽���ĵط���Ȼ��ת���ɫ����C��
			{
				if(Left_2_led != 1)
				{
					tracking();	  //ѭ��
				}
				else
				{
					go_forward(40);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
					calibration(10);	 
	 				RotationAngle(-45);	 //��ת45��ָ��D��
					Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
					calibration(10);
					break;
				}
			 }
				 
		 }
		 else{
	
			 RotationAngle(180);
			 calibration(10);	
	
			 WedgesAddressChoice(COLOUR);//�Ӻ��߽���ĵط�ǰ��ָ����ɫ������
	
		 	 RotationAngle(135);//RotationAngle(45);//��ת135�ȣ�ָ��D��
			 Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE

			 calibration(10);	 				 
		 
		 }	
	
	}
	
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	Return_D
 *   ���ã�             ȡ����D������Ժ�����Żس����� ������·�ں�ָ����E��
 *        
 ***************************************************************************************************/
 void Return_D(void)
 {

	LeftGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	COLOUR = JudgeColour();
	while(COLOUR == 0)
		COLOUR = JudgeColour();  

   if(COLOUR==COLOUR_BLACK)//-------------------------����Ǻ�ɫ
   {
   		calibration(10);
		RotationAngle(180);//-----------------------��ת180��ָ���ɫ����
		calibration(10);
		LeftGetBlackLine();//-----------------------��ת������ʱ��ͬ��΢ת��Ѱ�Һ���

		PlaceWedges(); //����飬Ȼ�󷵻غ��佻��ĵط�

		go_forward(23);		
		calibration(10);
		RotationAngle(45); RotationAngle(90); //��תָ��E��
		Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
		calibration(10);

   }
   else{

		while(1)//--------------------------ͨ��ѭ���ص����߽���ĵط���Ȼ��ת���ɫ����C��
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
				go_forward(60);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
				calibration(10);	 
				break;
			}
		 }
		 
		 if(COLOUR!=COLOUR_WHITE&&COLOUR!=COLOUR_YELLOW&&COLOUR!=COLOUR_RED) 
		 {
		 	RotationAngle(45);
			calibration(10);
		  	go_forward(15);	
			calibration(10);

			LeftGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

			Counter_Wedges++;
		
			ArrangeWedges(Counter_Wedges); //����ת�Ƶ������ϵ�����
		
			RightGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���	

			while(1)//--------------------------ͨ��ѭ���ص����߽���ĵط���Ȼ��ת���ɫ����C��
			{
				if(Left_2_led != 1)
				{
					tracking();	  //ѭ��
				}
				else
				{
					go_forward(40);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
					calibration(10);	 
	 				RotationAngle(-90);//machine(3,132,132);	 //��ת45��ָ��E��
					Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
					calibration(10);
					break;
				}
			 }		 
		 
		 }
		 else{

			 RotationAngle(-90);RotationAngle(-45);
			 calibration(10);	 
			 WedgesAddressChoice(COLOUR);//�Ӻ��߽���ĵط�ǰ��ָ����ɫ������
	
		 	 RotationAngle(90);//��ת90�ȣ�ָ��E��
			 Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
			 calibration(10);			 		 		 
		 }
   }

 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	Return_E
 *   ���ã�             ��D��������ʱ��
 *				
 ***************************************************************************************************/
 void Return_E(void)
 {
	LeftGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	COLOUR = JudgeColour();
	while(COLOUR == 0)
		COLOUR = JudgeColour();  

   if(COLOUR==COLOUR_BLUE)//-------------------------�������ɫ
   {
   		calibration(10);
		RotationAngle(-180);//-----------------------��ת180��ָ����ɫ����
		calibration(10);
		RightGetBlackLine();//-----------------------��ת������ʱ��ͬ��΢ת��Ѱ�Һ���

		PlaceWedges(); //����飬Ȼ�󷵻غ��佻��ĵط�
		go_forward(23);
		RotationAngle(90); //��תָ�����������
		Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
		calibration(10);


   }
   else{
		while(1)//--------------------------ͨ��ѭ���ص����߽���ĵط���Ȼ��ת���ɫ����C��
		{
			if(Left_2_led != 1)
			{
				tracking();	  //ѭ��
			}
			else
			{
				go_forward(60);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
				calibration(10);	 
				RotationAngle(-90);
				calibration(10);	 
				break;
			}
		 } 
		 
		 WedgesAddressChoice(COLOUR);//�Ӻ��߽���ĵط�ǰ��ָ����ɫ������
		 Counter++;		  //CounterΪ0ʱΪA,1ΪB��2ΪC��3ΪD��4ΪE
   
   }

 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GetBodyChoice
 *   ���ã�             ȥ�����󷵻ص�·��ѡ��
 *        
 ***************************************************************************************************/
 void GetBodyChoice(unsigned char counter)
 {
	switch(counter)
	{	
		case  0:  Return_A(); break;
		
		case  1:  Return_B(); break;
		
		case  2:  Return_C(); break;
		                          	
		case  3:  Return_D(); break;

		case  4:  Return_E(); break;

		default :  break;
	}	 
 
 }


 
 /***************************************************************************************************
 *
 *	 �������ƣ�	    	WedgesAddressChoice
 *   ���ã�             �����ӽ��洦�ͻ�ָ����ɫ�����ѡ��
 *   ������          	��ʲô��ɫ
 *        
 ***************************************************************************************************/
 void WedgesAddressChoice(unsigned char x)
 {
	switch(x)
	{	
		case  COLOUR_RED:    GoRedAddress(); break;	 //��ɫ
		
		case  COLOUR_WHITE:  GoWhiteAddress(); break;	 //��ɫ
		
		case  COLOUR_BLUE:   GoBlueAddress(); break;	 //��ɫ
		                          	
		case  COLOUR_BLACK:  GoBlackAddress(); break;	 //��ɫ

		case  COLOUR_YELLOW: GoYellowAddress(); break;  //��ɫ

		default :  break;
	}	  	 
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GoRedAddress
 *   ���ã�             �����ӽ��洦�ͻغ�ɫ����
 *   ������          	
 *        
 ***************************************************************************************************/
 void GoRedAddress(void)
 {
 	go_forward(25);	
	calibration(2);

	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1)//------------------------------�����ŵ���ɫ����
	{
		if(Left_2_led != 1/*||Right_2_led != 0*/)
		{
			tracking();//-------------------ѭ��
		}
		else
		{
//			go_forward(3);
			calibration(1);	 
			break;
		}
	}
	
	draw_back(35);//------------------------��������	����
	RotationAngle(180);//machine(2,132,132);//��ת180��
	calibration(10); 
	  
	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1)
	{
		if(Left_2_led != 1/*||Right_2_led != 1*/)
		{
			tracking();	  //ѭ��
		}
		else
		{

			go_forward(62);	//--------------����·��̫����ߣ���������Ҫ��ǰ��һ���ľ������ѭ��
			calibration(10);	 
			break;
		}
	}
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GoWhiteAddress
 *   ���ã�             �����ӽ��洦�ͻذ�ɫ����
 *   ������          	
 *        
 ***************************************************************************************************/
 void GoWhiteAddress(void)
 {
	RotationAngle(45);	 
	calibration(2);
	go_forward(25);

	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1)//------------------------------�����ŵ���ɫ����
	{
		if(Left_2_led != 1/*||Right_2_led != 0*/)
		{
			tracking();	//------------------ѭ��
		}
		else
		{
//			go_forward(2);
			calibration(1);	 
			break;
		}
	}
	
	draw_back(35);//------------------------��������	����
	RotationAngle(180);//machine(2,132,132);//��ת180��
	calibration(10); 
	  
	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1)//------------------------------ͨ��ѭ���ص����߽���ĵط�����ָ������������ĺ�����
	{
		if(Left_2_led != 1/*||Right_2_led != 1*/)
		{
			tracking();	  //----------------ѭ��
		}
		else
		{
			go_forward(62);	//--------------�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
			calibration(10);	 
			RotationAngle(-45);	//----------��ת45�Ⱥ���ǰ��һ��
//			go_forward(5);
			calibration(20);	 
			break;
		}
	}


 }
 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GoBlueAddress
 *   ���ã�             �����ӽ��洦�ͻ���ɫ����
 *   ������          	
 *        
 ***************************************************************************************************/
 void GoBlueAddress(void)
 {
	RotationAngle(-90);	 
	calibration(2);
	go_forward(25);

//	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���
	RightGetBlackLine();

	while(1)//------------------------------�����ŵ���ɫ����
	{
		if(Left_2_led != 1)
		{
			tracking();	  //----------------ѭ��
		}
		else
		{
			go_forward(12);
			calibration(1);	 
			break;
		}
	}

	draw_back(35);//-----------------------��������	����	
	RotationAngle(180);machine(2,132,132);//��ת180��
	calibration(10); 

//--------------------------ͨ��ѭ���ص����߽���ĵط�����ָ������������ĺ�����
	  
	LeftGetBlackLine();//------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1) //----------------------------ѭ���ص������
	{
		if(Left_2_led != 1)
		{
			tracking();	  //---------------ѭ��
		}
		else
		{
			go_forward(60);	//-------------�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
			RotationAngle(90);
			calibration(10);	 
//			go_forward(15);
//			calibration(10);	
			break; 
		}
	} 

 }
 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GoBlackAddress
 *   ���ã�             �����ӽ��洦�ͻغ�ɫ����
 *   ������          	
 *        
 ***************************************************************************************************/
 void GoBlackAddress(void)
 {
	RotationAngle(-45);	 
	calibration(2);
	go_forward(25);

	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1)//------------------------------�����ŵ���ɫ����
	{
		if(Left_2_led != 1/*||Right_2_led != 0*/)
		{
			tracking();	  //ѭ��
		}
		else
		{
//			go_forward(3);
			calibration(1);	 
			break;
		}
	}

	draw_back(35); //-------------------------��������	����	
	RotationAngle(180);//machine(2,132,132);//--��ת180��
	calibration(10); 

//------------------------------ͨ��ѭ���ص����߽���ĵط�����ָ������������ĺ�����	 
 
	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1)
	{
		if(Left_2_led != 1/*||Right_2_led != 1*/)
		{
			tracking();	  //-----------------ѭ��
		}
		else
		{
		
			go_forward(65);	//---------------�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
			calibration(10);	 
			RotationAngle(45);
//			go_forward(5);
			calibration(10);	 
			break;
		}
	}
 
 }
 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GoYellowAddress
 *   ���ã�             �����ӽ��洦�ͻػ�ɫ����
 *   ������          	
 *        
 ***************************************************************************************************/
 void GoYellowAddress(void)
 {
	RotationAngle(90);	 
	calibration(2);
	go_forward(25);

	LeftGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���


	while(1)//------------------------------�����ŵ���ɫ����
	{
		if(Left_2_led != 1/*||Right_2_led != 0*/)
		{
			tracking();	  //ѭ��
		}
		else
		{
//			go_forward(1);
			calibration(10);	 
			break;
		}
	}
	
	draw_back(35);//------------------------��������	����
	RotationAngle(-180);//	 machine(2,132,132); //��ת180��
	calibration(10); 

//------------------------------------ͨ��ѭ���ص����߽���ĵط�����ָ������������ĺ�����
	  
	RightGetBlackLine();//-------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���

	while(1) //-----------------------------ѭ���ص������
	{
		if(Left_2_led != 1)
		{
			tracking();	  //----------------ѭ��
		}
		else
		{
			go_forward(40);	//--------------�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
			calibration(10);	 
			RotationAngle(-90);	//----------��ת90�Ⱥ���ǰ��һ��
//			go_forward(10);
			calibration(10);	 
			break;
		}
	} 
 
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GetBlackLineWedges
 *   ���ã�             �ӽ��洦ȥȡ�����������ϵ����,�������ͻغ��ߵĽ��洦
 *   ������          	
 *        
 ***************************************************************************************************/
 void GetBlackLineWedges(void)
 {
//	LeftGetBlackLine();//--------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���
	Flag_Rotate = 0;
	flag_1 = 0;
	Go_Forward_Counter = 0;

	go_forward(10);

	while(Left_1_led==1&&Centre_1_led==1&&Right_1_led==1)
	{
		if(Flag_Rotate<15)
		{
			 machine(1,146,146); //����ⲻ����ʱ��Դ����ת
			 calibration(2);
			 Flag_Rotate++;
		}
		else{
			 machine(1,158,158); //����ⲻ����ʱ��Դ����ת
			 calibration(2);
			 Flag_Rotate++;		
		}
	}

	while(1)
	{
		if(flag_1 == 0)
		{
			go_forward(5);
			flag_1++;
		}
		tracking();	  //ѭ��
		
		if(ultrasonic()<=1/*&&ultrasonic()>=0*/)
		{
			Go_Forward_Counter = 0;
			while(Go_Forward_Counter<17)
				tracking();	  //ѭ��
			Go_Forward_Counter = 0;
			calibration(5);
			RotationAngle(-180);//��ת//��ת
			calibration(10);
			flag_1 = 0;
			break;
		} 
	}

	RightGetBlackLine();//����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���
	
	while(1) //ȡ�����󷵻ص�ʮ��·��ͣ��
	{
		if(Left_2_led != 1/*||Right_2_led != 1*/)
		{
			tracking();
		}
		else
		{
			go_forward(40);		 
			calibration(10);
			break;
		}
	}			
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	LeftGetBlackLine
 *   ���ã�             ����ת�ǶȲ�����ʱ��ͨ��С�Ƕȵ���ת�Һ���
 *   ������          	
 *        
 ***************************************************************************************************/
 void LeftGetBlackLine(void)
 {
	while(Left_1_led==1&&Centre_1_led==1&&Right_1_led==1)  //�����������߶���ⲻ��ʱ��
	{
		 machine(2,132,132); //����ⲻ����ʱ��Դ����ת
		 calibration(2);
	} 
 
 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	RightGetBlackLine
 *   ���ã�             ����ת�ǶȲ�����ʱ��ͨ��С�Ƕȵ���ת�Һ���
 *   ������          	
 *        
 ***************************************************************************************************/
 void RightGetBlackLine(void)
 {
	while(Left_1_led==1&&Centre_1_led==1&&Right_1_led==1)  //�����������߶���ⲻ��ʱ��
	{
		 calibration(2);
		 machine(1,172,172); //����ⲻ����ʱ��Դ����ת
		 
	} 
 
 }




 /***************************************************************************************************
 *
 *	 �������ƣ�	    	ArrangeWedges
 *   ���ã�             ����ת������ٺ�����
 *   ������          	
 *        
 ***************************************************************************************************/
 void ArrangeWedges(unsigned char y)
 {
 	Go_Forward_Counter = 0;

	switch(y)
	{	
		case  1:  
			while(1)
			{
				if(Left_2_led != 1)
				{
					tracking();	  //ѭ��
				}
				else
				{
					go_forward(18);
					calibration(1);	 
					break;
				}
			}

			draw_back(35);//��������	����
			RotationAngle(-180);//	 machine(3,172,132); //��ת180��
			calibration(10);

	 	break;
		
		case  2:  
		 	while(Go_Forward_Counter<120)
				tracking();	  //ѭ��
			Go_Forward_Counter = 0;
		
			draw_back(35);//��������	����
			RotationAngle(-180);//	 machine(3,132,132); //��ת180��
			calibration(10);	
			
		 break;
		
		case  3: 
			while(Go_Forward_Counter<90)
				tracking();	  //ѭ��
			Go_Forward_Counter = 0;
		
			draw_back(35);//��������	����
			RotationAngle(-180);//	 machine(3,132,132); //��ת180��
			calibration(10);
				
		 break;
		                          	

		default :  break;
	}	 
 
 }

/***************************************************************************************************
 *
 *	 �������ƣ�	    	JudgeColour
 *   ���ã�             �ж�������ɫ
 *   ����ֵ��           ������ɫ���ص�ֵ
 *        
 ***************************************************************************************************/
int JudgeColour()
{
	LED=1;//LED	
//	whitebalance();
	while(1)
	{	
		
		pulses=0;
		time=0;
		TR0=1; 
		s2=0;						  
		s3=0;
		//ѡ���ɫ�˹�
		while(time!=t[0]);
			red=pulses;
		TR0=0;
		time=0;
		pulses=0;
		TR0=1;
		//ѡ����ɫ�˹�
		s2=1;
		s3=1;
		while(time!=t[2]);
			green=pulses;
		TR0=0;      
		time=0;
		pulses=0;
		TR0=1; 
		//ѡ����ɫ�˹�
		s2=0;
		s3=1;
		while(time!=t[1]); 
			blue=pulses;
		TR0=0;
		time=0;
		pulses=0;
		//�رն�ʱ��������ֻΪ��ʾ��
		//	     printf("red=%ld,green=%ld,blue=%ld\n",red,green,blue);
		red = red/3.6;green = green/3.9;blue = blue/3.9; 
		UART_Send_Str("red=");
		UART_Put_Num(red);
		UART_Send_Str("\n");
		UART_Send_Str("green=");
		UART_Put_Num(green);
		UART_Send_Str("\n");
		UART_Send_Str("blue=");
		UART_Put_Num(blue);
		UART_Send_Str("\n");
		delay_nms(200);

//---------------------------------------------------��ɫ
		if(red<10&&blue<10&&green<10)
		{
				UART_Send_Str("��ɫ");
				LED = 0;//LED	
				return COLOUR_BLACK;     
		}


//---------------------------------------------------��ɫ
		if(30<red/*&&red<80*/&&30<green/*&&green<80*/&&30<blue/*&&blue<90*/)
		{
//			if((-10)<(red-green)&&(red-green)<10&&(-10)<(blue-green)&&(blue-green)<10&&(-10)<(blue-red)&&(blue-red)<10)
//			{
				UART_Send_Str("��ɫ");
				LED = 0;//LED	
				return COLOUR_WHITE;  
//			}   
		}

//---------------------------------------------------��ɫ
		if(red<blue&&green<blue&&red<green&&blue<30&&10<blue)
		{
				UART_Send_Str("��ɫ");
				LED = 0;//LED	
				return COLOUR_BLUE;     
		}

//---------------------------------------------------��ɫ
		if(red>blue&&green>blue&&red>green&&red>30&&green>20)
		{
				UART_Send_Str("��ɫ");
				LED = 0;//LED	
				return COLOUR_YELLOW;     
		}

//---------------------------------------------------��ɫ
		if(red>blue&&red>green&&(-9)<(blue-green)&&(blue-green)<9&&red<45&&green<20)
		{
				UART_Send_Str("��ɫ");
				LED = 0;//LED	
				return COLOUR_RED;     
		}

		return 0;
	}
}

/***************************************************************************************************
 *
 *	 �������ƣ�	    	whitebalance
 *   ���ã�             ��ȡ��ƽ��ʱ�ı���ϵ�����⺯��������û���õ�
 *   ����ֵ��           
 *        
 ***************************************************************************************************/
void whitebalance()
{
	unsigned char i;	
	UartInit();	
	T0_init();//��ʱ����ʼ��
	
	Outside_Init();//�ⲿ�жϳ�ʼ��
	//Time2_init(); //���ڳ�ʼ��

	s2=0;//��ɫ
	s3=0;
	TR0=1;
//	UART_Send_Str("����\n");   
//	UART_Put_Num(pulses);
	while(pulses<255)
		t[0] =time;//�洢ϵ�� 
    
	TR0=0;
	time=0;
	pulses=0;	
	s2=0;//��ɫ
	s3=1;
	TR0=1;	
	while(pulses<255)							    
		t[1] =time;//�洢ϵ��
	TR0=0;
	time=0;
	pulses=0;	
	s2=1;//��ɫ
	s3=1;
	TR0=1;
	while(pulses<255)
		t[2] =time;//�洢ϵ��
	TR0=0;	   
	for(i=0;i<3;i++)
	{
	//printf("%ld\n",t[i]);//�������ϵ��
		UART_Put_Num(t[i]);
	} 	
}
	/*----------------------------------------------------------------
      ��������Time2_init( ) 
      ��  �ܣ�ʹ��T2������ʱ��
-----------------------------------------------------------------*/
//void Time2_init(void)
//{
//	EA = 1;
//	T2MOD = 0; 
//	T2CON |= 0x10;
//	SCON = 0x50 ;
//	TH2 = (65536 - 36)/256;
//	TL2 = (65536-36)%256;
//	RCAP2H = (65536 - 36)/256;
//	RCAP2L =(65536 - 36)%256;
//	TR2 = 1;	 
//	TI = 1;
//}
void T0_init()//��ʱ��0��ʼ��
{ 
    TMOD |=0x01;//���ö�ʱ��0Ϊ������ʽ1										
    TH0 =0xfc;//װ��ֵ
    TL0 =0x66;     //���������11.0592MHZ�Ļ��������0.00017%
    EA=1;//�����ж�
    ET0=1;//��ʱ��0�ж�
//    TR0=1;//������ʱ��0
}
//��ʱ��0����ж�//
void c1ms_out() interrupt 1//1ms�ж��ӳ���
{
	TR0=0;
	time=time+1;
	TH0=0xfc;
	TL0=0x66+TL0;
	TR0=1;  
}
void Outside_Init() //�ⲿ�ж�0��ʼ��
{ 	
	EA = 1;     //�����ж� 
	EX0 = 1;   //���ⲿ�ж�0   
	IT0 = 1;   //�½��ش���      
}  
void Outside_Int() interrupt 0 //�ⲿ�ж�0 
{  
	pulses=pulses+1;
//	UART_Put_Num(8);

}


/***************************************************************************************************
 *
 *	 �������ƣ�	    	test_led
 *   ���ã�             led���� ��˸3��
 *   ����ֵ��           
 *        
 ***************************************************************************************************/
void test_led()
{
	unsigned char i;
	for(i=0;i<3;i++)
	{
		LED=0;
		delay_nms(200);
		LED=1;
		delay_nms(200);
	}
	LED=0;
}


 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GetFGHIWedges
 *   ���ã�             ��ȡ��FGHI������
 *        
 ***************************************************************************************************/
 void GetFGHIWedges_Right(void)
 {
 	Counter_FGHI = 0;
	while(1)
	{	
		if(ultrasonic()>20)		//�ж��Ƿ������
		{
		  	RotationAngle(30); //��ת30
			Counter_FGHI++;		 
			calibration(20);

			if(Counter_FGHI==17)
			{
			 	RotationAngle(-90);
				calibration(50);
				Counter_FGHI = 0;
			}
		}	 
		else if(ultrasonic()<20)
		{
			go_forward(3);

			if(ultrasonic()<3/*&&ultrasonic()>=0*/)
			{
				go_forward(25);

				while(1)
				{
					if(Left_2_led != 1)
					{
						go_forward(1);
					}
					else
					{
						go_forward(38);
//						if(Counter_FGHI>=4)
//							 go_forward(15);
						calibration(10);
						machine(36,158,158);
						calibration(10);
						break;
					}
			    }					
				break;
			  }
			 			
			}
   }

//	if(Counter_FGHI<=4)
//	{
//		LeftGetBlackLine();
//	}
//	else
//	{
		RightGetBlackLine();
//	}

	while(1) 
	{
		if(Left_2_led != 1)
		{
			tracking();
		}
		else
		{
			go_forward(60);		 
			calibration(10);
			break;
		}
	} 

	RotationAngle(-135);
	go_forward(20);
	LeftGetBlackLine();
   
	while(1) 
	{
		if(Left_2_led != 1)
		{
			tracking();
		}
		else
		{
			go_forward(40);		 
			calibration(10);
			break;
		}
	} 

 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GetFGHIWedges
 *   ���ã�             ��ȡ��FGHI������
 *        
 ***************************************************************************************************/
 void GetFGHIWedges_Left(void)
 {
 	Counter_FGHI = 0;
	while(1)
	{	
		if(ultrasonic()>20)		//�ж��Ƿ������
		{
		  	RotationAngle(30); //��ת30
			Counter_FGHI++;		 
			calibration(20);

			if(Counter_FGHI==17)
			{
			 	RotationAngle(-90);
				calibration(50);
				Counter_FGHI = 0;
			}
		}	 
		else if(ultrasonic()<20)
		{
			go_forward(3);

			if(ultrasonic()<3/*&&ultrasonic()>=0*/)
			{
				go_forward(25);

				while(1)
				{
					if(Left_2_led != 1)
					{
						go_forward(1);
					}
					else
					{
						go_forward(20);
						if(Counter_FGHI>=4)
							 go_forward(15);
						calibration(10);
						machine(40,146,146);
						calibration(10);
						break;
					}
			    }
				break;	
			  }

			 		
		}
   }

	if(Counter_FGHI<=8)
	{
		LeftGetBlackLine();
	}
	else
	{
		RightGetBlackLine();
	}

	while(1) 
	{
		if(Left_2_led != 1)
		{
			tracking();
		}
		else
		{
			go_forward(45);		 
			calibration(10);
			break;
		}
	} 

	RotationAngle(135);
	go_forward(20);
	RightGetBlackLine();
   
	while(1) 
	{
		if(Left_2_led != 1)
		{
			tracking();
		}
		else
		{
			go_forward(40);		 
			calibration(10);
			break;
		}
	} 

 }

 /***************************************************************************************************
 *
 *	 �������ƣ�	    	GoHome
 *   ���ã�             ���������С���Ӻ��ߵ����Ļص�������
 *        
 ***************************************************************************************************/

 void GoHome(void)
 {
 	go_forward(25);
	calibration(5);
 	LeftGetBlackLine();
	while(1)
	{
		if(Left_2_led != 1)
		{
			tracking();	  //ѭ��
		}
		else
		{
			go_forward(115); 
			calibration(10);	 
			break;
		}
	}
	while(1)//--------------------------------�����˽�����ֹͣ
 		calibration(1000);
 }


 /***************************************************************************************************
 *
 *	 �������ƣ�	    	PlaceWedges
 *   ���ã�             ������飬Ȼ��ص����ߵĽ��洦��
 *        
 ***************************************************************************************************/
 void PlaceWedges(void)
 {
	while(1)//-----------------------------------�����ŵ�����ɫ������
	{
		if(Left_2_led != 1)
		{
			tracking();	  //ѭ��
		}
		else
		{
			if(COLOUR==COLOUR_BLUE)
				go_forward(15);	 //��ǰ��һ���ľ��룬�Ѻ�ɫ�����ں�ɫ������
			calibration(1);	 
			break;
		}
	}
//-------------------------------------------------��������	����
	if(COLOUR==COLOUR_YELLOW)
	{	
		draw_back(35);
		RotationAngle(-180);	
		calibration(10); 	 
	 	RightGetBlackLine();
	 }
	 else{
		draw_back(35);
		RotationAngle(180);	// machine(2,132,132); //��ת180��
		calibration(10); 
		LeftGetBlackLine();//-------------------------����ת�ĽǶȲ�����ʱ��ͬ������΢ת��Ѱ�Һ���
	 }
//------------------------------------------------ͨ��ѭ���ص����߽���ĵط�����ָ������������ĺ�����	  
	
	
	while(1)
	{
		if(Left_2_led != 1)
		{
			tracking();	  //ѭ��
		}
		else
		{
			go_forward(40);	//�����߼�⵽ʮ��·�ں���ǰ��һ�㱣֤��ʮ��·�ڵ�����λ��
			calibration(10);	 
			break;
		}
	} 

 }

