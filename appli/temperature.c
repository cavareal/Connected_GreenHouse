/*
 * temperature.c
 *
 *  Created on: 21 janv. 2023
 *      Author: alice
 */

#include "stm32f1_adc.h"

/**
 * @biref permet de récupérer la température en degre Celcius
 */
uint32_t getTemperatureDegre(void){
	  volatile int32_t value_temperature;
	  volatile int32_t temp_milli;
	  volatile int32_t temperature_C;
	  value_temperature = ADC_getValue(ADC_0); //r�cup�ration de la valeur de la temp�rature
	  temp_milli = value_temperature * 3300 / 4096; // convertion en millivolt
	  temperature_C = (int32_t)(((temp_milli - 400) * 2) / 39); //convertion en C�
	  return temperature_C;
}
