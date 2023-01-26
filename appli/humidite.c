/*
 * humidite.c
 *
 *  Created on: 21 janv. 2023
 *      Author: alice
 */


#include "DHT11/dht11.h"

/**
 * @brief Récupère la valeur entière de l'humidité
 */
int DHT11(void)
{
    static uint8_t humidity_int;
    static uint8_t humidity_dec;
    static uint8_t temperature_int;
    static uint8_t temperature_dec;
	static bool_e initialized = FALSE;
	if(!initialized)
	{
		initialized = TRUE;
		DHT11_init(GPIOB, GPIO_PIN_7);
	}
	while(1){
    switch(DHT11_state_machine_get_datas(&humidity_int, &humidity_dec, &temperature_int, &temperature_dec))
    		{
    			case END_OK:
     				debug_printf("DHT11 h=%d,%d | t=%d,%d\n",humidity_int, humidity_dec, temperature_int, temperature_dec);
     				HAL_Delay(1500);
     				return humidity_int;
    				break;
    			case END_ERROR:
    				debug_printf("DHT11 read error (h=%d,%d | t=%d,%d)\n", humidity_int, humidity_dec, temperature_int, temperature_dec);
    				HAL_Delay(1500);
    				break;
    			case END_TIMEOUT:
    				debug_printf("DHT11 timeout (h=%d,%d | t=%d,%d)\n", humidity_int, humidity_dec, temperature_int, temperature_dec);
    				HAL_Delay(1500);
    				return ;
    				break;
    			default:
    				break;
    		}
	}
}
