/*
 * 002_SPI_testing.c
 *
 *  Created on: Jan 18, 2023
 *      Author: admin
 */

#include "stm32f407xx_driver.h"
#include<string.h>



void delay(long long int t){

	for(long long int i=0;i<t;i++);
}





void SPI_GpioBtnInit(void){

	GPIO_Handle_t GpioBtn;

	GpioBtn.pGPIOx						= GPIOA;
	GpioBtn.GpioPinConfig.gpio_PinNum	= PIN_NUM_0;
	GpioBtn.GpioPinConfig.gpio_PinMode  = GPIO_MODE_IN;
	GpioBtn.GpioPinConfig.gpio_PinOpType= GPIO_OP_PP;
	GpioBtn.GpioPinConfig.gpio_PinSpeed = GPIO_HIGH_SPEED;
	GpioBtn.GpioPinConfig.gpio_PuPdCtrl = GPIO_NO_PUPD;

	GPIO_Init(&GpioBtn);

}


void SPI_GpioInit(){

		GPIO_Handle_t Gpiox;



		Gpiox.pGPIOx							= GPIOB;
		Gpiox.GpioPinConfig.gpio_PinMode 		= GPIO_MODE_ALTFUNMODE;
		Gpiox.GpioPinConfig.gpio_PinSpeed		= GPIO_HIGH_SPEED;
		Gpiox.GpioPinConfig.gpio_PinAltFunMode	= GPIO_MODE_AF5;
		Gpiox.GpioPinConfig.gpio_PinOpType		= GPIO_OP_PP;
		Gpiox.GpioPinConfig.gpio_PuPdCtrl		= GPIO_NO_PUPD;

		//NSS pin config
		Gpiox.GpioPinConfig.gpio_PinNum = PIN_NUM_12;
		GPIO_Init(& Gpiox);

		//SCLK pin config
		Gpiox.GpioPinConfig.gpio_PinNum = PIN_NUM_13;
		GPIO_Init(&Gpiox);

		//MISO pin config
		//Gpiox.GpioPinConfig.gpio_PinNum = PIN_NUM_14;
		//GPIO_Init(&Gpiox);

		//MOSI pin config
		Gpiox.GpioPinConfig.gpio_PinNum = PIN_NUM_15;
		GPIO_Init(&Gpiox);




	}


void SPI2_Init(void){

	SPI_Handle_t Spix;

	Spix.SPIx							= SPI2;

	Spix.SPIx_PinConfig.SPI_Mode 		= SPI_MODE_MASTER;
	Spix.SPIx_PinConfig.SPI_BusConfig   = SPI_BUSCFG_FD;
	Spix.SPIx_PinConfig.SPI_clkSpeed    = SPI_CLKSPEED_DIV32;
	Spix.SPIx_PinConfig.SPI_Cpol        = SPI_CPOL_LOW;
	Spix.SPIx_PinConfig.SPI_Cpha        = SPI_CPHA_LOW;
	Spix.SPIx_PinConfig.SPI_dff			= SPI_DFF_8;
	Spix.SPIx_PinConfig.SPI_ssm			= SPI_SSM_DI;

	SPI_Init(&Spix);


}


int main(void){


		char User_Data[]="saravanan willl be an billionre";

		//Button configuration

		SPI_GpioBtnInit();

	  //Configure GPIO pins for SPI

		SPI_GpioInit();

	 // SPI configuration

		SPI2_Init();

	 //SSI enable

		//SPI_SSIControl(SPI2,ENABLE);

	//Enable SSOE

	SPI_SSOEConfig(SPI2,ENABLE);

    while(1){

	while( !ReadFromInputPin(GPIOA, PIN_NUM_0));

	delay(500000);

	 //Enable SPI

	 SPI_PControl(SPI2,ENABLE);


	 uint8_t len = strlen(User_Data);

	 //Send length info to slave

	 SPI_SendData(SPI2, &len,1);

	 //send data

	 SPI_SendData(SPI2,(uint8_t *)User_Data,strlen(User_Data));


	 while(Get_Flag_Status(SPI2, BSY_FLAG_SET));

	 //SPI disable

	 SPI_PControl(SPI2,DISABLE);


    }


}

