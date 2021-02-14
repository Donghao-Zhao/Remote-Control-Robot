#include "pwm.h"
#include "led.h"

/*********************************************************************************
*************************MCU启明 STM32F407核心开发板******************************
**********************************************************************************
* 文件名称: pwm.c                                                                *
* 文件简述：pwm初始化                                                            *
* 创建日期：2015.03.08                                                           *
* 版    本：V1.0                                                                 *
* 作    者：Clever                                                               *
* 说    明：设置PA0(TIM5_CH1)输出PWM波                                           * 
**********************************************************************************
*********************************************************************************/ 	 

/****************************************************************************
* 名    称: void TIM5_PWM_Init(u32 auto_data,u32 fractional)
* 功    能：PWM输出初始化
* 入口参数：auto_data: 自动重装值
*           fractional: 时钟预分频数
* 返回参数：无
* 说    明：设置PA0(TIM5_CH1)输出PWM波      
****************************************************************************/
void TIM3_PWM_Init(u32 auto_data,u32 fractional)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructureB4,GPIO_InitStructureB5,GPIO_InitStructureB0,GPIO_InitStructureB1;
	GPIO_InitTypeDef GPIO_InitStructureD12,GPIO_InitStructureD13;
	GPIO_InitTypeDef GPIO_InitStructureA0,GPIO_InitStructureA7,GPIO_InitStructureE6;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTB时钟	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTA时钟
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3); //GPIOB4复用为定时器3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3); //GPIOB5复用为定时器3
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB0复用为定时器3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB1复用为定时器3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12复用为定时器4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //GPIOD13复用为定时器4
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //GPIOA0复用为定时器5	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14); //GPIOA0复用为定时器5
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9); //GPIOA0复用为定时器5
	
	GPIO_InitStructureB4.GPIO_Pin = GPIO_Pin_4;           //GPIOB4
	GPIO_InitStructureB4.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureB4.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureB4.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureB4.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructureB4);              //初始化PB4

	GPIO_InitStructureB5.GPIO_Pin = GPIO_Pin_5;           //GPIOB5
	GPIO_InitStructureB5.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureB5.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureB5.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureB5.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructureB5);              //初始化PB5

	GPIO_InitStructureB0.GPIO_Pin = GPIO_Pin_0;           //GPIOB0
	GPIO_InitStructureB0.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureB0.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureB0.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureB0.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructureB0);              //初始化PB0
	
	GPIO_InitStructureB1.GPIO_Pin = GPIO_Pin_1;           //GPIOB1
	GPIO_InitStructureB1.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureB1.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureB1.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureB1.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructureB1);              //初始化PB1
	
	GPIO_InitStructureD12.GPIO_Pin = GPIO_Pin_12;           //GPIOD12
	GPIO_InitStructureD12.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureD12.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureD12.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureD12.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructureD12);              //初始化PD12

  GPIO_InitStructureD13.GPIO_Pin = GPIO_Pin_13;           //GPIOD13
	GPIO_InitStructureD13.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureD13.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureD13.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureD13.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructureD13);              //初始化PD13

	GPIO_InitStructureA0.GPIO_Pin = GPIO_Pin_0;           //GPIOA0
	GPIO_InitStructureA0.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureA0.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureA0.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureA0.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructureA0);              //初始化PA0
	
	GPIO_InitStructureA7.GPIO_Pin = GPIO_Pin_7;           //GPIOA0
	GPIO_InitStructureA7.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureA7.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureA7.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureA7.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructureA7);              //初始化PA0
	
	GPIO_InitStructureE6.GPIO_Pin = GPIO_Pin_6;           //GPIOA0
	GPIO_InitStructureE6.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructureE6.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructureE6.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructureE6.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructureE6);              //初始化PA0
	

  TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器3
	
	TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器3
	 
	TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器3
	
	TIM_TimeBaseStructure.TIM_Prescaler=fractional;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//初始化定时器3
	
	TIM_TimeBaseStructure.TIM_Prescaler=83;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=auto_data;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//初始化定时器3
	
	//初始化TIM3 Channel 1.2.3.4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
	
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC4
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC4
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC4
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC4
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 4OC4
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能 
	TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPE使能 
	TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能 
	TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3	
  TIM_Cmd(TIM4, ENABLE);  //使能TIM3	
  TIM_Cmd(TIM5, ENABLE);  //使能TIM3	
	TIM_Cmd(TIM14, ENABLE);  //使能TIM3	
  TIM_Cmd(TIM9, ENABLE);  //使能TIM3	
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
		TIM_SetCompare2(TIM4,D13); //PD13 ENA数值减小，转速增大
		TIM_SetCompare1(TIM4,D12); //PD12 IN1
	 	TIM_SetCompare4(TIM3,B1); //PB1 IN2
		
   	TIM_SetCompare3(TIM3,B0); //PB0 ENB
		TIM_SetCompare1(TIM14,A7); //PA7 IN1 
		TIM_SetCompare2(TIM9,E6); //PE6 IN2
		
		TIM_SetCompare1(TIM5,A0); //PA0 ENA 2
	  TIM_SetCompare1(TIM3,B4);	//PB4 IN1 2
    TIM_SetCompare2(TIM3,B5); //PB5 IN2 2
}



