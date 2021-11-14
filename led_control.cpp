/**Explitted part of the code as each of us has different leds (commmon cathode/common anode).
This one corresponds to the Common Anode led**/


#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <string>

#define TEST 0
#define NORMAL 1


extern bool RGBerror;
extern DigitalOut Red;
extern DigitalOut Blue;
extern DigitalOut Green;
extern int red_counter;
extern int blue_counter;
extern int rgb_readings[4];
extern int green_counter;
extern float rhData;
extern float tData;
extern float moisture_value;
extern float light_value;
extern int mode;
extern float x_value, y_value, z_value;
bool release = false;

bool changeled = false;
Semaphore sem(0);

Thread threadProblems;


void setLed(){

	while(true){
				
				while(mode == TEST){
				if(changeled){
						changeled = false;
					if(!RGBerror){
					
								if(rgb_readings[0]>6000)
							{
									Red    = 0;
									Green  = 0;
									Blue   = 0;		
							}
							else
								{
									if(rgb_readings[1]<100 && rgb_readings[2]<100 && rgb_readings[3]<100) //If low: none
										{
											Red    = 1;
											Green  = 1;
											Blue   = 1;
										}
										else
											{
											if(rgb_readings[1]>rgb_readings[2] && rgb_readings[1]>=rgb_readings[3]) //If max=RED
												{
													Red    = 0;
													Green  = 1;
													Blue   = 1;
												}else if(rgb_readings[2]>rgb_readings[1] && rgb_readings[2]>rgb_readings[3]) //If max=Green
												{
													Red    = 1;
													Green  = 0;
													Blue   = 1;
												}
												else if(rgb_readings[3]>rgb_readings[1] && rgb_readings[3]>rgb_readings[2])   //If max=Blue
												{
													Red    = 1;
													Green  = 1;
													Blue   = 0;						
												}
											}
								
								}
							}else 
						printf("************Please Connect RGB sensor*******************");
						}
					}
				/**Limits for Montsera Mansoni**/
					while(mode == NORMAL){
								release = false;
	
							if(tData > 25 || tData < 20 && !release){
								Red = 0;
								Green = 1;
								Blue = 1;
							  ThisThread::sleep_for(chrono::milliseconds(2000));
								}
							
							if(rhData < 60 && !release){
								Red = 1;
								Green = 0;
								Blue = 1;
							  ThisThread::sleep_for(chrono::milliseconds(2000));
							}
							
							if(light_value < 15000 && !release){
								Red = 1;
								Green = 1;
								Blue = 0;
							  ThisThread::sleep_for(chrono::milliseconds(2000));
							}
							
							if(moisture_value < 50 && !release){
								Red = 1;
								Green = 0;
								Blue = 0;
							  ThisThread::sleep_for(chrono::milliseconds(2000));
							}
							
							if(!(rgb_readings[2]>rgb_readings[1] && rgb_readings[2]>rgb_readings[3]) && !release){
								Red = 0;
								Green = 0;
								Blue = 1;
							  ThisThread::sleep_for(chrono::milliseconds(2000));
							}
							if(!((x_value > 2 || x_value < -2) && (y_value > 2 || y_value < -2) 
								&& (z_value < 8 || z_value > 10)) &&!release){
								Red = 0;
								Green = 1;
								Blue = 0;
							 ThisThread::sleep_for(chrono::milliseconds(2000));
								}
								Red = 1;
								Green = 1;
								Blue = 1;
					}
				}
			}

				

