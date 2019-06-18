#ifndef __GLESK_EX_FLASH_H__
#define __GLESK_EX_FLASH_H__

#include <sys/types.h>
#include "glesk_common.h"

int ex_flash_init(void);
int ex_flash_read(u8 *data, ssize_t len);
int ex_flash_write(const u8 *data, ssize_t len);

#endif /* ifndef __GLESK_EX_FLASH_H__ */
