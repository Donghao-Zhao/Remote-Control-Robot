#include "adc.h"	 
/*********************************************************************************
*************************MCUÆôÃ÷ STM32F407ºËÐÄ¿ª·¢°å******************************
**********************************************************************************
* ÎÄ¼þÃû³Æ: adc.c                                                                *
* ÎÄ¼þ¼òÊö£ºadc³õÊ¼»¯                                                            *
* ´´½¨ÈÕÆÚ£º2015.03.07                                                           *
* °æ    ±¾£ºV1.0                                                                 *
* ×÷    Õß£ºClever                                                               *
* Ëµ    Ã÷£º                                                                     * 
**********************************************************************************
*********************************************************************************/	


//³õÊ¼»¯ADC															   
void  ADC1_Init(void)
{    
  GPIO_InitTypeDef  GPIO_InitStructure1,GPIO_InitStructure2,GPIO_InitStructure3;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//Ê¹ÄÜGPIOAÊ±Ö
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Ê¹ÄÜADC1Ê±ÖÓ
	

  //ÏÈ³õÊ¼»¯ADC1Í¨µÀ5 IO¿Ú
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_5;//PA5 Í¨µÀ5
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AN;//Ä£ÄâÊäÈë
  GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_NOPULL ;//²»´øÉÏÏÂÀ­
  GPIO_Init(GPIOA, &GPIO_InitStructure1);//³õÊ¼»¯ 
	
	//ÏÈ³õÊ¼»¯ADC1Í¨µÀ5 IO¿Ú
  GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_4;//PA5 Í¨µÀ5
  GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AN;//Ä£ÄâÊäÈë
  GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL ;//²»´øÉÏÏÂÀ­
  GPIO_Init(GPIOC, &GPIO_InitStructure2);//³õÊ¼»¯  
	
	  //ÏÈ³õÊ¼»¯ADC1Í¨µÀ5 IO¿Ú
  GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_7;//PA5 Í¨µÀ5
  GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_AN;//Ä£ÄâÊäÈë
  GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_NOPULL ;//²»´øÉÏÏÂÀ­
  GPIO_Init(GPIOA, &GPIO_InitStructure3);//³õÊ¼»¯  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1¸´Î»
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//¸´Î»½áÊø	 
 
	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//¶ÀÁ¢Ä£Ê½
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//Á½¸ö²ÉÑù½×¶ÎÖ®¼äµÄÑÓ³Ù5¸öÊ±ÖÓ
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAÊ§ÄÜ
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ô¤·ÖÆµ4·ÖÆµ¡£ADCCLK=PCLK2/4=84/4=21Mhz,ADCÊ±ÖÓ×îºÃ²»Òª³¬¹ý36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//³õÊ¼»¯
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12Î»Ä£Ê½
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//·ÇÉ¨ÃèÄ£Ê½	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//¹Ø±ÕÁ¬Ðø×ª»»
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//½ûÖ¹´¥·¢¼ì²â£¬Ê¹ÓÃÈí¼þ´¥·¢
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ÓÒ¶ÔÆë	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1¸ö×ª»»ÔÚ¹æÔòÐòÁÐÖÐ Ò²¾ÍÊÇÖ»×ª»»¹æÔòÐòÁÐ1 
  ADC_Init(ADC1, &ADC_InitStructure);//ADC³õÊ¼»¯
	
	ADC_Cmd(ADC1, ENABLE);//¿ªÆôAD×ª»»Æ÷	
}


/****************************************************************************
* Ãû    ³Æ: u16 Get_Adc(u8 ch) 
* ¹¦    ÄÜ£º»ñµÃADCÖµ
* Èë¿Ú²ÎÊý£ºch: Í¨µÀÖµ 0~16È¡Öµ·¶Î§Îª£ºADC_Channel_0~ADC_Channel_16
* ·µ»Ø²ÎÊý£º12Î»ADCÓÐÐ§Öµ
* Ëµ    Ã÷£º       
****************************************************************************/
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCÍ¨µÀ,480¸öÖÜÆÚ,Ìá¸ß²ÉÑùÊ±¼ä¿ÉÒÔÌá¸ß¾«È·¶È			    
  
	ADC_SoftwareStartConv(ADC1);		//Ê¹ÄÜÖ¸¶¨µÄADC1µÄÈí¼þ×ª»»Æô¶¯¹¦ÄÜ	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//µÈ´ý×ª»»½áÊø

	return ADC_GetConversionValue(ADC1);	//·µ»Ø×î½üÒ»´ÎADC1¹æÔò×éµÄ×ª»»½á¹û
}

/****************************************************************************
* Ãû    ³Æ: u16 Get_Adc_Average(u8 ch,u8 times) 
* ¹¦    ÄÜ£º»ñÈ¡Í¨µÀchµÄ×ª»»Öµ£¬È¡times´Î,È»ºóÆ½¾ù 
* Èë¿Ú²ÎÊý£ºch: Í¨µÀÖµ 0~16È¡Öµ·¶Î§Îª£ºADC_Channel_0~ADC_Channel_16
*           times:»ñÈ¡´ÎÊý
* ·µ»Ø²ÎÊý£ºÍ¨µÀchµÄtimes´Î×ª»»½á¹ûÆ½¾ùÖµ
* Ëµ    Ã÷£º       
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
