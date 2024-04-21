#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include <Servo.h>
Servo ESCL;     // create servo object to control the ESC
Servo ESCR;
Servo WingR;  //creates the servo object for the control surfaces
Servo WingL ;
#define step1Pin 2   
#define dir1Pin 3
#define step2Pin 4
#define dir2Pin 5
unsigned long steps=0;  //steppermotor step counter
int ThrusterR=90;
int ThrusterL=90; 
int ServoR=90;
int ServoL=90;  //initialize the ints for the servos and thrusters
 //set all to starting pos 
int customDelay= 523; // Read the potentiometer value
int customDelayMapped = map(customDelay, 0, 1023, 1, 300); 

class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown	(uint8_t mod, uint8_t key);
    void OnKeyUp	(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
  Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
  Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
  Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");

  Serial.print(" >");
  PrintHex<uint8_t>(key, 0x80);
  Serial.print("< ");

  Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
  Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
  Serial.println((mod.bmRightGUI    == 1) ? "G" : " ");
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  Serial.print("DN ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  if (c)
    OnKeyPressed(c);
}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    Serial.println("LeftCtrl changed");
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    Serial.println("LeftShift changed");
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    Serial.println("LeftAlt changed");
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    Serial.println("LeftGUI changed");
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    Serial.println("RightCtrl changed");
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    Serial.println("RightShift changed");
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    Serial.println("RightAlt changed");
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    Serial.println("RightGUI changed");
  }

}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.print("UP ");
  Serial.println( ThrusterR);
  Serial.println( ThrusterL);
  Serial.println( ServoR);
  Serial.println( ServoL);
  PrintKey(mod, key);
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
  Serial.print("ASCII: ");
  Serial.println((char)key);
  switch ((char)key) {
  case 'q': //stop Thruster 1 key
    // do something when var equals 1
    ThrusterL=ThrusterR=90; // Adjust position by the 'change' amount
    ESCL.write(ThrusterL); 
    ESCR.write(ThrusterR);// Set the servo to the new position
    break;
  case 'i': //Reset Servos 1 pad key
    ServoL=ServoR=90; // Adjust position by the 'change' amount
    WingL.write(ServoL); 
    WingR.write(ServoR);// Set the servo to the new position
    break;
  case 'w': //Thrusters Forward w key
    ThrusterR += 5;
    ThrusterL=ThrusterR; // Adjust position by the 'change' amount
    ThrusterR = constrain(ThrusterR, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    ThrusterL = constrain(ThrusterR, 0, 180);
    ESCR.write(ThrusterR); // Set the servo to the new position
    ESCL.write(ThrusterL); // Set the servo to the new position
    break;
  case 's': //Thrusters Reverse s key
     ThrusterR -= 5;
    ThrusterL=ThrusterR; // Adjust position by the 'change' amount
    ThrusterR = constrain(ThrusterR, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    ThrusterL = constrain(ThrusterR, 0, 180);
    ESCR.write(ThrusterR); // Set the servo to the new position
    ESCL.write(ThrusterL); // Set the servo to the new position
    break;
  case 'a': //Left turn a key
    ThrusterR += 5;
    ThrusterL -= 5; // Adjust position by the 'change' amount
    ThrusterR = constrain(ThrusterR, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    ThrusterL = constrain(ThrusterL, 0, 180);
    ESCR.write(ThrusterR); // Set the servo to the new position
    ESCL.write(ThrusterL); // Set the servo to the new position
    // do something when var equals 1
    break;
  case 'd': //Right turn d key
    ThrusterR -= 5;
    ThrusterL += 5; // Adjust position by the 'change' amount
    ThrusterR = constrain(ThrusterR, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    ThrusterL = constrain(ThrusterL, 0, 180);
    ESCR.write(ThrusterR); // Set the servo to the new position
    ESCL.write(ThrusterL); // Set the servo to the new position
    // do something when var equals 2
    break;
  case 'u': //Wings Dive up arrow
    ServoR += 10;
    ServoL=ServoR; // Adjust position by the 'change' amount
    ServoR = constrain(ServoR, 0, 180);
    ServoL = constrain(ServoL, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    WingR.write(ServoR); // Set the servo to the new position
    WingL.write(ServoL);
    break;
  case 'j': //wings surface down arrow
    ServoR -= 10;
    ServoL=ServoR; // Adjust position by the 'change' amount
    ServoR = constrain(ServoR, 0, 180);
    ServoL = constrain(ServoL, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    WingR.write(ServoR); // Set the servo to the new position
    WingL.write(ServoL);
    // do something when var equals 2
    break;
  case 'h': // Bank left left arrow
    ServoR -= 10;
    ServoL += 10 ; // Adjust position by the 'change' amount
    ServoR = constrain(ServoR, 0, 180);
    ServoL = constrain(ServoL, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    WingR.write(ServoR); // Set the servo to the new position
    WingL.write(ServoL);
    // do something when var equals 1
    break;
  case 'k': //bank right right arrow
    ServoR += 10;
    ServoL -= 10 ; // Adjust position by the 'change' amount
    ServoR = constrain(ServoR, 0, 180);
    ServoL = constrain(ServoL, 0, 180); // Ensure the position stays within the servo's range (0 to 180 degrees)
    WingR.write(ServoR); // Set the servo to the new position
    WingL.write(ServoL);
    // do something when var equals 2
    break;
  case 'm': //empty ballast pg up
    for (int i = 0; i <= 5000; i++) {
	 // Makes pules with custom delay
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
    }
    break;
  case 'z': //fill ballast pg down
    for (int i = 0; i <= 5000; i++) {
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
    }
    break;
  default:
    // if nothing else matches, do the default
    // default is optional
    break;
};
}

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");
  ESCL.attach(9,1000,2000);  //connects the motors with attach
  ESCR.attach(10,1000,2000);// (pin, min pulse width, max pulse width in microseconds)  
  WingL.attach(11,1000,2000);
  WingR.attach(6,1000,2000);
  pinMode(step1Pin, OUTPUT); // selects output for our stepper motor pins
  pinMode(dir1Pin, OUTPUT);
  pinMode(step2Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);

  

if (Usb.Init() == -1)
  Serial.println("OSC did not start.");

  delay( 200 );

  HidKeyboard.SetReportParser(0, &Prs);
};

void loop()
{
  Usb.Task();
}

