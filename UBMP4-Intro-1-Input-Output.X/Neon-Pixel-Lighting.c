/*==============================================================================
 Project: NeoPixel-Starter
 Date: January 27, 2022
 ==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program constant definitions
#define LEDs 10

// Program variable definitions
unsigned char red;              // Colour or colour-adjusted output values
unsigned char green;
unsigned char blue;

unsigned char red_index = 10;   // Raw colour index values
unsigned char green_index = 10;
unsigned char blue_index = 10;

bool red_up = true;             // Colour adjustment direction variables
bool green_up = true;
bool blue_up = true;

//Program Modes
#define off 0
#define on 1
#define rainbow 2
#define red 3
#define breathing 4
#define colour 5

unsigned char mode = off

// Gamma 1.8 colour output look-up table
const char gamma[256] = {
0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 1, 1, 1, 1, 1, 2,
2, 2, 2, 2, 3, 3, 3, 3,
4, 4, 4, 4, 5, 5, 5, 6,
6, 6, 7, 7, 8, 8, 8, 9,
9, 10, 10, 10, 11, 11, 12, 12,
13, 13, 14, 14, 15, 15, 16, 16,
17, 17, 18, 18, 19, 19, 20, 21,
21, 22, 22, 23, 24, 24, 25, 26,
26, 27, 28, 28, 29, 30, 30, 31,
32, 32, 33, 34, 35, 35, 36, 37,
38, 38, 39, 40, 41, 41, 42, 43,
44, 45, 46, 46, 47, 48, 49, 50,
51, 52, 53, 53, 54, 55, 56, 57,
58, 59, 60, 61, 62, 63, 64, 65,
66, 67, 68, 69, 70, 71, 72, 73,
74, 75, 76, 77, 78, 79, 80, 81,
82, 83, 84, 86, 87, 88, 89, 90,
91, 92, 93, 95, 96, 97, 98, 99,
100, 102, 103, 104, 105, 107, 108, 109,
110, 111, 113, 114, 115, 116, 118, 119,
120, 122, 123, 124, 126, 127, 128, 129,
131, 132, 134, 135, 136, 138, 139, 140,
142, 143, 145, 146, 147, 149, 150, 152,
153, 154, 156, 157, 159, 160, 162, 163,
165, 166, 168, 169, 171, 172, 174, 175,
177, 178, 180, 181, 183, 184, 186, 188,
189, 191, 192, 194, 195, 197, 199, 200,
202, 204, 205, 207, 208, 210, 212, 213,
215, 217, 218, 220, 222, 224, 225, 227,
229, 230, 232, 234, 236, 237, 239, 241,
243, 244, 246, 248, 250, 251, 253, 255};


// Shift 8-bits of NeoPixel data
void neopixel_shift(unsigned char col)
{
    for(unsigned char bits = 8; bits != 0; bits --)
    {
        H1OUT = 1;
        if((col & 0b10000000) == 0)
        {
            H1OUT = 0;
        }
        NOP();
        H1OUT = 0;
        col = col << 1;
    }
}

// Fill NeoPixel strip with colour from the red, green, and blue variables
void neopixel_fill(unsigned char leds)
{
    for(leds; leds != 0; leds--)
    {
        neopixel_shift(green);
        neopixel_shift(red);
        neopixel_shift(blue);
    }
}


int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
    while(1)
    {
        while(mode = off)
        {
            red_backup = red;
            red = 0;
            green_backup = green;
            green = 0;
            blue_backup = blue;
            blue = 0;

            neonpixel_fill(LEDs);
            __delay_ms(20);
            while(SW2 ++ 0);
            red = red_backup;
            mode = colour;
        }
        while(mode = colour)
        if(SW3 == 0)            // Adjust red index value
        {
            if(red_up == true)
            {
                if(red_index < 255)
                {
                    red_index++;
                }
                else
                {
                    red_up = false;
                }
            }
            else
            {
                if(red_index > 0)
                {
                    red_index--;
                }
                else
                {
                    red_up = true;
                }
            }
        }
        
        if(SW4 == 0)            // Adjust green index value
        {
            if(green_up == true)
            {
                if(green_index < 255)
                {
                    green_index++;
                }
                else
                {
                    green_up = false;
                }
            }
            else
            {
                if(green_index > 0)
                {
                    green_index--;
                }
                else
                {
                    green_up = true;
                }
            }
        }
        
        if(SW5 == 0)            // Adjust blue index value
        {
            if(blue_up == true)
            {
                if(blue_index < 255)
                {
                    blue_index++;
                }
                else
                {
                    blue_up = false;
                }
            }
            else
            {
                if(blue_index > 0)
                {
                    blue_index--;
                }
                else
                {
                    blue_up = true;
                }
            }
        }
        If(SW2 == 0)
        {
            mode = breathing
            while(SW2 == 0)
        }


        
        // Gamma adjust output colours
        red = gamma[red_index];
        green = gamma[green_index];
        blue = gamma[blue_index];
        
        // Fill the strip with adjusted colours
        neopixel_fill(LEDs);
        __delay_ms(20);

        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}
