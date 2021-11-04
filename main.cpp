
/*******************************************************************************
 *******************************  Includes  ***********************************
 ******************************************************************************/
#include "mbed.h"
#include "MMA8451Q.h"



/*******************************************************************************
 *******************************  Variables  ***********************************
 ******************************************************************************/
 
extern uint32_t _rhData;
extern int32_t  _tData;
extern float light_value;
extern float moisture_value;

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
			
			if(present == 0x1A){
				acc.getAccAllAxis(result);
				printf("Rotation: x =%f \t y=%f\t z=%f\n",result[0],result[1],result[2]);
			}else{
				printf("Please connect accelerometer");
				present = acc.getWhoAmI();
			}
	}
}