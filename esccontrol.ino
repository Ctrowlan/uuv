/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>
Servo Ser1; 
Servo ESC1;     // create servo object to control the ESC
Servo ESC2; 
int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Ser1.attach(11,1000,2000);
  ESC1.attach(9,1000,2000); 
  ESC2.attach(10,1000,2000);// (pin, min pulse width, max pulse width in microseconds) 
}

void loop() {
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = 90;   // scale it to use it with the servo library (value between 0 and 180)
  delay(5000);
  ESC1.write(potValue); 
  ESC2.write(potValue);
  delay(4000);   // Send the signal to the ESC
   ESC1.write(110);
   
   ESC2.write(110);
   delay(6000);
   ESC1.write(potValue); 
  ESC2.write(potValue);
  delay(4000);
   ESC1.write(80);
   ESC2.write(80);
   delay(6000);
   ESC1.write(potValue); 
  ESC2.write(potValue);
  delay(30000);
   

  // Wait for a bit to avoid spamming the Serial Monitor
}