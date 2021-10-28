#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <string>

#define RAISED  0;
#define LOWERING 1;
#define DOWN 2;
#define RISING 3;

AnalogIn light(PA_4);
AnalogIn moisture(PA_0);


float light_value;
float moisture_value;


bool checker = false;
bool printer_checker;
bool up = true;
bool summer = true;
int state = RAISED;
string s_state = "RAISED";

Ticker sample;
Ticker printer;
Timeout timer;

void tick_isr(void) {checker = true;}
void printer_isr(void) {printer_checker = true;}
void timer_isr(void){up = !up;}
void summer_winter(void){summer = !summer;}

Thread thread;
Thread thread_2;

void ReadADC(void) {
            light_value = light.read_u16()*100.00/65536.00;
						moisture_value = moisture.read_u16()*100.00/65536.00;
            checker = false; 
    } 



