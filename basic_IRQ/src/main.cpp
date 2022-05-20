/**
 * @brief Example triggering an external interrupt. Everytime the interrupt is
 *        triggered a counter increments and its value is displayed on an OLED
 *        screen.
 * @pre Have an OLED display connected to the Blue Pill.
 * @pre A push button switch to GND is connected in series with DIO_READ_PIN.
 *      When the switch is pressed DIO_READ_PIN gets shorted to GND.
 */
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DIO_READ_PIN PA0    //digital read pin

/**
 * @brief IRQ for external interrupt
 * @param none
 * @retval none
 */
void irq_handler();

// Variable to store the value of the counter
volatile uint16_t value = 0;
// Variable to show the program is running
uint16_t loop_count = 0;

/**
 * @brief Initialize the analog in pin and the LED control pin.
 * @param none
 * @retval none
 */
void setup()
{
  //Initialize DIO_READ_PIN to pullup - will be pulled to GND when switch
  //pressed
  pinMode(DIO_READ_PIN, INPUT_PULLUP);

  //Attach external IRQ pin to IRQ handler
  attachInterrupt(digitalPinToInterrupt(DIO_READ_PIN), irq_handler, RISING);

  //Initialize OLED display
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  // Displays Adafruit logo by default. call clearDisplay immediately if you
  // don't want this.
  display_handler.display();
  delay(2000);

  // Displays "Hello world!" on the screen
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Hello world!");
  display_handler.display();
}

/**
 * @brief Read the value of the analog-in pin and set the timing for the LED
 *        blink period depending on this value.
 * @param none
 * @retval none
 */
void loop()
{
  display_handler.clearDisplay();
  display_handler.setCursor(0, 0);
  display_handler.println(loop_count++, DEC);
  display_handler.print(value, DEC);
  display_handler.display();

  delay(500);
}

void irq_handler(){
  value++;
}
