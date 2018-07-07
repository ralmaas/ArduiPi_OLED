/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32|64 size display using SPI or I2C to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution

02/18/2013 	Charles-Henri Hallard (http://hallard.me)
	Modified for compiling and use on Raspberry ArduiPi Board
	LCD size and connection are now passed as arguments on 
	the command line (no more #define on compilation needed)
	ArduiPi project documentation http://hallard.me/arduipi

Example of a watch with 2x font
						
*********************************************************************/

#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <signal.h>

#define PRG_NAME        "oled_time"
#define PRG_VERSION     "1.0"
#define	SIZE 32

// Instantiate the display
ArduiPi_OLED display;

// Config Option
struct s_opts
{
	int oled;
	int verbose;
} ;

// default options values
s_opts opts = {
	OLED_ADAFRUIT_I2C_128x32,	// Default oled
	false										// Not verbose
};

void display_time(int sig)
{
	char buffer[SIZE];                                          
	time_t curtime;                                             
	struct tm *loctime; 

	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(16, 10);
	display.clearDisplay();   // clears the screen  buffer
	display.display();

	// Get current time
	curtime = time(NULL);
	loctime = localtime(&curtime);
	// Ready to print
	sprintf(buffer, "%2.2d:%2.2d:%2.2d\n", loctime->tm_hour, loctime->tm_min, loctime->tm_sec);

	display.print(buffer);
	display.display();
	alarm(1);	// Set new trigger
}

/* ======================================================================
Function: main
Purpose : Main entry Point
Input 	: -
Output	: -
Comments: 
====================================================================== */
int main(int argc, char **argv)
{
	printf("argc=%d\n", argc);
	if (argc == 2)
		opts.oled = OLED_ADAFRUIT_I2C_128x64;
	if ( !display.init(OLED_I2C_RESET,opts.oled) )
		exit(EXIT_FAILURE);

	display.begin();
	
	// init done
	display.clearDisplay();   // clears the screen  buffer
	display.display();   		// display it (clear display)

	signal(SIGALRM, &display_time);
	alarm(1);
	while(1);
	// display_time();

	display.close();
}


