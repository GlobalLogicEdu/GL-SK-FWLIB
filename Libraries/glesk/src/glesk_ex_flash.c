#include "glesk_ex_flash.h"
#include "glesk_spi.h"

#define TEST

#ifdef TEST
    #include <stdio.h>
#endif /* ifdef TEST */

void Send_Byte(unsigned char out)
{
    spi_w_byte(1, out);
}

unsigned char Get_Byte()
{
    return spi_r_byte(1);
}

void CE_High()
{
    spi_slave_disable();
}

void CE_Low()
{
    spi_slave_enable();
}

unsigned char Read_Status_Register()
{
    unsigned char byte = 0;
    CE_Low();			/* enable device */
    Send_Byte(0x05);		/* send RDSR command */
    byte = Get_Byte();		/* receive byte */
    CE_High();			/* disable device */
    return byte;
}

// Enables Write Status Register
void EWSR()
{
    CE_Low();			/* enable device */
    Send_Byte(0x50);		/* enable writing to the status register */
    CE_High();			/* disable device */
}

// This procedure writes a byte to the Status Register.
void WRSR(u8 byte)
{
    CE_Low();			/* enable device */
    Send_Byte(0x01);		/* select write to status register */
    Send_Byte(byte);		/* data that will change the status of BPx
                       or BPL (only bits 2,3,4,5,7 can be written) */
    CE_High();			/* disable the device */
}

// This procedure enables the Write Enable Latch.
void WREN()
{
    CE_Low();			/* enable device */
    Send_Byte(0x06);		/* send WREN command */
    CE_High();			/* disable device */
}

// This procedure disables the Write Enable Latch.
void WRDI()
{
    CE_Low();			/* enable device */
    Send_Byte(0x04);		/* send WRDI command */
    CE_High();			/* disable device */
}

unsigned char Read_ID(u8 ID_addr)
{
    unsigned char byte;
    CE_Low();			/* enable device */
    Send_Byte(0x90);		/* send read ID command (90h or ABh) */
    Send_Byte(0x00);		/* send address */
    Send_Byte(0x00);		/* send address */
    Send_Byte(ID_addr);		/* send address - either 00H or 01H */
    byte = Get_Byte();		/* receive byte */
    CE_High();			/* disable device */
    return byte;
}

unsigned char Read(unsigned long Dst)
{
    unsigned char byte = 0;

    CE_Low();			/* enable device */
    Send_Byte(0x03); 		/* read command */
    Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
    Send_Byte(((Dst & 0xFFFF) >> 8));
    Send_Byte(Dst & 0xFF);
    byte = Get_Byte();
    CE_High();			/* disable device */
    return byte;			/* return one byte read */
}

void Byte_Program(unsigned long Dst, unsigned char byte)
{
    CE_Low();				/* enable device */
    Send_Byte(0x02); 			/* send Byte Program command */
    Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
    Send_Byte(((Dst & 0xFFFF) >> 8));
    Send_Byte(Dst & 0xFF);
    Send_Byte(byte);			/* send byte to be programmed */
    CE_High();				/* disable device */
}

void Chip_Erase()
{
    CE_Low();				/* enable device */
    Send_Byte(0x60);			/* send Chip Erase command (60h or C7h) */
    CE_High();				/* disable device */
}

void Sector_Erase(unsigned long Dst)
{
    CE_Low();				/* enable device */
    Send_Byte(0x20);			/* send Sector Erase command */
    Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
    Send_Byte(((Dst & 0xFFFF) >> 8));
    Send_Byte(Dst & 0xFF);
    CE_High();				/* disable device */
}

void Block_Erase_32K(unsigned long Dst)
{
    CE_Low();				/* enable device */
    Send_Byte(0x52);			/* send 32 KByte Block Erase command */
    Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
    Send_Byte(((Dst & 0xFFFF) >> 8));
    Send_Byte(Dst & 0xFF);
    CE_High();				/* disable device */
}

void Block_Erase_64K(unsigned long Dst)
{
    CE_Low();				/* enable device */
    Send_Byte(0xD8);			/* send 64KByte Block Erase command */
    Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
    Send_Byte(((Dst & 0xFFFF) >> 8));
    Send_Byte(Dst & 0xFF);
    CE_High();				/* disable device */
}

void Wait_Busy()
{
    while ((Read_Status_Register() & 0x03) == 0x03)	/* waste time until not busy */
        Read_Status_Register();
}

int ex_flash_init(void)
{
    spi_init(1);
#ifdef TEST
    printf("Manufacture id: %x\n\r", Read_ID(0));
    printf("Device id: %x\n\r", Read_ID(1));

    printf("Read 0x00 before erasing: %x\n\r", Read(0x00));
    printf("Read 0x01 before erasing: %x\n\r", Read(0x01));

    printf("Status register: %x\n\r", Read_Status_Register());

    WREN();
    Read_Status_Register();
    EWSR();
    WRSR(0x10);
    Read_Status_Register();

    printf("Status register after clear protection: %x\n\r", Read_Status_Register());

    WREN();
    Sector_Erase(0x00);
    Wait_Busy();

    printf("Read 0x00 after erasing: %x\n\r", Read(0x00));
    printf("Read 0x01 after erasing: %x\n\r", Read(0x01));

    WREN();
    Byte_Program(0x00, 0xab);
    Wait_Busy();

    WREN();
    Byte_Program(0x01, 0xcd);
    Wait_Busy();

    printf("Read 0x00 after writing: %x\n\r", Read(0x00));
    printf("Read 0x01 after writing: %x\n\r", Read(0x01));
#endif /* ifdef TEST */

    return 0;
}

int ex_flash_read(u8 *data, ssize_t len)
{
    return -1;
}

int ex_flash_write(const u8 *data, ssize_t len)
{
    return -1;
}
