#include "mbed.h"



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

}
	}