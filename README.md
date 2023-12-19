# Arduino Badge reader 

Simple Badge Reader  🔐                                                                                                                                                                                          
Project realised with Dario, Victor and Matthias


work for Esp32 Microcontroller ✅                                      
using a RFID RC522  ✅

We are starting learning about arduino so the code is not the best one it's just basics functions.

# How to Use ⚡🏆
Just compile the code from arduino IDE or another one and enter the Wifi SSID  and the Wifi Password to connect to the API.                                                                                                                                    
To add a badge connect to the api on a web browser by this link : [http://badges-api.glitch.me/](http://badges-api.glitch.me/)  and add /add/UID (UID is the HEX of your badge.)               
To remove a badge connect to the api on a web browser by this link : [http://badges-api.glitch.me/](http://badges-api.glitch.me/)  and add /delete/UID.             




# Functions ⚡
+ **Serial.println**                      
    •Print a string on the console                                                                                                                                                                                                                             
  -*basic arduino function*                                            
                                            
+ **Serial.available**                  
    • Get a character from microcontroller.                                                                                                                                                                                                                    
    • This function returns the number of memories used.                                                                                                                                                                                                       
  -*basic arduino function*                     
                                            
+ **Serial.readStringUntil**                           
	• This function reads character from a serial buffer into a string.                                                                                                                                                                                    
  -*basic arduino function*                                                    
                                              
+ **validateCard**                         
    • This function send an http request get to the API with the RFID card UID to see if the badge is stored in the databse. The function return `true` and turn on a LED if the badge is stored in the database. Else the function return `false` and turn on another LED                                                                                                                                                                                                                                                    
  -*function created by us*
                                                                           
+ **getUID**                          
    • This function uses RFID-RC522 to get the UID from the badge currently reading. Convert it to an HEX string an return this string. After you can operate with this string to verify it, add it to the database or remove it etc...                        
  -*function created by us*
                                        

![image](https://github.com/trinioff/Arduino-badge-security-system/blob/main/badge%20reader.png)


▰▰▰▰▰▰▰▰▰▰▰▰▰▰ 100% Finish ❤️                          
            
