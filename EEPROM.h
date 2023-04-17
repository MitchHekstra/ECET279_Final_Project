/*
 * EEPROM.h
 *
 * Created: 4/5/2023 12:26:11 PM
 *  Author: mitch
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_write_one_char(uint16_t, uint8_t);
void EEPROM_write_string(uint16_t, volatile char *ucDATA);
char EEPROM_read(uint16_t Address);
void EEPROM_read_string(uint16_t readAddress, char *writeToArray);
void EEPROM_write_locations(uint16_t address, uint16_t data);

#endif /* EEPROM_H_ */