#ifndef __GLESK_EX_FLASH_H__
#define __GLESK_EX_FLASH_H__

#include "glesk_common.h"

int ex_flash_init(void);

int ex_flash_read(u32 addr, u8 *data, ssize_t len);
int ex_flash_write(u32 addr, const u8 *data, ssize_t len);

// Erase 4KiB
void ex_flash_erase_sector(u32 addr);

// Erase 32KiB
void ex_flash_erase_block_32k(u32 addr);

// Erase 64KiB
void ex_flash_erase_block_64k(u32 addr);

// Erase whole flash chip
void ex_flash_erase_chip(void);

#endif /* ifndef __GLESK_EX_FLASH_H__ */
