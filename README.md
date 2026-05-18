# smart-irrigation-system
![Project Photo](<img width="1280" height="960" alt="smart" src="https://github.com/user-attachments/assets/1eeff43e-f48b-4115-9eb3-56f14d55e847" />

## features
          -soil moisture detection and monitoring
          -water pumping system
          -mqqt smoke notifications
          -esp32s3 webside display and control
          -humidity balancing and detection
          -rain detection



this project main function is plant irrigating and monitoring system using esp32s3and arduino uno which basically reduces human labour 
## Components
          -arduino unox2
           -esp 32
           - mq smoke sensor=smoke and fire detection
           -soil moist sendor=soilmoisture
           -water level sensor=tank water level sensing
           -humidity sensor=detect temperature and humidity
           -rain drop sensor=detect rain drop
           -lcd screen=display rain drop and humidity
           -dc motor=for cooling system
           -bread board= circuit 
           -jumper wires=connecting cables
           -5v submersable water pump+umping water from tank
           -tube = transfer water from pump to crops
           -potentio meter=for lcd
           -HC bluetooth module
           -uv led
           WOOD FOROVEL ALL CAse 
           
 mq and soil sensors reads data and send it to the esp 32s3 which has its own local area website which we can access wit the ip adress it gives us in the serial monitor of our programming applications then on the website thereis a data chart which is coded by java scrips it gives live data charts for the soil moisture sensor and provides it to us on the website dachboard it also has an alerting system for the mq smoke sensor whih alerts us when smoke is detected and also has a percent bar that shows us data from the water level sensor the pump,lcd,relay,raindrop,humidity are all accessed from the arduino uno recives data from the humidity and raindrop sensor and displays it on the lcd screen and the other arduino is connected to a bluetooth module to recive signals from mobile devices from a certain app to control(switching on /off ) the pump module and the uv light led and the cooling system which is used to cool down the crops when temperature is high which we can  see on the lcd display this all coordinates to make this project
  
