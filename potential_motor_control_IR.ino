/* Sumo drive testing */

/* Imports */
#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_EV3Infrared.h>

/* Init Shield */
EVShield evshield(0x34, 0x36);

/* Init analog devices on shield */
EVs_EV3Infrared    sensorIR;

int direction = 2;                // current direction, 
                                    // 2 is station, 3 is forward, 
                                    // 1 as backward

void setup()
{
  Serial.begin(115200);             // 115200 baud rate
  delay(1000);                      // delay one second
  Serial.flush();
  delay(1000);
  char str[80];                     // string to output to serial

  evshield.init( SH_HardwareI2C );  // I2C init
  
  Serial.println ("---------------------------");
  Serial.println ("Starting Drive Test Program");
  Serial.println ("---------------------------");
  delay(1000);
  
  /*
   * initialize IR and assign ports
  */
  sensorIR.init( &evshield, SH_BAS1 );
  sensorIR.setMode(MODE_Infrared_Remote);
  
  evshield.bank_a.motorReset();
  evshield.bank_b.motorReset();
  
  Serial.println("setup done");
  Serial.println("set LEGO remote to specified channel and push buttons");
  Serial.println ("Press GO button to continue");
  evshield.bank_a.ledSetRGB(100,0,0);
  evshield.bank_b.ledSetRGB(100,0,0);
  evshield.waitForButtonPress(BTN_GO);
  evshield.bank_a.ledSetRGB(0,0,100);
  evshield.bank_b.ledSetRGB(0,0,100);  
}

void loop()
{
  int button;
  int channel = 1;
  button = sensorIR.readChannelButton(channel);
  
  driveForward(button);
  driveBackward(button);
  turnLeft(button);
  turnRight(button);
  
  Serial.print("Button: ");
  Serial.println(button);
}

void driveForward(int button)
{
  if(button == 1)
  {
    Serial.print("Drive Forward");
    evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 100);
    evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 100);
  }
}

void driveBackward(int button)
{
  if(button == 2)
  {
    Serial.print("Drive Backward");
    evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, 100);
    evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, 100);
  }
}

void turnLeft(int button)
{
  if(button == 3)
  {
    Serial.print("Drive Left");
    evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 100, 35, SH_Completion_Wait_For, SH_Next_Action_Float);
  }
}

void turnRight(int button)
{
  if(button == 4)
  {
    Serial.print("Drive Right");
    evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 100, 35, SH_Completion_Wait_For, SH_Next_Action_Float);
  }
}


