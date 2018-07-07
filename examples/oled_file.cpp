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

						
*********************************************************************/

#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include <stdio.h>
#include <getopt.h>

#define PRG_NAME        "oled_file"
#define PRG_VERSION     "1.1"

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

void display_file(char* name)
{
	FILE	*fp;
	int	lineCounter = 0;
	char	line[100];
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);

	display.display();

	fp = fopen(name, "r");
	if (fp != NULL) {
  		display.clearDisplay();
		while (fgets(line, 80, fp) != NULL) {
			lineCounter++;
			line[strlen(line)-1] = 0;
			if (lineCounter > 8)
				break;
			line[21] = 0;
			if (strstr(line, "\\") != NULL) {
				display.setTextSize(2);
				strcpy(line, &line[2]);
			}
			display.print(line);
			display.print("\n");
		 	display.setTextSize(1);
		}
		fclose(fp);
	}
	display.display();
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
  if ( !display.init(OLED_I2C_RESET,opts.oled) )
      exit(EXIT_FAILURE);

  display.begin();
	
  // init done
  display.clearDisplay();   // clears the screen  buffer
  display.display();   		// display it (clear display)

	display.clearDisplay();

	display.setTextSize(1);
 	display.setTextColor(WHITE);
	display.setCursor(0,0);
	if (argc == 2) {
		// printf("Debug info: %d, %s\n", argc, argv[1]);
		display_file(argv[1]);
  	}
  	else {
		display_file("/tmp/display");
		// Free PI GPIO ports
		// sleep(2);
		// display.startscrollright(0x00, 0x08);
  		// display.display();   		// display it (clear display)
	}
	display.close();
}


