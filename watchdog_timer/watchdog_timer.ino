#include <avr/wdt.h>

void setup(){
  Serial.begin(9600);
  Serial.println("Setup started :");
  // make a delay before enable WDT 
  // this delay help to complete all initial tasks
  delay(2000);
  wdt_enable(WDTO_4S);
}

void loop(){
  Serial.println("LOOP started ! ");
  for(int i=0; i<=5; i++){
    Serial.print("Loop : ");
    Serial.print(i);
    Serial.println();
    delay(1000);
    wdt_reset();
  }
  //infinity loop to hang MCU
  while(1){}
}
