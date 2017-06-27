//
// Created by JGMR on 17/06/2017.
//

#include <cstdint>
#include "color.h"

#define NUM_LED_COLUMNS (4)
#define NUM_LED_ROWS (1)
#define NUM_COLORS (3)

//#define RED_PIN (2)     //Launchpad
//#define GREEN_PIN (4)   //Launchpad
//#define BLUE_PIN (3)    //Launchpad

#define RED_PIN (0)   // Raspberry
#define GREEN_PIN (2) // Raspberry
#define BLUE_PIN (3)  // Raspberry

#define RED_COLOR (0)
#define GREEN_COLOR (1)
#define BLUE_COLOR (2)
#define CYAN_COLOR (3)
#define MAGENTA_COLOR (4)
#define YELLOW_COLOR (5)
#define WHITE_COLOR (6)

/**
 * Starts the process concerning LEDs management
 * @method setupColorThread
 */
void setupColorThread() {

    // setup hardware
    setupPins();

    // init global variables
    next_color_scan = millis() + 1;
    led_index = 0;
    color_index = 0;

    uint8_t i = 0;
    uint8_t j = 0;

    // Initialize the LED display array
    for(i; i < NUM_LED_COLUMNS; i++)
    {
        for(j; j < NUM_COLORS; j++)
        {
            LED_buffer[i][j] = false;
        }
    }
    // Set the first LED in the buffer on
    LED_buffer[0][0] = true;


    // Set LEDs default colors
    int colors[4] = { RED_COLOR, MAGENTA_COLOR, BLUE_COLOR, WHITE_COLOR };
    setLEDColors(colors);


    //Serial.println("Setup Complete.");

    //todo launch scan() in a infinite loop
    //todo add listeners to receive commands
}

/**
 * Initialize the LEDs Pins
 * @method setupPins
 */
static void setupPins()
{
    uint8_t i;

    // initialize all of the output pins

    // LED column lines
    for(i = 0; i < NUM_LED_COLUMNS; i++)
    {
        pinMode(ledcolumnpins[i], OUTPUT);

        // with nothing selected by default
        digitalWrite(ledcolumnpins[i], 1);
    }

    // LED row lines
    for(i = 0; i < NUM_COLORS; i++)
    {
        pinMode(colorpins[i], OUTPUT);

        // with nothing driven by default
        digitalWrite(colorpins[i], 0);
    }

}

/**
 * Loops through the available LEDs to light them one by one.
 * @method scan
 */
static void scan()
{
    static uint8_t current = 0; // current LED
    uint8_t val;
    uint8_t i, j;


    // Select a column
    digitalWrite(ledcolumnpins[current], LOW);

    // write the row pins
    for(i = 0; i < NUM_LED_COLUMNS; i++)
    {
        for(j = 0; j < NUM_COLORS; j++)
        {
            if(LED_buffer[current][j] && LED_colors[current][j])
            {
                switch(j){
                    //Red
                    case 0:
                        digitalWrite(RED_PIN, HIGH);
                        break;
                        //Green
                    case 1:
                        digitalWrite(GREEN_PIN, HIGH);
                        break;
                        //Blue
                    case 2:
                        digitalWrite(BLUE_PIN, HIGH);
                        break;
                }
            }
        }
    }

    digitalWrite(ledcolumnpins[current], HIGH);	//deselect current column

    for(i = 0; i < NUM_COLORS; i++)
    {
        digitalWrite(colorpins[i], LOW);	// "deselect" all colors
    }

    // Move on to the next column
    current++;
    if (current >= NUM_LED_COLUMNS)
    {
        current = 0;
    }

}

/**
 * This method receives new colors to set to the RGB LEDs.
 * @method setLEDColors
 * @param colors
 */
static void setLEDColors(int colors[4])
{
    uint8_t i;
    uint8_t j;

    for(i = 0; i < NUM_LED_COLUMNS; i++)
    {
        // Reset all values to false
        for(j = 0; j < NUM_COLORS; j++)
        {
            LED_colors[i][j] = false;
        }

        switch(colors[i]){
            case RED_COLOR:
                LED_colors[i][0] = true;
                break;
            case GREEN_COLOR:
                LED_colors[i][1] = true;
                break;
            case BLUE_COLOR:
                LED_colors[i][2] = true;
                break;
            case CYAN_COLOR:
                LED_colors[i][1] = true;
                LED_colors[i][2] = true;
                break;
            case MAGENTA_COLOR:
                LED_colors[i][0] = true;
                LED_colors[i][2] = true;
                break;
            case YELLOW_COLOR:
                LED_colors[i][0] = true;
                LED_colors[i][1] = true;
                break;
            case WHITE_COLOR:
                LED_colors[i][0] = true;
                LED_colors[i][1] = true;
                LED_colors[i][2] = true;
                break;
        }
    }
}
