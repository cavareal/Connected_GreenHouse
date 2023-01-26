/*
 * ili9341_affichage.c
 *
 *  Created on: 21 janv. 2023
 *      Author: alice
 */

#include "tft_ili9341/stm32f1_ili9341.h"
#include <math.h>



/**
 * @brief change un int en char* quel que soit la base de l'int
 * @author Lukas Chmela
 * @return char*
 */
char * itoa(int value, char * result, int base) {
  // on vérifie que l'algo peut s'appliquer (de base 2 à 35)
  if (base < 2 || base > 36) {
    * result = '\0';
    return result;
  }

  char * ptr = result, * ptr1 = result, tmp_char;
  int tmp_value;

  do {
    tmp_value = value;
    value /= base; //divise value par base at attribue le résultat à value
    * ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)]; // on ajoute à la chaine de caractère la valeur correspondant à l'indice
  } while (value);

  // gestion des nombres négatifs
  if (tmp_value < 0) * ptr++ = '-'; // si le nombre est inférieur à 0 on met un - au début de la chaine
  * ptr-- = '\0'; // on ajoute à la fin de la chaine le caractère null (ou vide)
  // dans ce while on inverse la chaine ptr
  while (ptr1 < ptr) {
    tmp_char = * ptr;
    * ptr-- = * ptr1;
    * ptr1++ = tmp_char;
  }
  return result;
}

/**
 * @date 15 December 2022
 * @version 0.3
 * @brief Affichage des valeurs des capteurs sur l'écran TFT
 * Grâce à la fonction itoa() on peut utiliser la fonction Puts pour afficher les nombres entiers
 */
void ILI9341_Affichage2(uint16_t lum, uint32_t temp, uint16_t distance, uint16_t humi) {
  char temps[4];
  char distances[2];
  char hum[5];


  if (lum >= 1500) { //il fait jour, on affiche un soleil (un rond jaune)
    ILI9341_draw_cross(140, 200, 7, ILI9341_COLOR_YELLOW);
    ILI9341_draw_ball(140, 200, 6, ILI9341_COLOR_YELLOW);
  } else if (lum < 1500) { // il fait nuit, on affiche une lune bleue
    ILI9341_draw_ball(140, 200, 6, ILI9341_COLOR_BLUE);
    ILI9341_draw_ball(145,200,6,ILI9341_COLOR_WHITE);
  }


  //affichage de l'alerte si la cuve est vide
  if(distance>150 && distance<300){
	  ILI9341_draw_ball(205, 140, 6, ILI9341_COLOR_RED);
  }
  else{
	  ILI9341_draw_ball(205, 140, 6, ILI9341_COLOR_WHITE);
  }

  //affichage des valeurs des capteurs
  #if USE_FONT7x10
  ILI9341_Puts(140, 170, itoa(temp, temps, 10), & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(140, 140, "     ", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE); // on efface les anciennes valeurs
  ILI9341_Puts(140, 140, itoa(distance, distances, 10), & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(140, 110, itoa(humi, hum, 10) , & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);

  #endif
}

/**
 * @date 22 November 2022
 * @version 0.6
 * @brief Initialise l'écran en "landscape" et affiche les informations qui ne bougent pas
 * Affiche la trame de base (lumière, humidité, température, hauteur d'eau)
 */
void ILI9341_Affichage1(void) {
  ILI9341_Init(); // Ecran
  ILI9341_Rotate(ILI9341_Orientation_Landscape_2);
  ILI9341_Fill(ILI9341_COLOR_WHITE);

  #if USE_FONT7x10
  ILI9341_Puts(25, 200, "Lumiere :", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(25, 110, "Humidite :", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(157, 110, "%", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(25, 170, "Temperature :", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(157, 170, "Celsius", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(25, 140, "Hauteur d'eau :", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  ILI9341_Puts(180, 140, "cm", & Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_WHITE);
  #endif
}





/**
 * @date 10 january 2023
 * @brief Permet de dessiner un cercle rempli sur l'écran ILI9341
 * @param coordonnées (x,y) avec un rayon r et une couleur
 * Dessine un cercle de centre (x,y) et de rayon r
 */
void ILI9341_draw_ball(int x, int y, int r, uint16_t color) {
  int i, j;
  for (i = -r; i <= r; i++) {
    for (j = -r; j <= r; j++) {
      if (i * i + j * j <= r * r) {
        if (j >= 0 && i >= -r / 2 && i <= r / 2) {
          ILI9341_DrawPixel(x + i, y + j, color);
        } else {
          ILI9341_DrawPixel(x + i, y + j, color);

        }
      }
    }
  }
}


/**
 * @date 10 january 2023
 * @brief Permet de dessiner un quadrillage sur l'écran ILI9341
 * @param coordonnées (x,y) avec un rayon r et une couleur
 * Dessine une croix de centre (x,y) et de rayon r
 */
void ILI9341_draw_cross(int x, int y, int r, uint16_t color) {
  int i, j;
  for (i = -r; i <= r; i++) {
    for (j = -r; j <= r; j++) {
      // horizontal lines
      if (j == -r / 2 || j == r / 2) {
        ILI9341_DrawPixel(x + i, y + j, color);
      }
      // vertical lines
      if (i == -r / 2 || i == r / 2) {
        ILI9341_DrawPixel(x + i, y + j, color);
      }
    }
  }
}

