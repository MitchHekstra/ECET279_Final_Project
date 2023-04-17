/*
 * EEPROM.c
 *
 * Created: 4/5/2023 12:25:59 PM
 *  Author: mitch
 */ 

#include <avr/io.h>
#include "EEPROM.h"
#include "stepper_motor.h"

void EEPROM_write_one_char(uint16_t uiAddress, uint8_t ucData)
{
	
	EECR = 0x00;
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address and Data Registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}

void EEPROM_write_string(uint16_t uiAddress, volatile char *ucData)
{
	while (*ucData != 0xFF)
	{
		EEPROM_write_one_char(uiAddress, *ucData);
		uiAddress++;
		ucData++;
	}
}

char EEPROM_read(uint16_t Address)
{
	while (EECR & (1<<EEPE));	// wait for completion of previous action
	EEAR = Address;			// set address location
	EECR |= (1<<EERE);			// start EEPROM read
	return EEDR;				// Return data from data register	
}

void EEPROM_read_string(uint16_t readAddress, char *writeToArray)
{
	while (*writeToArray != 0xFF)
	{
		*writeToArray = EEPROM_read(readAddress);
		writeToArray++;
		readAddress++;
	}
}

void EEPROM_write_locations(uint16_t address, uint16_t data)
{
	uint8_t dataL = data; //grab 8 lsb
	uint8_t dataH = (data>>8); //grab 4 msb
// 		while ((PINA & (1<<PINA0)) == 0)
// 		{ //WAIT UNTIL PB IS PRESSED
// 		}
	EEPROM_write_one_char(address, dataL);
	address++;
	EEPROM_write_one_char(address, dataH);
	address++;
}

uint16_t EEPROM_read_locations(uint16_t readAddress)
{
	// 		while ((PINA & (1<<PINA0)) == 0)
	// 		{ //WAIT UNTIL PB IS PRESSED
	// 		}
		
	uint8_t dataL = EEPROM_read(readAddress); //grab lsb
	readAddress++;
	uint8_t dataH = EEPROM_read(readAddress); //grab msb
	
	uint16_t total = (dataH<<8)|dataL;
	
	return total;
}