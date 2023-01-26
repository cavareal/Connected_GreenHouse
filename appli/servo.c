/*
 * servo.c
 *
 *  Created on: 21 janv. 2023
 *      Author: alice
 */

#include "stm32f1_timer.h"
#include "stm32f1_pwm.h"
#include "lumiere.h"
#include "temperature.h"


#define PERIOD_TIMER 10


/**
 * @brief initialise le servo et le met à la position close
 */
void initServo(void){
	TIMER_run_us(TIMER1_ID, PERIOD_TIMER*1000, FALSE);

	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3, 200, FALSE, FALSE);
}
/**
 * @brief met le servo moteur à la position open
 */

void openWindow(void){
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3,100);
}

/**
 * @brief met le servo moteur à la position close
 */
void closWindow(void){
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3,200);
}


/**
 * @brief ouvre la fenêtre quand il fait trop chaud et la ferme quand on arrive à température optimale
 */
void asservissementServo_temperature(void){
    if (getTemperatureDegre()>30){
    	 openWindow();
    }
    if(getTemperatureDegre()<=27){
    	closWindow();
    }
}



/**
 * @brief ouvre la fenêtre s'il fait jour, et la ferme sinon
 */
void asservissementServo_lumiere(void){
    if (getValuePhotoresistance()>1500){
    	 openWindow();
    }
    if(getValuePhotoresistance()<=1500){
    	closWindow();
    }
}


