
#include <Arduino.h>
#include <sim.h>
#include "random.h"

#define tempVar    (XSTIOT_Registers->DATA[0])
#define errorCount (XSTIOT_Registers->DATA[1])
	
void __attribute__ ((long_call, section(".data.data_begin"))) setup(void){
	CMSDK_GPIO9->DATAOUT = 0x00;
	CMSDK_GPIO9->OUTENABLESET = 0xFF;

	Serial.begin(115200);
	CMSDK_UART0->CTRL |= CMSDK_UART_CTRL_HSTM_Msk;
	Serial.println("X1 Internal Flash R/W Test");

	Serial.println("Enabling Cache...");
	__disable_irq();
	while ((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) == (0b11 << CMSDK_CACHE_SR_CS_Pos)); // Wait until cache is disabled
	if((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) == (0b00 << CMSDK_CACHE_SR_CS_Pos))
		CMSDK_CACHE->CCR |=  CMSDK_CACHE_CCR_EN_Msk; // Enable cache
	while ((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) != (0b10 << CMSDK_CACHE_SR_CS_Pos)); // Wait until cache is enabled
	__enable_irq();

	// Fill the cache
	for(uint8_t i=0; i<8; i++){
		Serial.print((*(uint8_t *) (0x1000+i)),HEX);
		Serial.print(' ');
	}
	Serial.println();

	Serial.println("Erasing Sector 0x1000...");
	__disable_irq();
	while(!(FLASHCTRL->STATUS & FLASH_STAT_INTREADY_Msk)); // Wait until ready
	FLASHCTRL->CONTROL |= FLASH_CTRL_INTERASE_Msk;         // Enable erase mode
	(*(uint8_t *) 0x1000) = 0x30;                           // Erase address 0x10000
	FLASHCTRL->CONTROL &= ~FLASH_CTRL_INTERASE_Msk;        // Disable erase mode
	while(!(FLASHCTRL->STATUS & FLASH_STAT_INTREADY_Msk)); // Wait until erase completed
	//for(volatile int i=0; i<0xFFFFF; i++);
	__enable_irq();
	Serial.println("Erase Done!");

	// Check contents
	for(uint8_t i=0; i<8; i++){
		Serial.print((*(uint8_t *) (0x1000+i)),HEX);
		Serial.print(' ');
	}
	Serial.println();

	Serial.println("Disabling Cache...");
	__disable_irq();
	if((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) == (0b10 << CMSDK_CACHE_SR_CS_Pos))
		CMSDK_CACHE->CCR &=  ~CMSDK_CACHE_CCR_EN_Msk; // Disable cache
	while ((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) != (0b00 << CMSDK_CACHE_SR_CS_Pos)); // Wait until cache is disabled
	__enable_irq();

	Serial.print("Blank check: ");
	errorCount = 0;
	for(int i=0; i<256; i++){
		if(*(uint8_t *)(0x1000+i) != 0xFF) errorCount++;
	}
	Serial.print(errorCount);
	Serial.println(" errors");

	Serial.println("Enabling Cache...");
	__disable_irq();
	if((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) == (0b00 << CMSDK_CACHE_SR_CS_Pos))
		CMSDK_CACHE->CCR |=  CMSDK_CACHE_CCR_EN_Msk; // Enable cache
	while ((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) != (0b10 << CMSDK_CACHE_SR_CS_Pos)); // Wait until cache is enabled
	__enable_irq();

	Serial.print("Blank check: ");
	errorCount = 0;
	for(int i=0; i<256; i++){
		if(*(uint8_t *)(0x1000+i) != 0xFF) errorCount++;
	}
	Serial.print(errorCount);
	Serial.println(" errors");

	Serial.println("Programming Sector...");
	__disable_irq();
	while(!(FLASHCTRL->STATUS & FLASH_STAT_INTREADY_Msk)); // Wait until ready
	for(int i=0; i<256; i++){
		*(uint8_t *)(0x1000+i) = (uint8_t) ~i;
		while(!(FLASHCTRL->STATUS & FLASH_STAT_INTREADY_Msk)); // Wait until ready
	}
	__enable_irq();

	// Check contents
	for(uint8_t i=0; i<8; i++){
		Serial.print((*(uint8_t *) (0x1000+i)),HEX);
		Serial.print(' ');
	}
	Serial.println();

	Serial.println("Disabling Cache...");
	__disable_irq();
	if((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) == (0b10 << CMSDK_CACHE_SR_CS_Pos))
		CMSDK_CACHE->CCR &=  ~CMSDK_CACHE_CCR_EN_Msk; // Disable cache
	while ((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) != (0b00 << CMSDK_CACHE_SR_CS_Pos)); // Wait until cache is disabled
	__enable_irq();

	Serial.print("Verify: ");
	errorCount = 0;
	for(int i=0; i<256; i++){
		if(*(uint8_t *)(0x1000+i) != (uint8_t) ~i) errorCount++;
	}
	Serial.print(errorCount);
	Serial.println(" errors");

	Serial.println("Enabling Cache...");
	__disable_irq();
	if((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) == (0b00 << CMSDK_CACHE_SR_CS_Pos))
		CMSDK_CACHE->CCR |=  CMSDK_CACHE_CCR_EN_Msk; // Enable cache
	while ((CMSDK_CACHE->SR & CMSDK_CACHE_SR_CS_Msk) != (0b10 << CMSDK_CACHE_SR_CS_Pos)); // Wait until cache is enabled
	__enable_irq();

	Serial.print("Verify: ");
	errorCount = 0;
	for(int i=0; i<256; i++){
		if(*(uint8_t *)(0x1000+i) != (uint8_t) ~i) errorCount++;
	}
	Serial.print(errorCount);
	Serial.println(" errors");

	Serial.print((char)0x04);
}

void loop(void){
	
}
