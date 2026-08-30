# H743_DASH_LOGGER_KTM_990
This is a seprate physical display to compliment the trailtech voyger on my ktm 990 with the added ability to data log. 

NOTE: I am not getting any senor data from the ecu's canbus (KWP2000 SEA ISO 2014230-2 protocol), I am reading voltages directly and calculating the variables in the controllers. I will be datalogging every 10ms and I can guarantee the log rate and sensor data. Basically I know nothing about the ktm 990's keihin ecu's canbus and I can find very little information on the pid's for each value I am interested in. 

The controller is a STM32H743IIT6 sold online pictured below. The board has w9825g6kh SDRAM IC and an w25q128 QSPI flash IC onboard. The board also had a SD card slot and a LDTC FPC connector that is not used for this project. 

<img width="800" height="800" alt="image" src="https://github.com/user-attachments/assets/0376ca0c-f9fb-41ce-ad42-d74cee1f4d40" />

the display is a 3.5inch transflective LCD with a st7365p controller IC. the display is a viewe PN: UEED035HV-RX40-L001A pictured below 

<img width="768" height="648" alt="image" src="https://github.com/user-attachments/assets/5fb465dd-2ef4-4d7b-9d3a-f7f5a3b2a06c" />

The whole idea is this stm32 controller will be attached on the dash next to a traitech voyger as a complementary information screen, this controller will be connected to an additional controller referred to as a "sensor hub" via CAN or FDCAN.

DATA collected directly from the motorcycle by the main dash controller will be 
1. RPM
2. Engine temp (will be relayed to the voyger via a digital potentiometer)
3. speed via front wheel (will also be relayed to the voyger)
4. front and rear wheel pressure and temperature via bluetooth wheel sensors 

Data that will be relayed to main controller via sensor hub
1. one of the injectors pulse width
2. both map sensors
3. throttle position
4. front and rear cylinder LAMBDA with 2 bosch lsu4.9 and 2 14point7 lambra controllers

Undecided to which controller this will connect 
1. hydrostatic pressure sensor for fuel level

Data to be displayed on LCD in normal rider mode 
1. wheel status
2. live fuel consumption
3. current fuel capacity
4. current range

The main controller will also datalog all information onto an sdcard for tunning the fuel maps and ignition maps.  

NOTE: I am not getting any senor data from the ecu's canbus (KWP2000 SEA ISO 2014230-2 protocol), I am reading voltages directly and calculating the variables in the controllers. I will be datalogging every 10ms and I can guarantee the log rate and sensor data. Basically I know nothing about the ktm 990's keihin ecu's canbus and I can find very little information on the pid's for each value I am interested in. The learning curve is immense with this project and I don't want to get stuck down with reverse engineering the motorcycles canbus communication. 
