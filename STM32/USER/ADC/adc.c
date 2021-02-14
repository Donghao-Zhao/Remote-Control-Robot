#include "adc.h"	 
/*********************************************************************************
*************************MCU���� STM32F407���Ŀ�����******************************
**********************************************************************************
* �ļ�����: adc.c                                                                *
* �ļ�������adc��ʼ��                                                            *
* �������ڣ�2015.03.07                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ����                                                                     * 
**********************************************************************************
*********************************************************************************/	


//��ʼ��ADC															   
void  ADC1_Init(void)
{    
  GPIO_InitTypeDef  GPIO_InitStructure1,GPIO_InitStructure2,GPIO_InitStructure3;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ�
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��
	

  //�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_5;//PA5 ͨ��5
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure1);//��ʼ�� 
	
	//�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_4;//PA5 ͨ��5
  GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOC, &GPIO_InitStructure2);//��ʼ��  
	
	  //�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_7;//PA5 ͨ��5
  GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure3);//��ʼ��  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
 
	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
  ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
	
	ADC_Cmd(ADC1, ENABLE);//����ADת����	
}


/****************************************************************************
* ��    ��: u16 Get_Adc(u8 ch) 
* ��    �ܣ����ADCֵ
* ��ڲ�����ch: ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
* ���ز�����12λADC��Чֵ
* ˵    ����       
****************************************************************************/
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

/****************************************************************************
* ��    ��: u16 Get_Adc_Average(u8 ch,u8 times) 
* ��    �ܣ���ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
* ��ڲ�����ch: ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
*           times:��ȡ����
* ���ز�����ͨ��ch��times��ת�����ƽ��ֵ
* ˵    ����       
****************************************************************************/
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
