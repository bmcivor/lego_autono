/*
 * file EV3Shield defines the main interfaces that will be used for
 *      sensors and motors attached to the shield. This shield came
 *      with a library of software originally, however some faults
 *      were discovered with software quality with testing.
 *
 *      This is a modified version by Blake McIvor of the provided software
 *      authored by Nitin Patil in 2014. The original was provided with no
 *      guarantee or warranty on functionality.
*/

#ifndef EVShield_H
#define EVShield_H

#include "SHDefines.h"

/*
 * Motor control related constants. 
*/
#define SH_CONTROL_SPEED      0x01
#define SH_CONTROL_RAMP       0x02
#define SH_CONTROL_RELATIVE   0x04
#define SH_CONTROL_TACHO      0x08
#define SH_CONTROL_BRK        0x10
#define SH_CONTROL_ON         0x20
#define SH_CONTROL_TIME       0x40
#define SH_CONTROL_GO         0x80

#define SH_STATUS_SPEED       0x01
#define SH_STATUS_RAMP        0x02
#define SH_STATUS_MOVING      0x04
#define SH_STATUS_TACHO       0x08
#define SH_STATUS_BREAK       0x10
#define SH_STATUS_OVERLOAD    0x20
#define SH_STATUS_TIME        0x40
#define SH_STATUS_STALL       0x80

#define SH_COMMAND     0x41
#define SH_VOLTAGE     0x6E

#define SH_SETPT_M1     0x42
#define SH_SPEED_M1     0x46
#define SH_TIME_M1      0x47
#define SH_CMD_B_M1     0x48
#define SH_CMD_A_M1     0x49

#define SH_SETPT_M2     0x4A
#define SH_SPEED_M2     0x4E
#define SH_TIME_M2      0x4F
#define SH_CMD_B_M2     0x50
#define SH_CMD_A_M2     0x51

/*
 * Read registers.
 */
#define SH_POSITION_M1  0x52
#define SH_POSITION_M2  0x56
#define SH_STATUS_M1    0x5A
#define SH_STATUS_M2    0x5B
#define SH_TASKS_M1     0x5C
#define SH_TASKS_M2     0x5D

#define SH_ENCODER_PID  0x5E
#define SH_SPEED_PID  0x64
#define SH_PASS_COUNT  0x6A
#define SH_TOLERANCE  0x6B

#define SH_S1_MODE  0x6F
#define SH_S1_EV3_MODE  0x6F
#define SH_S1_ANALOG   0x70

#define SH_S2_MODE  0xA3
#define SH_S2_EV3_MODE  0x6F
#define SH_S2_ANALOG   0xA4

#define SH_BTN_PRESS     0xDA
#define SH_RGB_LED     0xD7
#define SH_CENTER_RGB_LED     0xDE

/* constants to be used by user programs */
/*
 * \enum SH_Motor Motor selection related constants
 */
typedef enum
{
    SH_Motor_1     = 0x01,   /*!< Choose Motor 1 for selected operation */
    SH_Motor_2     = 0x02,   /*!< Choose Motor 2 for selected operation  */
    SH_Motor_Both  = 0x03    /*!< Choose Both Motors for selected operation */
} SH_Motor;

/*
 * \enum SH_Next_Action Next action related constants
 */
typedef enum
{
    SH_Next_Action_Float  = 0x00,   /*!< stop and let the motor coast. */
    SH_Next_Action_Brake = 0x01,    /*!< apply brakes, and resist change to tachometer, but if tach position is forcibly changed, do not restore position */
    SH_Next_Action_BrakeHold = 0x02 /*!< apply brakes, and restore externally forced change to tachometer */
} SH_Next_Action;

/**
 * \enum SH_Direction Motor direction related constants.
 */
typedef enum
{
    SH_Direction_Reverse = 0x00,   /*!< Run motor in reverse direction */
    SH_Direction_Forward = 0x01    /*!< Run motor in forward direction */
} SH_Direction;

/*
 * \enum SH_Move Tachometer movement related constants
 */
typedef enum
{
    SH_Move_Absolute = 0x00,   /*!< Move the tach to absolute value provided */
    SH_Move_Relative = 0x01    /*!< Move the tach relative to previous position */
} SH_Move;

/*
 * \enum SH_Completion_Wait Whether to wait for motor to finish it's current task or not
 */
typedef enum
{
    SH_Completion_Dont_Wait    = 0x00,  /*!< Don't wait for motor to finish, program will continue with next function */
    SH_Completion_Wait_For     = 0x01   /*!< Wait for motor to finish, program will wait until current function finishes it's operation */
} SH_Completion_Wait;

/*
 * Speed constants, these are just convenience constants,
 * You can use any value between 0 and 100.
 */
#define SH_Speed_Full 90
#define SH_Speed_Medium 60
#define SH_Speed_Slow 25

/*
 * EVShield has two banks, and each of them has different I2C address.
 * each bank has 2 motors and 2 sensors.
 *
 */
/*!
 \def SH_Bank_A
	I2C address of bank A
 */
#define SH_Bank_A 0x34
/*!
 \def SH_Bank_B
	I2C address of bank B
 */
#define SH_Bank_B 0x36


/*
 *  Sensor type primitives
 *
 */

/*!
 \def SH_Type_NONE
	In this type the sensor port is not defined and used.
 */
#define SH_Type_NONE   0x00

#define SH_Type_SWITCH    0x01

/*!
 \def SH_Type_ANALOG
	In this type the sensor port is not powered (for sensors like touch sensor).
 */
#define SH_Type_ANALOG   0x02


/*!
 \def SH_Type_LIGHT_REFLECTED
	Used for detection of Refelected Light from Light sensors,
 */
#define SH_Type_LIGHT_REFLECTED      0x03
/*!
 \def SH_Type_LIGHT_AMBIENT
	Used for detection of ambient Light using the light sensors,
 */
#define SH_Type_LIGHT_AMBIENT      0x04
/*!
 \def SH_Type_I2C
	In this type the sensor connected should be an i2c device.
 */
#define SH_Type_I2C                 0x09

/*!
 \def SH_Type_COLORFULL
	In this type the sensor connected is NXT color sensor in color mode
 */
#define SH_Type_COLORFULL            13
/*!
 \def SH_Type_COLORRED
	In this type the sensor connected is NXT color sensor in RED color mode
 */
#define SH_Type_COLORRED             14
/*!
 \def SH_Type_COLORGREEN
	In this type the sensor connected is NXT color sensor in GREEN color mode
 */
#define SH_Type_COLORGREEN           15
/*!
 \def SH_Type_COLORBLUE
	In this type the sensor connected is NXT color sensor in BLUE color mode
 */
#define SH_Type_COLORBLUE            16
/*!
 \def SH_Type_COLORNONE
	In this type the sensor connected is NXT color sensor in ambient light mode
 */
#define SH_Type_COLORNONE            17
/*!
 \def SH_Type_EV3_SWITCH
	In this type the sensor connected is EV3 touch sensor
 */
#define SH_Type_EV3_SWITCH           18
/*!
 \def SH_Type_EV3
	In this type the sensor connected is EV3 UART sensor
 */
#define SH_Type_EV3                  19



/*
 * Sensor defines.
 */
/*!
 \def SH_S1
	This is used internally to address Sensor Port 1.
	Do not use this in sketches.
	Sketches should use SH_BankPort enums.
 */
#define SH_S1   1
/*!
 \def SH_S2
	This is used internally to address Sensor Port 2.
	Do not use this in sketches.
	Sketches should use SH_BankPort enums.
 */
#define SH_S2   2

#include "EVShieldI2C.h"
#if defined(__AVR__)
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
