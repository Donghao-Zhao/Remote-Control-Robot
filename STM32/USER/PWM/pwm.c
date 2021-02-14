#include "pwm.h"
#include "led.h"

/*********************************************************************************
*************************MCU���� STM32F407���Ŀ�����******************************
**********************************************************************************
* �ļ�����: pwm.c                                                                *
* �ļ�������pwm��ʼ��                                                            *
* �������ڣ�2015.03.08                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ��������PA0(TIM5_CH1)���PWM��                                           * 
**********************************************************************************
*********************************************************************************/ 	 

/****************************************************************************
* ��    ��: void TIM5_PWM_Init(u32 auto_data,u32 fractional)
* ��    �ܣ�PWM�����ʼ��
* ��ڲ�����auto_data: �Զ���װֵ
*           fractional: ʱ��Ԥ��Ƶ��
* ���ز�������
* ˵    ��������PA0(TIM5_CH1)���PWM��      
****************************************************************************/
void TIM3_PWM_Init(u32 auto_data,u32 fractional)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructureB4,GPIO_InitStructureB5,GPIO_InitStructureB0,GPIO_InitStructureB1;
	GPIO_InitTypeDef GPIO_InitStructureD12,GPIO_InitStructureD13;
	GPIO_InitTypeDef GPIO_InitStructureA0,GPIO_InitStructureA7,GPIO_InitStructureE6;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTBʱ��	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTAʱ��
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3); //GPIOB4����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3); //GPIOB5����Ϊ��ʱ��3
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB0����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB1����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12����Ϊ��ʱ��4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //GPIOD13����Ϊ��ʱ��4
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //GPIOA0����Ϊ��ʱ��5	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14); //GPIOA0����Ϊ��ʱ��5
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9); //GPIOA0����Ϊ��ʱ��5
	
	GPIO_InitStructureB4.GPIO_Pin = GPIO_Pin_4;           //GPIOB4
	GPIO_InitStructureB4.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureB4.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureB4.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureB4.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructureB4);              //��ʼ��PB4

	GPIO_InitStructureB5.GPIO_Pin = GPIO_Pin_5;           //GPIOB5
	GPIO_InitStructureB5.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureB5.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureB5.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureB5.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructureB5);              //��ʼ��PB5

	GPIO_InitStructureB0.GPIO_Pin = GPIO_Pin_0;           //GPIOB0
	GPIO_InitStructureB0.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureB0.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureB0.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureB0.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructureB0);              //��ʼ��PB0
	
	GPIO_InitStructureB1.GPIO_Pin = GPIO_Pin_1;           //GPIOB1
	GPIO_InitStructureB1.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureB1.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureB1.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureB1.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructureB1);              //��ʼ��PB1
	
	GPIO_InitStructureD12.GPIO_Pin = GPIO_Pin_12;           //GPIOD12
	GPIO_InitStructureD12.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureD12.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureD12.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureD12.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructureD12);              //��ʼ��PD12

  GPIO_InitStructureD13.GPIO_Pin = GPIO_Pin_13;           //GPIOD13
	GPIO_InitStructureD13.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureD13.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureD13.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureD13.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructureD13);              //��ʼ��PD13

	GPIO_InitStructureA0.GPIO_Pin = GPIO_Pin_0;           //GPIOA0
	GPIO_InitStructureA0.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureA0.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureA0.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureA0.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructureA0);              //��ʼ��PA0
	
	GPIO_InitStructureA7.GPIO_Pin = GPIO_Pin_7;           //GPIOA0
	GPIO_InitStructureA7.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureA7.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureA7.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureA7.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructureA7);              //��ʼ��PA0
	
	GPIO_InitStructureE6.GPIO_Pin = GPIO_Pin_6;           //GPIOA0
	GPIO_InitStructureE6.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructureE6.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructureE6.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructureE6.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructureE6);              //��ʼ��PA0
	

  TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	 
	TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	TIM_TimeBaseStructure.TIM_Prescaler=83;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	//��ʼ��TIM3 Channel 1.2.3.4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���
	
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC4
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC4
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC4
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC4
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 4OC4
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPEʹ�� 
	TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ�� 
	TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3	
  TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM3	
  TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM3	
	TIM_Cmd(TIM14, ENABLE);  //ʹ��TIM3	
  TIM_Cmd(TIM9, ENABLE);  //ʹ��TIM3	
}  

void duoji(int a,int b,int c, int d,int e)
	{
		a=a*34+34200;
		b=b*24+36000;
		c=39200-c*20;
		d=d*17+36000;
		e=36800-e*11;

	}
	
	
void forward(int a,int b,int c,int d)
	{
		a=a*400;
		b=b*400;
		c=c*400;
		d=d*400;

	}

void go(int D13,int D12,int B1,int B0,int A7,int E6,int A0,int B4,int B5)
{
		TIM_SetCompare2(TIM4,D13); //PD13 ENA��ֵ��С��ת������
		TIM_SetCompare1(TIM4,D12); //PD12 IN1
	 	TIM_SetCompare4(TIM3,B1); //PB1 IN2
		
   	TIM_SetCompare3(TIM3,B0); //PB0 ENB
		TIM_SetCompare1(TIM14,A7); //PA7 IN1 
		TIM_SetCompare2(TIM9,E6); //PE6 IN2
		
		TIM_SetCompare1(TIM5,A0); //PA0 ENA 2
	  TIM_SetCompare1(TIM3,B4);	//PB4 IN1 2
    TIM_SetCompare2(TIM3,B5); //PB5 IN2 2
}



