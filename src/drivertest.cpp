
#include "drivertest.h"

#include <Arduino.h>

#include "I2SClocklessLedDriver.h"

static I2SClocklessLedDriver driver;

#define NUM_LEDS_PER_STRIP 256
#define NUMSTRIPS 1

//here we have 3 colors per pixel
uint8_t leds[NUMSTRIPS*NUM_LEDS_PER_STRIP*3];

#ifdef CONFIG_IDF_TARGET_ESP32S3
    int pins[6] = {9, 10,12,8,18,17};
#else
    int pins[6] = {14, 12, 13, 25, 33, 32};
#endif

void setupDriver()
{
    driver.initled(leds,pins,NUMSTRIPS,NUM_LEDS_PER_STRIP,ORDER_GRB);
    driver.setBrightness(20);
}

void loopDriver()
{
    // Delete Arduino loop task, as it is not needed in this example
    // vTaskDelete(NULL);

    for(int i=0;i<NUM_LEDS_PER_STRIP*NUMSTRIPS*3;i++)
        leds[i] *= 0.7; //fadetoblack 70%
    driver.setPixel(random(NUM_LEDS_PER_STRIP*NUMSTRIPS), 255, random(255), 0);

    driver.showPixels();

}
