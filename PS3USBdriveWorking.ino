#include <PS3USB.h>
#include <Servo.h>
#include <SPI.h>


USB Usb;
PS3USB PS3(&Usb);

Servo servo1;  // Create servo object to control the first servo
Servo servo2;  // Create servo object to control the second servo
Servo esc1;
Servo esc2;

#define stepPin1 2
#define dirPin1 3
#define stepPin2 4
#define dirPin2 5

const int motorPin1 = 9;  // PWM pin connected to thruster 1
const int motorPin2 = 10;  // PWM pin connected to thruster 2

const int servoPin1 = 6;  // Pin for servo 1
const int servoPin2 = 11; // Pin for servo 2
int steps=0;
void setup() {
  Serial.begin(115200);
  Usb.Init();
  servo1.attach(servoPin1);  // attach the servos to their respective pins
  servo2.attach(servoPin2);
  esc1.attach(motorPin1);  // attach the servos to their respective pins
  esc2.attach(motorPin2);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

}

void loop() {
  Usb.Task();

  if (PS3.PS3Connected) {
    int thruster1Speed = map(PS3.getAnalogButton(L2), 0, 255, 90, 180); // Analog value from L2 for Thruster 1
    int thruster2Speed = map(PS3.getAnalogButton(R2), 0, 255, 90, 180); // Analog value from R2 for Thruster 2

    esc1.write(constrain(thruster1Speed, 0, 180));
    delay(15);
    esc2.write(constrain(thruster2Speed, 0, 180));

    
    

   
    delay(15);

    int servo1Position = map(PS3.getAnalogHat(LeftHatY), 0, 255, 0, 180);
    int servo2Position = map(PS3.getAnalogHat(RightHatY), 0, 255, 0, 180);
    servo1.write(constrain(servo1Position, 0, 180));
    delay(15);
    servo2.write(constrain(servo2Position, 0, 180));
    
    Serial.print(F("\tRightHatX: "));
    Serial.print(PS3.getAnalogHat(RightHatX));
    Serial.print(F("\tRightHatY: "));
    Serial.print(PS3.getAnalogHat(RightHatY));

    Serial.print(F("\r\nLeftHatX: "));
    Serial.print(PS3.getAnalogHat(LeftHatX));
    Serial.print(F("\tLeftHatY: "));
    Serial.print(PS3.getAnalogHat(LeftHatY));

    // Other controls and serial outputs as needed
    delay(15);

     if (PS3.getButtonClick(UP)) {
      digitalWrite(dirPin1, HIGH);
      performStep(stepPin1, 300); // Example delay, adjust as needed
    }
    if (PS3.getButtonClick(DOWN)) {
      digitalWrite(dirPin1, LOW);
      performStep(stepPin1, 300);
    }

    // Motor 2 controlled by TRIANGLE and CROSS
    if (PS3.getButtonClick(TRIANGLE)) {
      digitalWrite(dirPin2, HIGH);
      performStep(stepPin2, 300);
    }
    if (PS3.getButtonClick(CROSS)) {
      digitalWrite(dirPin2, LOW);
      performStep(stepPin2, 300);
    }
  }
}



void performStep(int stepPin, int stepDelay) {
  for (int thisPin = 0; thisPin < 10000; thisPin++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
    steps=1+steps;
}
 Serial.print(steps);
}
