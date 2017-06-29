//
// Created by JGMR on 17/06/2017.
//
#include <iostream>
#include <cstdint>
#include "color.h"

#define NUM_LED_COLUMNS (4)
#define NUM_LED_ROWS (1)
#define NUM_COLORS (3)

#define RED_PIN (0)   // Raspberry
#define GREEN_PIN (3) // Raspberry
#define BLUE_PIN (2)  // Raspberry

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
    led_index = 0;
    color_index = 0;

    // Set LEDs default colors
    int colors[4] = { RED_COLOR, MAGENTA_COLOR, BLUE_COLOR, WHITE_COLOR };
    setLEDColors(colors);

    std::cout << "Setup Colors completed." << std::endl;

    while(isRunning){

        scan();

        if(led_index == 4){
            led_index = 0;
        }
        if(color_index == 2){
            led_index++;
        }

        color_index++;

        if(color_index == 3){
            color_index = 0;
        }
    }
    std::cout << "Color process ended." << std::endl;
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
    // Select a column
    digitalWrite(ledcolumnpins[led_index], LOW);

    // write the row pins
    if(LED_colors[led_index][color_index])
    {
        switch(color_index){
            case 0:
                digitalWrite(RED_PIN, HIGH);
                break;
            case 1:
                digitalWrite(GREEN_PIN, HIGH);
                break;
            case 2:
                digitalWrite(BLUE_PIN, HIGH);
                break;
        }
    }

    delay(1);

    digitalWrite(ledcolumnpins[led_index], HIGH);	//deselect current column

    digitalWrite(colorpins[color_index], LOW);
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
