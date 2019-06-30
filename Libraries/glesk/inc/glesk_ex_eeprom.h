#ifndef __GLESK_EX_EEPROM_H__
#define __GLESK_EX_EEPROM_H__

#include "glesk_common.h"

int ex_eeprom_init(void);

int ex_eeprom_read(u32 addr, u8 *data, ssize_t len);
int ex_eeprom_write(u32 addr, const u8 *data, ssize_t len);

#endif /* ifndef __GLESK_EX_EEPROM_H__ */
