/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "display.h"
#include "i2c.h"
#include <stdio.h>
#include <math.h>
#include "lps25hb.h"
#include "hts221.h"

void SystemClock_Config(void);

extern uint64_t disp_time;

uint64_t saved_time;
double num_to_display = 10;

//char name[]="danIEL_UJJ_98375";
char info[12];
char newstring[12];
char display[4];

int left_to_right=1,dot_found = 0;
int position=0, dot_pos = 0, dyn_pos = 0;
int state = 0, humidity_out = 0;
float temperature_out = 0, pressure_out = 0, altitude_out = 0;

char *cutDot(char *string);

int main(void)
{

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();

  setSegments();
  setDigits();

  LL_mDelay(2000);

  resetDigits();
  resetSegments();

  while(!lsm6ds0_init());
  while(!lps25hb_init());
  while(!hts221_init());
  while(!lis3mdl_init());

  MX_TIM3_Init();

  while (1)
  {

	  switch(state)
	  {
	  	  case 0:
	  		  temperature_out = hts221_get_temp();
	  		  snprintf(info, sizeof(info), "tEMP_%2.1f", temperature_out);
	  		  break;
	  	  case 1:
	  		  humidity_out = hts221_get_humid();
	  		  snprintf(info, sizeof(info), "HUM_%d", humidity_out);
	  		  break;
	  	  case 2:
	  		  pressure_out = lps25hb_get_pressure();
	  		  snprintf(info, sizeof(info), "bAr_%4.2f", pressure_out);
	  		  break;
	  	  case 3:
	  		  pressure_out = lps25hb_get_pressure();
	  		  temperature_out = lps25hb_get_temp();
	  		  altitude_out = ((powf((1013.25/pressure_out),1/5.257)-1)*(temperature_out+273.15))/0.0065;
	  		  snprintf(info, sizeof(info), "ALt_%4.1f", altitude_out);
	  }

	  dot_found = 0;

	  for(int i = 0; i <= strlen(info); i++)
	  	{
	  		if(info[i] == '.')
	  		{
	  			dot_pos = i;
	  			for(int j = 0; j<i; j++)
	  			{
	  				newstring[j] = info[j];
	  			}

	  			for(int k = i; k < (strlen(info) - 1); k++)
	  			{
	  				newstring[k] = info[k+1];
	  			}

	  			dot_found = 1;
	  		}
	  		else if(dot_found == 0)
	  		{
	  			newstring[i] = info[i];
	  		}

	  	}


	  if(left_to_right==1){
		  for(int i=0; i<=3;i++){
			  display[i]=newstring[position+i];
		  }
		  dyn_pos = dot_pos - (position + 3) + 2;
		  position=position+1;
		  if(position+4 >= (strlen(newstring)/sizeof(char))){
			  left_to_right=0;
		  }
	  }
	  else if(left_to_right==0){
		  for(int i=3; i>=0;i--){
			  display[i]=newstring[position+i];
		  }
		  dyn_pos = dot_pos - (position + 3) + 2;
		  position=position-1;
		  if(position == 0){
			  left_to_right=1;
		  }
	  }

	  displayName(display,dyn_pos);
	  LL_mDelay(500);

  }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SYSTICK_EnableIT();
  LL_SetSystemCoreClock(8000000);
}





int setState(int new_state)
{
	state = new_state;
	left_to_right = 1;
	position = 0;
}

char *cutDot(char string[])
{
	char *newstring;


	for(int i = 0; i <= strlen(string); i++)
	{
		if(string[i] == '.')
		{
			for(int j = 0; j<i; j++)
			{
				newstring[j] = string[j];
			}

			for(int k = i; k < (strlen(string) - 1); k++)
			{
				newstring[k] = string[k+1];
			}
		}
	}
	return newstring;
}


/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
