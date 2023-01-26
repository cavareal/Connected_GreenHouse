/*
 * ili9341_affichage.h
 *
 *  Created on: 21 janv. 2023
 *      Author: alice
 */

#ifndef ILI9341_AFFICHAGE_H_
#define ILI9341_AFFICHAGE_H_


char * itoa(int value, char * result, int base);

void ILI9341_Affichage1(void);

void ILI9341_Affichage2(uint16_t lum, uint32_t temp, uint16_t distance, uint16_t humi);

void ILI9341_draw_ball(int x, int y, int r, uint16_t color);

void ILI9341_draw_cross(int x, int y, int r, uint16_t color);

#endif /* ILI9341_AFFICHAGE_H_ */
