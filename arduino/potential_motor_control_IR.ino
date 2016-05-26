/* Sumo drive testing */

/* Imports */
#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_EV3Infrared.h>

const int FULL_POWER = 100;
const int STEERING_FULL_POWER = 60;

/* Init Shield */
EVShield evshield(0x34, 0x36);

/* Init analog devices on shield */
EVs_EV3Infrared    sensorIR;

int direction = 2;                  // current direction, 
                                    // 2 is station, 3 is forward, 
                                    // 1 as backward

int32_t steeringDegrees;            // steering servo position in degrees 
                                    // works in a range of 140 degrees
                                    // wheels must be centered at setup
                                    
int32_t maxSteerLeft;               // max value for steering left
int32_t maxSteerRight;              // max value for steering right
int32_t centerSteer;                // center value of steering

int32_t static power = 0;                      // power settings for rear wheels, single for now

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
  
  Serial.println("Setup Done");
  Serial.println("set LEGO remote to specified channel and push buttons");
  for(int i = 0; i < 5; i++)
  {
    Serial.println(".");
    delay(1000);
  }
  Serial.println("Ensure front wheels are centered for steering init");
  evshield.bank_a.ledSetRGB(100,0,0);
  evshield.bank_b.ledSetRGB(100,0,0);
  Serial.println ("Press GO button to calibrate steering");
  evshield.waitForButtonPress(BTN_GO);
  
  maxSteerRight = setMaxRight();
  Serial.println("Max Right Steering Value: ");
  Serial.println(maxSteerRight);
  delay(1000);
  
  maxSteerLeft = setMaxLeft();
  Serial.println("Max Left Steering Value: ");
  Serial.println(maxSteerLeft);
  delay(1000);
  
  centerSteer = centerSteering(maxSteerLeft, maxSteerRight) - maxSteerRight;
  Serial.println("Center value: ");
  Serial.println(centerSteer);
  delay(500);
  Serial.println ("Press GO button to Start Car");
  evshield.waitForButtonPress(BTN_GO);
  
  evshield.bank_a.ledSetRGB(0,100,0);
  evshield.bank_b.ledSetRGB(0,100,0);  
}

void loop()
{
  int button;
  int channel = 1;
  button = sensorIR.readChannelButton(channel);
  
  steeringDegrees = getSteeringPosition();
  power = powerTurning(steeringDegrees);
  Serial.print("Power rating: ");
  Serial.println(power);
  driveForward(button, power);
  driveBackward(button, power);
  turnLeft(button);
  turnRight(button);
 
  Serial.print("Degrees: ");
  Serial.println(steeringDegrees);
}

void driveForward(int button, int32_t power)
{
  if(button == 1)
  {
    evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, power);
    evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, power);
  }
}

void driveBackward(int button, int power)
{
  if(button == 2)
  {
    evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, power);
    evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, power);
  }
}

//use getSteering() as method to calculate current position
int32_t powerTurning(int steeringValue)
{
  Serial.println("calculating power");
  if(steeringValue < (centerSteer + 10))
  {
    Serial.println("Turned Righ");
    return 100;
  }
  else
  {
    return 1;
  }
}

void turnLeft(int button)
{
  if(button == 3)
  {
    evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 100, 35, SH_Completion_Wait_For, SH_Next_Action_Float);
  }
}

void turnRight(int button)
{
  if(button == 4)
  {
    evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 100, 35, SH_Completion_Wait_For, SH_Next_Action_Float);
  }
}

int32_t getSteeringPosition()
{
  return evshield.bank_b.motorGetEncoderPosition(SH_Motor_2);
}

int32_t setMaxRight()
{
  evshield.bank_b.motorRunSeconds(SH_Motor_2, SH_Direction_Forward, 100, 5, SH_Completion_Wait_For, SH_Next_Action_Float);
  delay(5000);
  return evshield.bank_b.motorGetEncoderPosition(SH_Motor_2);
}

int32_t setMaxLeft()
{
  evshield.bank_b.motorRunSeconds(SH_Motor_2, SH_Direction_Reverse, 100, 5, SH_Completion_Wait_For, SH_Next_Action_Float);
  delay(5000);
  return evshield.bank_b.motorGetEncoderPosition(SH_Motor_2);
}

int32_t centerSteering(int32_t maxLeft, int32_t maxRight)
{
  int32_t center = (maxRight - maxLeft) / 2;
  evshield.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 100, center, SH_Completion_Wait_For, SH_Next_Action_Float);
  delay(5000);
  return center;
}
