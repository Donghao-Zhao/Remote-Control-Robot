#include "usart3.h"
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h" 
#include "pwm.h"

/*********************************************************************************
***********************MCU���� STM32F407������(�����)****************************
**********************************************************************************
* �ļ�����: usart3.c                                                             *
* �ļ�������USART3ʹ��                                                           *
* �������ڣ�2015.03.06                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    �������ô��ڵ������־���USART1����LED��������������                    * 
**********************************************************************************
*********************************************************************************/	

u8 receive_str[USART3_REC_NUM];     //���ջ�������,���USART_REC_LEN���ֽ� 
u8 uart_byte_count=0;

/****************************************************************************
* ��    ��: void uart3_init(u32 bound)
* ��    �ܣ�USART1��ʼ��
* ��ڲ�����bound��������
* ���ز�������
* ˵    ���� 
****************************************************************************/
void uart3_init(u32 bound)
{   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ�� 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //ʹ��USART3ʱ�� 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);  //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10��GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);          //��ʼ��PB10��PB11
   //USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART3, &USART_InitStructure); //��ʼ������1	
  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);         //��������ж�
	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;      //����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		   //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	  //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

//����1����һ���ַ�
void uart3SendChar(u8 ch)
{      
	while((USART3->SR&0x40)==0);  
    USART3->DR = (u8) ch;      
}
/****************************************************************************
* ��    ��: void uart1SendChars(u8 *str, u16 strlen)
* ��    �ܣ�����1����һ�ַ���
* ��ڲ�����*str�����͵��ַ���
            strlen���ַ�������
* ���ز�������
* ˵    ���� 
****************************************************************************/
void uart3SendChars(u8 *str, u16 strlen)
{ 
	  u16 k= 0 ; 
   do { uart3SendChar(*(str + k)); k++; }   //ѭ������,ֱ���������   
    while (k < strlen); 
} 

//����1�жϷ������
void USART3_IRQHandler(void)  
{
	u8 rec_data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж� 
		{
				rec_data =(u8)USART_ReceiveData(USART3);         //(USART1->DR) ��ȡ���յ�������
        if(rec_data=='O')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
					uart_byte_count=0x01; 
				}

			else if(rec_data=='K')		                         //���E����ʾ��������Ϣ���͵Ľ���λ
				{
					if(strcmp("LON",(char *)receive_str)==0)        LED1=0;	//����LED1
					else if(strcmp("LOFF",(char *)receive_str)==0)   LED1=1;	//����LED1
					else if(strcmp("BON",(char *)receive_str)==0)    BEEP=1; 	//��������
					else if(strcmp("BOFF",(char *)receive_str)==0)   BEEP=0; 	//����������
					for(uart_byte_count=0;uart_byte_count<32;uart_byte_count++)receive_str[uart_byte_count]=0x00;
					uart_byte_count=0;    
				}
				else if(rec_data=='W')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						go(0,1,1,3000,4200,1,3000,1,4200);
						delay_ms(100);	
						go(0,1,1,0,1,1,0,1,1); 
				}				
				else if(rec_data=='S')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						go(0,1,1,3000,1,4200,3000,4200,1);
						delay_ms(100);
						go(0,1,1,0,1,1,0,1,1); 
				}	
				else if(rec_data=='A')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						go(2400,4200,1,3000,1,4200,3000,1,4200);
						delay_ms(100);
						go(0,1,1,0,1,1,0,1,1);
				}	
				else if(rec_data=='D')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						
						go(2400,1,4200,3000,4200,1,3000,4200,1);
						delay_ms(100);
						go(0,1,1,0,1,1,0,1,1); 
				}	
				else if(rec_data=='Q')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						go(3500,1,4200,3500,1,4200,3500,1,4200);
						delay_ms(100);
						go(0,1,1,0,1,1,0,1,1);
				}	
				else if(rec_data=='E')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						
						go(3500,4200,1,3500,4200,1,3500,4200,1);
						delay_ms(100);
						go(0,1,1,0,1,1,0,1,1); 
				}	
				else if(rec_data=='R')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						BEEP=1; 
				}			
				else if(rec_data=='F')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
						BEEP=0; 
				}			
				
			else if((uart_byte_count>0)&&(uart_byte_count<=USART3_REC_NUM))
				{
				   receive_str[uart_byte_count-1]=rec_data;
				   uart_byte_count++;
				}                		 
   } 
} 

