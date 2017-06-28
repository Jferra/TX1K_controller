//
// Created by JGMR on 17/06/2017.
//
#include <iostream>
#include <cstdint>
#include "button.h"

#define NUM_BTN_COLUMNS (4)
#define NUM_BTN_ROWS (1)

#define BTN_READ_PIN (21)

#define MAX_DEBOUNCE (3)

/**
 * Sets everything to start the Button thread
 * @method setupButtonThread
 * @return void
 */
void setupButtonThread()
{
    // setup hardware
    setupPins();

    // init global variables
    next_btn_scan = millis() + 1;
    btn_index = 0;

    std::cout << "Setup Buttons completed." << std::endl;
    while(1){
        scan();
    }
}

/**
 * Set all button pins
 * @method setupPins
 * @return void
 */
static void setupPins()
{
    uint8_t i;

    // Row button pin
    pinMode(BTN_READ_PIN, INPUT);
    pullUpDnControl(BTN_READ_PIN, PUD_UP);

    // Columns button pins
    for(i = 0; i < NUM_BTN_COLUMNS; i++)
    {
        pinMode(btnSelectionPins[i], OUTPUT);
        digitalWrite(btnSelectionPins[i], HIGH);
    }
}

/**
 * Scans all Buttons to check their status
 * @method scan
 * @return void
 */
static void scan()
{
    static uint8_t current = 0; // Current button
    uint8_t val;

    // Select a button to watch
    digitalWrite(btnSelectionPins[current], LOW);


    delay(1);

    val = digitalRead(BTN_READ_PIN);     // We read the pin's value at the other side of the circuit

    if(val == LOW){ // Means that the button is pressed
        if(*debounce_count[current] < MAX_DEBOUNCE){
            int8_t current_db = *debounce_count[current];
            current_db++;
            *debounce_count[current] = current_db;

            if(*debounce_count[current] == MAX_DEBOUNCE){
                sendButtonPressedEvent(current);
            }
        }
    } else {    // Means that the button is inactive
        if(*debounce_count[current] > 0){
            int8_t current_db = *debounce_count[current];
            current_db--;
            *debounce_count[current] = current_db;
        }
    }

    digitalWrite(btnSelectionPins[current], HIGH); // Deselect current button

    current++;
    if(current >= NUM_BTN_COLUMNS){
        current = 0;
    }
}

/**
 * Sends a message to notify system when a button is pressed
 * @method sendButtonPressedEvent
 * @param int8_t btnId
 * @return void
 */
static void sendButtonPressedEvent(int8_t btnId)
{
    //todo send to communication thread a message
    std::cout << "Button pressed !" << unsigned(btnId) << std::endl;
}
