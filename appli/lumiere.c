/*
 * lumiere.c
 *
 *  Created on: 21 janv. 2023
 *      Author: alice
 */

#include "stm32f1_adc.h"
#include "stm32f1xx_hal.h"

volatile bool_e bool = FALSE;

/**
 * @brief récupère la valeur qu'on obtient grâce à l'ADC
 */

uint16_t getValuePhotoresistance(){
	return ADC_getValue(ADC_1);
}

/**
 * @brief allume ou éteint les lampes (ici la LED de la bluePill)
 */
void lampeUV(){
    if (getValuePhotoresistance() < 1500 && bool == TRUE) { // il fait nuit
        HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN);//on allume les lumières
        bool = FALSE;
    }
    else if (getValuePhotoresistance() >= 1500 && bool == FALSE) {
         HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN); //on éteint les lumières
         bool = TRUE;
    }
}
