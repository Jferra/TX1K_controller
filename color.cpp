//
// Created by JGMR on 17/06/2017.
//

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


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


/**
 * Starts the process concerning LEDs management
 * @method setupColorThread
 */
void setupColorThread() {

    int socketFileDescriptor;
    char messageReceived[256];

    int msgReturnCode;

    // setup hardware
    setupPins();

    // Connect to socket
    socketFileDescriptor = NetworkService::connectToSocket(COLOR_SOCKET_PORT, COLOR_SOCKET_ADR);

    // init global variables
    led_index = 0;
    color_index = 0;

    // Set LEDs default colors
    int colors[4] = {RED_COLOR, MAGENTA_COLOR, BLUE_COLOR, WHITE_COLOR};
    setLEDColors(colors);

    std::cout << "Color::setupColorThread ---- Setup Colors completed." << std::endl;

    while (isColorThreadRunning) {
        scan();

        if (led_index == 4) {
            led_index = 0;
        }
        if (color_index == 2) {
            led_index++;
        }

        color_index++;

        if (color_index == 3) {
            color_index = 0;
        }

        int count;
        ioctl(socketFileDescriptor, FIONREAD, &count);

        if (count > 0) {
            msgReturnCode = NetworkService::readMessageFromSocket(socketFileDescriptor, messageReceived, 256);
            std::cout << "Color::setupColorThread ---- read in socket"
                      << messageReceived
                      << std::endl;

            std::vector<std::string> toto = split(messageReceived, ',');
            std::string * array = &toto[0];
            debugArray(array, 4);

            std::cout << "=========" << std::endl;

            int *intColors = getIntColors(array);
            // int intColors[4] = {2, 2, 2, 2};
            debugArray(intColors, 4);

            setLEDColors(intColors);
        }
        //if (NetworkService::readMessageFromSocket(socketFileDescriptor, messageReceived, 256) < 0) {
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));
            //continue;
        //}
        /*std::cout << "Color::setupColorThread ---- Message received from Socket !"
                  << messageReceived << std::endl;*/

    }
    std::cout << "Color::setupColorThread ---- Color process ended." << std::endl;
}

void debugArray(std::string * arr, int ito) {
    std::string* it(0);
    int c = 0;
    do  {
        it = &arr[c];
        std::cout << "TEST _____ " << *it << std::endl;
        ++c;
    } while (c < ito);
}

void debugArray(int * arr, int ito) {
    int * it(0);
    int c = 0;
    do  {
        it = &arr[c];
        std::cout << "TEST _____ " << *it << std::endl;
        ++c;
    } while (c < ito);
}

int* getIntColors(std::string * arr) {
    int res[4];
    std::string* it(0);
    int c = 0;
    do  {
        it = &arr[c];
        res[c] = stoi(*it);
        ++c;
    } while (c < 4);
    return &res[0];
}

/**
 * Initialize the LEDs Pins
 * @method setupPins
 */
static void setupPins() {
    uint8_t i;

    // initialize all of the output pins

    // LED column lines
    for (i = 0; i < NUM_LED_COLUMNS; i++) {
        pinMode(ledcolumnpins[i], OUTPUT);

        // with nothing selected by default
        digitalWrite(ledcolumnpins[i], 1);
    }

    // LED row lines
    for (i = 0; i < NUM_COLORS; i++) {
        pinMode(colorpins[i], OUTPUT);

        // with nothing driven by default
        digitalWrite(colorpins[i], 0);
    }
}

/**
 * Loops through the available LEDs to light them one by one.
 * @method scan
 */
static void scan() {
    // Select a column
    digitalWrite(ledcolumnpins[led_index], LOW);

    // write the row pins
    if (LED_colors[led_index][color_index]) {
        switch (color_index) {
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

    digitalWrite(ledcolumnpins[led_index], HIGH);    //deselect current column

    digitalWrite(colorpins[color_index], LOW);
}

/**
 * This method receives new colors to set to the RGB LEDs.
 * @method setLEDColors
 * @param colors
 */
static void setLEDColors(int colors[4]) {
    uint8_t i;
    uint8_t j;

    for (i = 0; i < NUM_LED_COLUMNS; i++) {
        // Reset all values to false
        for (j = 0; j < NUM_COLORS; j++) {
            LED_colors[i][j] = false;
        }

        switch (colors[i]) {
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


