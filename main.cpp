
/*******************************************************************************
 *******************************  Includes  ***********************************
 ******************************************************************************/
#include "mbed.h"
#include "MMA8451Q.h"
#include "TCS3472_I2C/TCS3472_I2C.h"
#include "MBed_Adafruit_GPS.h"

using namespace std::chrono;
BufferedSerial * gps_Serial;




/*******************************************************************************
 *******************************  Global Variables  ****************************
 ******************************************************************************/
 
extern uint32_t _rhData;
extern int32_t  _tData;
extern float light_value;
extern float moisture_value;
float result[3] = {0,0,0};
int rgb_readings[4]; // Declare a 4 element array to store RGB sensor readings



//Show the sensed colour

DigitalOut Red(PH_0);
DigitalOut Green(PH_1);
DigitalOut Blue(PB_13);

Thread AnalogThread(osPriorityNormal, 1024);
Thread I2CThread(osPriorityNormal, 1024);
Thread GPSThread;

bool AnalogFinish;
bool I2CFinish;
bool GPSFinish;


bool RTHerror;
bool AccError;
bool RGBerror;
/*******************************************************************************
 *******************************     Global FUNCTIONS   ************************
 ******************************************************************************/

extern void readSensor(void);
extern bool RTHpresent();
extern void ReadADC(void);

void AnalogRead(void){
	while(true){
		ReadADC();
		AnalogFinish = true;
		wait_us(2000000);
	}
}

void I2CRead(void){
	TCS3472_I2C rgb_sensor (PB_9, PB_8);
	MMA8451Q acc(PB_9,PB_8,0x1c<<1);

	int present;
	while(true){
		//read of temperature and humidity first
			if(RTHpresent()){
					readSensor();
					RTHerror = false;
			}
			else
				RTHerror = true;
		//Now the accelerometer
			present = acc.getWhoAmI();
			if(present == 0x1A){
				acc.getAccAllAxis(result);
				AccError = false;
			}
			else
				AccError = true;
			//rgb sensor at last
				rgb_sensor.enablePowerAndRGBC();
				rgb_sensor.getAllColors(rgb_readings);
				RGBerror = false;
			
			I2CFinish = true;
			wait_us(2000000);
		  
	}
}


int main(void) {
	
	AnalogThread.start(AnalogRead);
	I2CThread.start(I2CRead);
	AnalogFinish = false;
	I2CFinish = false;
	
	  gps_Serial = new BufferedSerial(PA_9, PA_10,9600); //serial object for use w/ GPS
    Adafruit_GPS myGPS(gps_Serial); //object of Adafruit's GPS class
    char c; //when read via Adafruit_GPS::read(), the class returns single character stored here
    Timer refresh_Timer; //sets up a timer for use in loop; how often do we print GPS info?
    const int refresh_Time = 2000; //refresh time in ms

    myGPS.begin(9600);  //sets baud rate for GPS communication; note this may be changed via Adafruit_GPS::sendCommand(char *)
                        //a list of GPS commands is available at http://www.adafruit.com/datasheets/PMTK_A08.pdf

    myGPS.sendCommand(PMTK_SET_NMEA_OUTPUT_GGA); //these commands are defined in MBed_Adafruit_GPS.h; a link is provided there for command creation
    myGPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    myGPS.sendCommand(PGCMD_ANTENNA);

    printf("Connection established at 9600 baud...\r\n");

    

    refresh_Timer.start();  //starts the clock on the timer

	
	
  while (1){
	
			if(AnalogFinish && I2CFinish){
				AnalogFinish = false;
				I2CFinish = false;
				
				printf("SOIL MOISTURE: %.2f\n", moisture_value);
				printf("LIGHT: %.2f\n", light_value);
				
				
				c = myGPS.read();   //queries the GPS

//        if (c) { printf("%c", c); } //this line will echo the GPS data if not paused

        //check if we recieved a new message from GPS, if so, attempt to parse it,
        if ( myGPS.newNMEAreceived() ) {
            if ( !myGPS.parse(myGPS.lastNMEA()) ) {
                continue;
            }
        }

        //check if enough time has passed to warrant printing GPS info to screen
        //note if refresh_Time is too low or pc.baud is too low, GPS data may be lost during printing
        if (duration_cast<milliseconds>(refresh_Timer.elapsed_time()).count() >= refresh_Time) {
        //if (refresh_Timer.read_ms() >= refresh_Time) {
            refresh_Timer.reset();
					
					printf("GPS - #Sats: %d\r", myGPS.satellites);
            if ((int)myGPS.fixquality > 0) {
                printf("Lat(VTC): %5.2f %c\r", myGPS.latitude, myGPS.lat);
							  printf("Long(VTC): %5.2f %c\r", myGPS.longitude, myGPS.lon);
                printf("Altitude: %5.2f m\r", myGPS.altitude);
            }else
						printf("NOT ENOUGH QUALITY TO GET LOCATION ");
						
						printf("GPS Time: %d:%d:%d.%u\r\n", myGPS.hour + 1, myGPS.minute, myGPS.seconds, myGPS.milliseconds);
        }
				
					if(!RTHerror){		
				printf("TEMP/HUM -");
				printf("Temperature: %d ,%3d oC ", _tData / 1000, _tData % 1000);
				printf("Relative Humidity: %d,%3d % \n", _rhData / 1000, _rhData % 1000);
					}
					else
				printf("**********PLEASE CONNECT THE RTH SENSOR***********\n");
					
				if(!AccError){
					printf("ROTATION: X_axis= %.2f\t Y_axis= %.2f\t Z_axis= %.2f \n",
					result[0] * 10,result[1] * 10,result[2] * 10);
				}else
				printf("**********PLEASE CONNECT ACCELEROMETER*********\n");
				
				if(!RGBerror){
					printf("COLOR SENSOR: Clear: %d, Red: %d, Green: %d, Blue: %d\n",rgb_readings[0],rgb_readings[1],rgb_readings[2],rgb_readings[3]);
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
					printf("Please Connect RGB sensor");

			}

	
	}
}
