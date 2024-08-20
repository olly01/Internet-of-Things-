#include <Ticker.h>

#include <SSens.h>

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

int val;
#define SENSOR_PIN 12 // The pin that the sensor input is 
// connected to on your board
SSens sensor(SENSOR_PIN); // Create the sensor object

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  sensor.begin();
  
}

// the loop function runs over and over again forever
void loop() {
  
  
  
  if(sensor.getSignal() >5.0){
    val = 1;
     digitalWrite(LED_BUILTIN, HIGH);
  }
    else{
    val = 0;
    digitalWrite(LED_BUILTIN, LOW);
      }
      Serial.print(sensor.getSignal());
      Serial.print(" " );
      Serial.print(val);
      Serial.println();
      delay(100);
      
      
      
      
  //Serial.print(78);
  
 // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
 // Serial.print("Light on");
 // delay(3000);                       // wait for a second
  
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
 // Serial.print("Light off");
 // delay(3000); 
  
  

  
}
