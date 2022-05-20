/**
* @brief Blink: Turns on an LED for one second then off for one second and then
*        repeats.
*/

#include "Arduino.h"

/**
 * @brief Set LED_BUILTIN if it is not defined by Arduino framework. If using 
 *        the original Blue Pill you will use the PC13 if you use the Blue Pill 
 *        Plus (uses USB C port instead of micro USB) you will use PB2 (comment
 *        uncomment the appropriate line).
 */
#define LED_BUILTIN PC13
//#define LED_BUILTIN PB2

/**
 * @brief Initialize LED pin as digital write.
 * @param none
 * @retval none
 */
void setup()
{
  //initialize LED digital pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * @brief Turn LED on for 1 sec and off for 1 sec.
 * @param none
 * @retval none
 */
void loop()
{
  uint32_t delay_ms = 1000;

  //turn LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  //wait for one second
  delay(delay_ms);

  //turn LED off (LOW sets voltage to GND)
  digitalWrite(LED_BUILTIN, LOW);

  //wait one more second
  delay(delay_ms);
}
