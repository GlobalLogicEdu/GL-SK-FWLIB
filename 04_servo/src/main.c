#include "stm32f4xx.h"
#include "drivers/LEDs.h"
#include "drivers/Buttons.h"
#include "drivers/USART.h"
#include "drivers/peripheral_pinout.h"
#include "drivers/PWM_controller_PCA9685PW.h"
#include "drivers/DISPLAY_WH1602B_4Bit.h"
#include "drivers/clock_config.h"
#include "drivers/test.h"

uint8_t cycle = 4;
int main(void)
{
  setup_clock_to_168MHz();
  setup_USART(USART3, INTERRUPT_DISABLE);
  setup_LED(LED_PORT, LED_PINS);
//  PCA_servo_example();
//  Display_example();
  while(cycle)
  {

  }

}
