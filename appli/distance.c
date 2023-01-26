/*
 * distance.c
 *
 *  Created on: 21 janv. 2023
 *      Author: alice
 */

#include "HC-SR04/HCSR04.h"

#define PERIOD_MEASURE 100


/**
 * @date 13 december 2022
 * @brief machine à état qui permet de récupérer la distance entre l'obstable et le capteur
 * @return la distance
 */
uint16_t HCSR04_distance_state_machine(void) {
  typedef enum {
    INIT,
    FAIL,
    LAUNCH_MEASURE,
    RUN,
    WAIT_DURING_MEASURE,
    WAIT_BEFORE_NEXT_MEASURE
  }
  state_e;

  static state_e state = INIT;
  static uint32_t tlocal;
  static uint8_t id_sensor;
  uint16_t distance;

  //ne pas oublier d'appeler en t�che de fond cette fonction.
  HCSR04_process_main();

  switch (state) {
  case INIT:
    if (HCSR04_add( & id_sensor, GPIOB, GPIO_PIN_15, GPIOB, GPIO_PIN_12) != HAL_OK) {
      state = FAIL;
    } else {
      state = LAUNCH_MEASURE;
    }
    break;
  case LAUNCH_MEASURE:
    HCSR04_run_measure(id_sensor);
    tlocal = HAL_GetTick();
    state = WAIT_DURING_MEASURE;
    break;
  case WAIT_DURING_MEASURE:
    switch (HCSR04_get_value(id_sensor, & distance)) {
    case HAL_BUSY:
      //rien � faire... on attend...
      break;
    case HAL_OK:
      state = WAIT_BEFORE_NEXT_MEASURE;
      return distance;
      break;
    case HAL_ERROR:
      state = WAIT_BEFORE_NEXT_MEASURE;
      break;

    case HAL_TIMEOUT:
      state = WAIT_BEFORE_NEXT_MEASURE;
      break;
    }
    break;
  case WAIT_BEFORE_NEXT_MEASURE:
    if (HAL_GetTick() > tlocal + PERIOD_MEASURE)
      state = LAUNCH_MEASURE;
    break;
  default:
    break;
    return 0;
  }
}


/**
 * @brief récupère la distance en cm
 */
uint16_t getDistance(){
	volatile uint16_t distance;
    volatile uint16_t dist;
    volatile uint16_t dist0;

    distance = HCSR04_distance_state_machine(); // appel de la fonction du module � ultrason
    dist0 = distance / 10;

    if (dist0 < 1500) { // affiche la valeur seulement si elle est cohérente
      dist = distance / 10;
    }

    return dist;

}
