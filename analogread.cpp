#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <string>


AnalogIn light(PA_4);
AnalogIn moisture(PA_0);


float light_value;
float moisture_value;


bool checker = false;

// calculations are in lux for light and RH for moisture in a 
void ReadADC(void) {
            light_value = light.read_u16()*(5.00/65536.00)/1000 * (10/6e-5);
						moisture_value = moisture.read_u16()*100.00/65536.00;
            checker = false; 
    } 



