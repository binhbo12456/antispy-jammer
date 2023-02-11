/*
 * Antispy ultrasonic device for preventing voice recording 
 * with ultrasonic waves generation based on ATTINY85,
 * ATTINY85 fuses have been set to internal PLL clock 16MHz 
 * with Resistor Ladder 5-bit Digital-to-Analog converter
 * and piezzo-electric driver
 * (C) Adam Loboda 2021, adam.loboda@wp.pl
 */

#include <stdint.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

// PIN - PORT ASSIGNMENT DEFINITION FOR 5-BIT DAC DEVICE
#define	OUTPUTPORT		PORTB
#define	OUTPUTPORTCTRL		DDRB

 

int main(void)
{
        uint16_t sequence;
        uint8_t pulsewidth, amplitude, i;

        // seeding random number generator
        srand(1234);
        // SET OUTPUT PIN ON ALL OUTPUT PORTS
        
        OUTPUTPORTCTRL = 0b00011111;  //set all 5 LOWER bit pins as output
        OUTPUTPORT     = 0b00000000;  //set all 5 LOWER bit pins to ZERO

       //* neverending loop */
       while (1) 
       { 

          // generating WAVE on BIT0-BIT5 DAC outputs
          // randomized length of the pulse to fit within 23-27kHz frequency
          pulsewidth = 10 + (rand() % 60) ;
   
   
          // randomized amplitude of the pulse to fit within 5-bit value
          // uncomment this if you want random amplitude
          //amplitude = rand() % 16;
          //amplitude = amplitude +15;
 
          // sending bulk of these pulses before switching frequency and amplitude
          // works best when 50 pulses sent
          //
          for(sequence=0; sequence<50; sequence++)
           {


           // send HIGH VOLTAGE - this time square wave
           // PB0 may serve as GND for PAM8403 module audio input
           // sending pseudorandom amplitude value to DAC
           // uncomment this for random amplitude
           //OUTPUTPORT = amplitude; 
           // or use this for no AM modulation instead
           OUTPUTPORT = 0b00000111;

           // now delay to achieve desired frequency
           for(i=0; i<pulsewidth; i++)
             {
              asm volatile (
           "    nop	\n" 
                );
              };
           //

           // send LOW VOLTAGE - this time square wave
           OUTPUTPORT = 0; 
           // now delay to achieve desired frequency
           for(i=0; i<(85 - pulsewidth); i++)
             {
              asm volatile (
           "    nop	\n" 
                );
              };
           //
           };

      
        }; // neverending loop 

};  // end of MAIN



