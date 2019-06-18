#include <stdio.h>
#include "glesk_ex_flash.h"

int main(void)
{
    printf("External flash test.\n\r");
    ex_flash_init();
    printf("Test finished.\n\r");
}
