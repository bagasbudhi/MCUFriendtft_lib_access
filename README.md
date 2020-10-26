# Porting-Library-Arm-32-bit-Cortex--M3-CPU
Porting library Arduino to XIRKA XA1 board based on Arm® 32-bit Cortex®-M3 CPU _ Bagas Budhi Permana

### Display 2.4 Inch TFT LCD Shield ILI9341 HX8347 240 * 320 Touch Board 65K RGB Color Display Module

##### 1. Instal 3 most important Libraries:
- Adafruit GFX Library-master = https://github.com/adafruit/Adafruit-GFX-Library   
- Adafruit TouchScreen-master = https://github.com/adafruit/Adafruit_TouchScreen
- MCUFRIEND_kbv-master        = https://github.com/prenticedavid/MCUFRIEND_kbv

##### 2. Extract the files and copy to yours Arduino Libary, mine in C:\Users\"Your PC"\Documents\Arduino\libraries 

##### 3. Open MCUFRIEND_kbv-master - find MCUFRIEND_kbv.cpp and open

##### 4. Edit Define Support ID
- there are many #define SUPPORT_XXXX lines, fine one that suit with your TFT LCD device ID
- mine is 0xD3D3 (look no.5) which the ID is 4532 so I just left #define SUPPORT_4532 and erased the rest
- save and close

##### 5 How to find the ID
- open Arduino 
- Connect your  Arduino ( mine is Mega 2560) with LCD TFT 2.4 MCUFRIEND
- open example and find an example in "MCUFRIEND_kbv", in this case I used "aspect_kbv" 
- compile and open serial monitor, it will show the HEX number. Ex. 0xD3D3 in mine, search this with keyword " 0xD3D3 TFT MCUFRIEND " and you will find the device ID (mine is 4532)
- after find the ID you could uncomment the "#define SUPPORT_XXXX" that same with your ID

##### 6 Run an Example from MCUFRIEND Library and there should be worked!

Have any question? fell free to email me: Bagaspermana88@gmail.com
