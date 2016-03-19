/************************************************************************/
/*
  This application has been authored with the purpose of interfacing 
  microcontrollers such as an Arduino and Raspberry Pi 2 Model B to 
  control the outputs to the motors of a car - 
  -> Left Rear 9V DC Motor (Drive)
  -> Right Rear 9V DC Motor (Drive)
  -> Front Servo Motor (Steering)
  
  based on the inputs of the sensors - 
  
  ->
  ->
  ->
  
  --------- Ports -> Motors
  
  M1 (Left Rear) - Bank B - M1
  
  
  
*/  
/************************************************************************/

#include <Wire.h>
#include <EVShield.h>

#define GLOBAL_DELAY 50

EVShield          evshield(0x34,0x36);

void setup()
{
  Serial.begin(115200);            // begin serial communication for output (terminal)
  delay(1000);                     // wait 1 second for serial to begin
  
  char str[50];                    // string to output to serial (terminal)
  
  evshield.init( SH_HardwareI2C );
  /*
  Serial.println("Press Go Button to start test");
  evshield.waitForButtonPress(BTN_GO);
  */
  Serial.println("Button Pressed, Resetting Bank A and Bank B");
  
  evshield.bank_a.motorReset();    // reset bank A of motors
  evshield.bank_b.motorReset();    // reset bank B of motors
  
  delay(500);                      // wait for possible reset to settle
  
  evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 90, 180, SH_Completion_Dont_Wait, SH_Next_Action_Float); 
  
  delay(2000);
  
  evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 90, 180, SH_Completion_Dont_Wait, SH_Next_Action_Float); 
  /*
  delay(2000);
  
  evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 90, 180, SH_Completion_Wait_For, SH_Next_Action_Float); 
  
  delay(2000);
  
  evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 90, 180, SH_Completion_Wait_For, SH_Next_Action_Float);
  */
  
  Serial.println("Test Back Right Motor....");
  sprintf(str, "Motor Forward");
  Serial.println(str);
  str[0] = '\0';
  
  // test back left motor... evshield.bank_b m1 forward
  evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 100);
  evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 50);
  
  delay(500);
 
  
  /*
  Serial.println("Motor 1 will run until go is pressed again");
  evshield.waitForButtonPress(BTN_GO);
  evshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_BrakeHold);
  evshield.bank_a.motorStop(SH_Motor_1, SH_Next_Action_BrakeHold);
  */
}

void loop()
{
  multi_color_blink();
}

void multi_color_blink(){
 for (int i=8; i>=0; i--){
   if (i<=4) evshield.ledSetRGB(i,4-i,0);
   else    evshield.ledSetRGB(i,0,0);
   delay(GLOBAL_DELAY);
 }
 
 for (int i=5; i<=8; i++){
   evshield.ledSetRGB(0,i,0);
   delay(GLOBAL_DELAY/2);
 }

 for (int i=8; i>=0; i--){
   if (i<=4) evshield.ledSetRGB(0,i,4-i);
   else    evshield.ledSetRGB(0,i,0);
   delay(GLOBAL_DELAY);
 }

 for (int i=5; i<=8; i++){
   evshield.ledSetRGB(0,0,i);
   delay(GLOBAL_DELAY/2);
 }

 for (int i=8; i>=0; i--){
   if (i<=4) evshield.ledSetRGB(4-i,0,i);
   else    evshield.ledSetRGB(0,0,i);
   delay(GLOBAL_DELAY);
 }

 for (int i=5; i<=8; i++){
   evshield.ledSetRGB(i,0,0);
   delay(GLOBAL_DELAY/2);
 } 
}


