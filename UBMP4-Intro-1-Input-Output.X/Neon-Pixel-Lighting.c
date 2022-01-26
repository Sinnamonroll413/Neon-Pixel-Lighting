/*==============================================================================
 Project: NeoPixel-Starter
 Date: January 19, 2022
 
 This program demonstrates basic NeoPixel data transmission.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program constant definitions
const unsigned char LEDs = 40;

// Program variable definitions
unsigned char red = 10;
unsigned char green = 10;
unsigned char blue = 10;
bool red_up = true;
bool green_up = true;
bool blue_up = true ;

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
void neopixel_fill(unsigned char leds)
{
    for(leds; leds != 0; leds --)
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
        if(SW3 == 0)
        {
            if(red_up == true)
            {
                if(red < 255)
                {
                    red++;
                }
                else
                {
                    red_up = false;
                }
            }
            else
            {
                if(red > 0)
                {
                    red --;
                }
                else
                {
                    red_up = true;
                }
            }
        }  


        if(SW4 == 0)
        {
            if(green_up == true)
            {
                if(green < 255)
                {
                    green++;
                }
                else
                {
                    green_up = false;
                }
            }
            else
            {
                if(green > 0)
                {
                    green --;
                }
                else
                green_up = true;
            }
        }  


        if(SW5 == 0)
        {
            if(blue_up == true)
            {
                if(blue < 255)
                {
                    blue++;
                }
                else
                {
                    blue_up = false;
                }
            }
            else
            {
                if(blue > 0)
                {
                    blue --;
                }
                else

                blue_up = true;
            }
        }  
        
        if(SW2 == 0)
        {
          
        }
        neopixel_fill(LEDs);
        __delay_ms(20);

        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}
