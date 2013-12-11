#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     DriveFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     DriveFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     DriveBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     DriveBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               BadType)
#pragma config(Servo,  srvo_S1_C4_2,    hand,                 BadType)
#pragma config(Servo,  srvo_S1_C4_3,    hand2,                BadType)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               BadType)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               BadType)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               BadType)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messagesvalidateLongAddresvalidateLongAddresvalidateLongAddresvalidateLongAddress
#include "TeleOp_functions.h"

const tMotor DriveMotors[] = { DriveFL, DriveFR, DriveBL, DriveBR };
int handPos = 0;
int sideSelect = 3;

void initializeRobot() {
	servo[hand] = handPos;
	servo[hand2] = 180-ServoValue[hand];

}

task main()
{
	initializeRobot();
		waitForStart();
	while (true)
	{
		getJoystickSettings(joystick);

		omni_drive_left(DriveMotors);
		operate_flag_claw(flag);

		if(joy1Btn(03) == 1) {
			sideSelect = 3;
		}
		else if(joy1Btn(02) == 1) {
			sideSelect = 2;

		}
		else if(joy1Btn(00) == 1) {
			sideSelect = 0;
		}
		else if(joy1Btn(01) == 1) {
			sideSelect = 1;
		}

		if(sideSelect == 3) {
			omni_drive(DriveMotors);
		}
		else if(sideSelect == 2) {
			omni_drive_left(DriveMotors);
		}
		else if(sideSelect == 0) {
			omni_drive_right(DriveMotors);
		}
		else if(sideSelect == 1) {
			omni_drive_back(DriveMotors);
		}

	}
}
