/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *********************************************
 *
 * PWM example using the PwmOut API
 *
 *********************************************
 *Description: McLab12_MOSFET_PWM_3chLED_OS6_tk1
 * Hardware
 * L432KC or similar with PWM capable outputs.
 * The L432KC pin D13 for onboard LED is not PWM capable!
 * LEDs and xxx Ohm resistor. For example for a 12 V supply,
 * three LEDs in series select a 120 Ohm resistor for 20 mA LEDs. 
 * For testing 3 pieces MOSFET IRL540, LEDs, resistors. 
 * Connect:
 * L432KC VIN --- 5V from a 5 V regulator on 12 V supply.
 * L432KC D3 -- MOSFET gate 
 * L432KC D5 -- MOSFET gate
 * L432KC D6 -- MOSFET gate
 * 
 * MOSFET drain -- resistor -- LEDs -- 12 V.
 * MOSFET source -- GND
 * Operating system OS 6.0
 * Timo Karppinen 5.10.2021  Apache-2.0
 */

#include "mbed.h"
#include <cmath>

// change every x milliseconds
#define changing_RATE     10ms

// Initialise the digital pins as a pwm output
// The pin needs to be one of the PWM capable pins ! 
PwmOut pwmMOSFET1(D3);
PwmOut pwmMOSFET2(D5);
PwmOut pwmMOSFET3(D6);
// Variables for the pwm
int intensCount1 = 1;
int intensCount2 = 1;
int intensCount3 = 1;
float angle1 = 0.0;
float angle2 = 0.0;
float angle3 = 0.0;
float intens1 = 1.0;   // from 0.0 to 1.0 
float intens2 = 1.0; 
float intens3 = 1.0; 
float usT = 1000;   // f = 1000 Hz  T = 1 ms = 1000 us
                    // f = 10000 Hz  T = 100 us
int main()
{
    pwmMOSFET1.period_us(usT);
    pwmMOSFET2.period_us(usT);
    pwmMOSFET3.period_us(usT);
    pwmMOSFET1.write(1.0f);
    pwmMOSFET2.write(1.0f);
    pwmMOSFET3.write(1.0f);
    
    while (true) {
  
        angle1 = angle1 + 0.1;
        intens1 = 0.5 + 0.5 *sin(angle1);
        
        angle2 = angle2 + 0.08;
        intens2 = 0.6 + 0.4 *sin(angle2);
        
        angle3 = angle3 + 0.02;
        intens3 = 0.7 + 0.3 *sin(angle3);
        
        if(angle1 > 628.31852){
            angle1 = 0.0;
            }
        if(angle2 > 628.31852){
            angle2 = 0.0;
            }
        if(angle3 > 628.31852){
            angle3 = 0.0;
            }
        
        
        pwmMOSFET1.write(intens1);
        pwmMOSFET2.write(intens2);
        pwmMOSFET3.write(intens3);
        
        ThisThread::sleep_for(changing_RATE);
    }
}