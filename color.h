//
// Created by JGMR on 17/06/2017.
//

#ifndef CONTROLLER_COLOR_H
#define CONTROLLER_COLOR_H

#include <stdio.h>
#include <wiringPi.h>

#define NUM_LED_COLUMNS (4)
#define NUM_LED_ROWS (1)
#define NUM_COLORS (3)

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


static bool LED_colors[NUM_LED_COLUMNS][NUM_COLORS];	// Mapping grid of LED colors
static int32_t next_color_scan;

static uint8_t led_index;
static uint8_t color_index;

static const uint8_t ledcolumnpins[NUM_LED_COLUMNS]   = {1,4,5,6}; //Raspberry Pi3 PINS

// RGB pins for each of 4 rows
static const uint8_t colorpins[NUM_COLORS] = {0, 2, 3};   //Raspberry Pi3 PINS


/**
 * Sets everything to start the Color thread
 */
void setupColorThread();

/**
 * Setup the LEDs pins - Hardware setup
 */
static void setupPins();

/**
 * Scans all LEDs to light them
 */
static void scan();

/**
 * Set all colors
 */
static void setLEDColors(int colors[4]);

#endif //CONTROLLER_COLOR_H
