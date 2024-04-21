#include <Servo.h>

Servo ESC1;     // create servo object to control the ESC
Servo ESC2;
Servo Wing1;
Servo Wing2 ;
#define step1Pin 2
#define dir1Pin 3
#define step2Pin 4
#define dir2Pin 5
unsigned long steps=0;
int customDelay, customDelayMapped;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  ESC1.attach(9,1000,2000); 
  ESC2.attach(10,1000,2000);// (pin, min pulse width, max pulse width in microseconds) 
  Wing1.attach(11,1000,2000);
  Wing2.attach(6,1000,2000);
    pinMode(step1Pin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
   pinMode(step2Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);

  

}

void loop(){
Wing1.write(90);
Wing2.write(90);
delay(6000);
Wing1.write(110);
Wing2.write(110);
delay(7000);
Wing1.write(90);
Wing2.write(90);
delay(7000);
Wing1.write(70);
Wing2.write(700);
delay(7000);
Wing1.write(90);
Wing2.write(90);
delay(5000); //repeat perhaps wing motions
ESC1.write(90);
ESC2.write(90);
delay(7000);
ESC1.write(100);
ESC2.write(100);
delay(7000);
ESC1.write(90);
ESC2.write(90);
delay(4000);
ESC1.write(80);
ESC2.write(80);
delay(7000);
ESC1.write(90);
ESC2.write(90);
delay(10000);

 speedControl();
  while( steps<(50000)){
	 // Makes pules with custom delay, depending on the Potentiometer, from which the speed of the motor depends
  digitalWrite(step1Pin, HIGH);
  delayMicroseconds(customDelayMapped);
  digitalWrite(step1Pin, LOW);
  delayMicroseconds(customDelayMapped);
  digitalWrite(dir1Pin, LOW);
  digitalWrite(step2Pin, HIGH);
  delayMicroseconds(customDelayMapped);
  digitalWrite(step2Pin, LOW);
  delayMicroseconds(customDelayMapped);   //ballast high is in low is out 
  digitalWrite(dir2Pin, LOW);
  steps=steps+1;
}
 while( steps>(1)){
	 // Makes pules with custom delay, depending on the Potentiometer, from which the speed of the motor depends
  digitalWrite(step1Pin, HIGH);
  delayMicroseconds(customDelayMapped);
  digitalWrite(step1Pin, LOW);
  delayMicroseconds(customDelayMapped);
  digitalWrite(dir1Pin, HIGH);
  digitalWrite(step2Pin, HIGH);
  delayMicroseconds(customDelayMapped);
  digitalWrite(step2Pin, LOW);
  delayMicroseconds(customDelayMapped);   //ballast high is in low is out 
  digitalWrite(dir2Pin, HIGH);
  steps=steps-1;
}
}
void speedControl() {
  customDelay = analogRead(A0);
  customDelay= 523; // Read the potentiometer value
  customDelayMapped = map(customDelay, 0, 1023, 1, 300); // Convert the analog input from 0 to 1024, to 300 to 3000
}
