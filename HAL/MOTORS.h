/*
 * MOTORS.h
 *
 * Created on: 24 Jul 2024
 * Author: Ahmed Saeed
 */

/*********************************************************************/
/* Description: Interface file for DC and Servo motor control        */
/* Version: 1.0 V                                                    */
/*********************************************************************/

#ifndef MOTORS_H_
#define MOTORS_H_

/*
 * Function to set the speed of a DC motor
 * Parameters:
 *   u8SpeedCpy (uint8): Speed level (e.g., 25%, 50%, 100%)
 */
void DC_MotorSetSpeed(uint8 u8SpeedCpy);

/*
 * Function to rotate DC motor clockwise
 * Parameters:
 *   u8LeftPinCpy (uint8): Left motor pin
 *   u8RightPinCpy (uint8): Right motor pin
 */
void DC_MotorRotateCW(uint8 u8LeftPinCpy, uint8 u8RightPinCpy);

/*
 * Function to rotate DC motor counter-clockwise
 * Parameters:
 *   u8LeftPinCpy (uint8): Left motor pin
 *   u8RightPinCpy (uint8): Right motor pin
 */
void DC_MotorRotateCCW(uint8 u8LeftPinCpy, uint8 u8RightPinCpy);

/*
 * Function to stop DC motor (apply brake)
 * Parameters:
 *   u8LeftPinCpy (uint8): Left motor pin
 *   u8RightPinCpy (uint8): Right motor pin
 */
void DC_MotorBreak(uint8 u8LeftPinCpy, uint8 u8RightPinCpy);

/*
 * Function to rotate a Servo motor at a specific angle
 * Parameters:
 *   u8DegreeCpy (uint8): Angle (0, 90, or 180 degrees)
 */
void Servo_MotorRotate(uint8 u8DegreeCpy);

/*
 * Function to rotate Servo motor from 0 to 180 degrees gradually
 */
void Servo_MotorRotate_0_TO_180(void);

/*
 * Function to rotate Servo motor from 180 to 0 degrees gradually
 */
void Servo_MotorRotate_180_To_0(void);

/*
 * Function to rotate Servo motor from 90 to 0 degrees gradually
 */
void Servo_MotorRotate_90_To_0(void);

/*
 * Function to rotate Servo motor from 0 to 90 degrees gradually
 */
void Servo_MotorRotate_0_TO_90(void);

#endif /* MOTORS_H_ */
