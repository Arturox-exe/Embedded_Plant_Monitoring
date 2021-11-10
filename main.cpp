
/*******************************************************************************
 *******************************  Includes  ***********************************
 ******************************************************************************/
#include "mbed.h"
#include "MMA8451Q.h"
#include "TCS3472_I2C/TCS3472_I2C.h"



/*******************************************************************************
 *******************************  Variables  ***********************************
 ******************************************************************************/
 
extern uint32_t _rhData;
extern int32_t  _tData;
extern float light_value;
extern float moisture_value;
int rgb_readings[4]; // Declare a 4 element array to store RGB sensor readings

TCS3472_I2C rgb_sensor (PB_9, PB_8);

//Show the sensed colour

DigitalOut Red(PH_0);
DigitalOut Green(PH_1);
DigitalOut Blue(PB_13);
/*******************************************************************************
 *******************************     FUNCTIONS   *******************************
 ******************************************************************************/

extern void readSensor(void);
extern bool RTHpresent();
extern void ReadADC(void);


/**void printer_thread(void) {
    while(true){     
	
    } 
}**/


int main() {
	float result[3] = {0,0,0};
	MMA8451Q acc(PB_9,PB_8,0x1c<<1);
	int present = acc.getWhoAmI();
	rgb_sensor.enablePowerAndRGBC();
  while (1){
			wait_us(1000000);
			if(RTHpresent()){
					printf("Temperature: %d ,%3d oC\r\n", _tData / 1000, _tData % 1000);
					printf("Humidity: %d,%3d%\r\n", _rhData / 1000, _rhData % 1000);
					readSensor();
			}
			else
				printf("please connect RHT sensor \n\n");
			
			 ReadADC();
			 printf("Light: %.2f % \n", light_value);
			 printf("Moisture:  %.2f % \n", moisture_value);
			 rgb_sensor.getAllColors(rgb_readings);
			 
			if(present == 0x1A){
				acc.getAccAllAxis(result);
				printf("Rotation: x =%f \t y=%f\t z=%f\n",result[0],result[1],result[2]);
			}else{
				printf("Please connect accelerometer");
				present = acc.getWhoAmI();
			}
			printf("Reading: clear %d, red%d,green%d, blue%d\n",rgb_readings[0],rgb_readings[1],rgb_readings[2],rgb_readings[3]);
			if(rgb_readings[0]>6000)
						{
								Red    = 1;
								Green  = 1;
								Blue   = 1;		
						}
						else
							{
								if(rgb_readings[1]<100 && rgb_readings[2]<100 && rgb_readings[3]<100) //If low: none
									{
										Red    = 0;
										Green  = 0;
										Blue   = 0;
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
	}
}