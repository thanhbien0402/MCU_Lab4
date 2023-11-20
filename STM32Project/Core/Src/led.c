/*
 * led.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Admin
 */


#include "main.h"
#include "led.h"

void Led1Shot(void) {
	HAL_GPIO_TogglePin(GPIOA, LED1SHOT_Pin);
}
void Led1(void) {
	HAL_GPIO_TogglePin(GPIOA, LED1_Pin);
}
void Led2(void) {
	HAL_GPIO_TogglePin(GPIOA, LED2_Pin);
}
void Led3(void) {
	HAL_GPIO_TogglePin(GPIOA, LED3_Pin);
}
void Led4(void) {
	HAL_GPIO_TogglePin(GPIOA, LED4_Pin);
}
