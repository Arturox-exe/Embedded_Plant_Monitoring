#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <string>


AnalogIn light(PA_4);
AnalogIn moisture(PA_0);


float light_value;
float moisture_value;


bool checker = false;


void ReadADC(void) {
            light_value = light.read_u16()*100.00/65536.00;
						moisture_value = moisture.read_u16()*100.00/65536.00;
            checker = false; 
    } 



