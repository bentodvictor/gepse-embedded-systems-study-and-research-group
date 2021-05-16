#include "LiquidCrystal.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "stm32f1xx_hal.h"

void pulseEnable(LCD_pins pinos);
void write4bits(uint8_t value, LCD_pins pinos);
void command(uint8_t value, LCD_pins pinos);
void send(uint8_t value, uint8_t mode, LCD_pins pinos);
void display(LCD_pins pinos);
void clear(LCD_pins pinos);

void pulseEnable(LCD_pins pinos)
{
	HAL_GPIO_WritePin(pinos.en.GPIOx, pinos.en.GPIO_Pin, 0);
	HAL_Delay(1);		
	HAL_GPIO_WritePin(pinos.en.GPIOx, pinos.en.GPIO_Pin, 1);
	HAL_Delay(1);		
	HAL_GPIO_WritePin(pinos.en.GPIOx, pinos.en.GPIO_Pin, 1);
	HAL_Delay(1);		
}

void write4bits(uint8_t value, LCD_pins pinos)
{
	for(int i = 0; i < 4; i++)
	{
		HAL_GPIO_WritePin(pinos.data[i].GPIOx, pinos.data[i].GPIO_Pin, (value >> i) & 0x01);
	}
	pulseEnable(pinos);
}

void begin(LCD_pins pinos)
{
	//esperar um tempo para o lcd ligar
	HAL_Delay(50);	
	HAL_GPIO_WritePin(pinos.rs.GPIOx, pinos.rs.GPIO_Pin, 0);
	HAL_GPIO_WritePin(pinos.en.GPIOx, pinos.en.GPIO_Pin, 0);
	HAL_GPIO_WritePin(pinos.rw.GPIOx, pinos.rw.GPIO_Pin, 0);
	
	write4bits(0x03, pinos);			
	HAL_Delay(5);					//wait min 4.5 microseconds 
	write4bits(0x03, pinos);			
	HAL_Delay(5);					//wait min 4.5 microseconds 
	write4bits(0x03, pinos);			
	HAL_Delay(1);					//wait min 4.5 microseconds 
	write4bits(0x02, pinos); 		//set 4bit interface
	
	command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS | LCD_2LINE, pinos);
	display(pinos);
	clear(pinos);
}

void send(uint8_t value, uint8_t mode, LCD_pins pinos)
{
	HAL_GPIO_WritePin(pinos.rs.GPIOx, pinos.rs.GPIO_Pin, mode);
	HAL_GPIO_WritePin(pinos.rw.GPIOx, pinos.rw.GPIO_Pin, 0);
	write4bits(value>>4, pinos);
  write4bits(value, pinos);
}

void write(uint8_t value, LCD_pins pinos)
{
	send(value, 1, pinos);
}

void command(uint8_t value, LCD_pins pinos)
{
		send(value, 0, pinos);
}

void clear(LCD_pins pinos)
{
	command(LCD_CLEARDISPLAY, pinos);
	HAL_Delay(2);
}

void display(LCD_pins pinos)
{
	command(LCD_DISPLAYCONTROL | LCD_DISPLAYON, pinos);
}
