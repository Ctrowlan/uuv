
 
// defines pins
#define step1Pin 2
#define dir1Pin 3
#define step2Pin 4
#define dir2Pin 5




int customDelay, customDelayMapped;
unsigned long steps=0;
int rot=2000;
void setup() {
  // Sets the two pins as Outputs
  pinMode(step1Pin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
   pinMode(step2Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);
}
void loop() {
   speedControl();
  while( steps<(10000)){
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
  steps=steps+1;

}

 
}
// Custom function for reading the potentiometer and mapping its value from 300 to 3000, suitable for the custom delay value in microseconds
void speedControl() {
  customDelay = analogRead(A0);
  customDelay= 523; // Read the potentiometer value
  customDelayMapped = map(customDelay, 0, 1023, 1, 300); // Convert the analog input from 0 to 1024, to 300 to 3000
}