//
// Created by JGMR on 17/06/2017.
//

#ifndef CONTROLLER_COLOR_H
#define CONTROLLER_COLOR_H

#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include <sstream>
#include <vector>
#include "NetworkService.h"

#define NUM_LED_COLUMNS (4)
#define NUM_LED_ROWS (1)
#define NUM_COLORS (3)

#define RED_PIN (0)
#define GREEN_PIN (3)
#define BLUE_PIN (2)

#define RED_COLOR (0)
#define GREEN_COLOR (1)
#define BLUE_COLOR (2)
#define CYAN_COLOR (3)
#define MAGENTA_COLOR (4)
#define YELLOW_COLOR (5)
#define WHITE_COLOR (6)

#define COLOR_SOCKET_ADR    "127.0.0.1"
#define COLOR_SOCKET_PORT   45001
static bool LED_colors[NUM_LED_COLUMNS][NUM_COLORS];    // Mapping grid of LED colors

static uint8_t led_index;
static uint8_t color_index;

static const uint8_t ledcolumnpins[NUM_LED_COLUMNS] = {1, 4, 5, 6};

// RGB pins for each of 4 rows
static const uint8_t colorpins[NUM_COLORS] = {0, 3, 2};

static bool isColorThreadRunning = true;



void debugArray(std::string * arr, int it);
void debugArray(int * arr, int it);
void getIntColors(std::string * arr, int * resArray);


template<typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

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
