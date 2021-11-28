# Embedded Plant Monitoring

Final project of the Embedded platforms and communications for iot subject from Internet of Things university master's degree: https://www.deepl.com/es/translator#es/en/Master%20universitario%20de%20internet%20de%20las%20cosas

## The project includes the following devices:

- B-L072Z-LRWAN1 (Electronic Platform)
- Si7021 (Temperature and Humidity)
- HW5P-1 (Ambient Light)
- SEN-13322 (Soil moisture)
- TCS34725 (Leaf Colour)
- MMA8451Q (Accelerometer)
- FGPMMOPA6H (GPS)
- RGB LED

## The project includes the following system requirements:

- Temperature in the range of -10ºC to 50ºC.
- Relative humidity in the range of 25%HR to 75%HR.
- Ambient light in %, corresponding 0% to total darkness and 100% to maximum light.
- Soil moisture in %, corresponding 0% to total dryness and 100% to maximum moisture.
- Colour of one leaf of the plant. The four associated parameters are clear, red, green, and blue values.
- Global location of the plant should be registered. The GPS module also offer the current time (only time, date is optional), that will be used to timestamp all the measurements taken by the system.
- The acceleration of the plant. At least the three axes (X, Y and Z) values should be monitored. 

## The project includes the following functionalities:

- TEST MODE
  - First mode to develop: Check connections and sensor management
  - All the required variables should be monitored every 2 seconds.
  - The system sends every 2 seconds all the measured values to the computer (using the USB virtual COM port of the B-L072Z-LRWAN1 board).
  - The RGB LED should be coloured in the dominant colour detected by the colour sensor.
  - In this mode, the LED1 of the B-L072Z-LRWAN1 board should be ON.

- NORMAL MODE
  - All the required variables should be monitored with a cadence of 30s.
  - The system sends every 30 seconds all the measured values to the computer (using the USB virtual COM port of the B-L072Z-LRWAN1 board).
  - The system calculates the mean, maximum and minimum values of temperature, relative humidity, ambient light and soil moisture every hour. These values are sent to the computer when calculated.
  - The system calculates the dominant colour of the leave every hour. This means to calculate which colour has appeared as dominant more times during the last hour. This value is sent to the computer when calculated.
  - The system calculates the maximum and minimum values of the three axes (X, y and Z) of the accelerometer every hour. These values are sent to the computer when calculated.
  - The global location of the plant (coordinates) is sent to the computer every 30 seconds. This should include the GPS time converted to local time.
  - Limits for every measured variable (temperature, humidity, ambient light, soil moisture, colour and acceleration) should be fixed. If current values of the measured parameters are outside the limits, the RGB LED should indicate this situation using different colour for every parameter.
  - In this mode, the LED2 of the B-L072Z-LRWAN1 board should be ON

(Some parameters like the monitored cadence are changed in order to make tests)

