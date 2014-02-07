#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     LEGOLIGHT,             sensorLightActive)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     DriveFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     DriveBL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     DriveFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     DriveBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     FRM,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     EG1,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     EG2,           tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    USServo,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    autoArm,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "TeleOp_functions.h"  // an H file that we wrote implementing various functions
#include "autonomous_functions.h"	// an H file that we wrote implementing various functions
#include "hitechnic-sensormux.h"
#include "lego-ultrasound.h"
#include "hitechnic-irseeker-v2.h"


const tMotor DriveMotors[] = { DriveFL, DriveBL, DriveFR, DriveBR };  //an array that describes the Drive motors
const int N_MOTORS = 4;

const tMUXSensor FRONTUS = msensor_S4_1;
//const tMUXSensor AFT_US = msensor_S4_2;
const tMUXSensor IR = msensor_S4_3;
//const tMUXSensor Gyro = msensor_S4_4;

int SERVO_DEGREES_FRONT = 0;

void  ZeroEncoders ()
{ for (int i = 0; i < N_MOTORS; ++i)
		nMotorEncoder[DriveMotors[i]] = 0;
}

int   EncoderTicks ()
{ int sum = 0;
	for (int i = 0; i < N_MOTORS; ++i)
		sum += abs(nMotorEncoder[DriveMotors[i]]);
	return sum;
}

int   IRSensorRegion () { return HTIRS2readACDir(IR); }

int ReturnLightVal () { return SensorValue[LEGOLIGHT]; }

int FrontUSDistance(int degrees) {
	int dist = 0;
	if(ServoValue[USServo] != degrees) {
		servo[USServo] = degrees;
		wait1Msec(1000);
	}
	dist = USreadDist(FRONTUS);
	return dist;
}

void Drive(int fl, int fr, int bl, int br) {
	motor[DriveFL] = fl;
	motor[DriveFR] = fr*0.8;
	motor[DriveBR] = br*0.8;
	motor[DriveBL] = bl;
}

void DriveForward (int speed) {
	Drive (speed, speed, speed, speed);
}

void DriveBackwards (int speed) {
	DriveForward (-speed);
}

void DriveLeft (int speed) {
	// We're weighted oddly. In order to make the thing
	// not crab, scale the rear wheels by this constant.
	const float magic = .50;
	Drive (-speed, speed, speed * magic, -speed * magic);
}

void DriveRight (int speed) {
	// We're weighted oddly. In order to make the thing
	// not crab, scale the rear wheels by this constant.
	const float magic = .45;
	Drive (speed, -speed * magic * 2.0, -speed * magic, speed * magic);
}

void Stop () {
	DriveForward (0);
}

void DriveForwardUntilTicksOrIR (const int ticks)
{
	while (EncoderTicks () < ticks &&	6 != IRSensorRegion ())
	{	DriveForward (25);
		wait10Msec (10);
	}
	Stop ();
}

void DriveForwardUntilTicks (const int ticks) {
	while (EncoderTicks () < ticks) {
		DriveForward (25);
		wait10Msec (10);
	}
	Stop ();
}

void DriveBackwardsUntilTicks (const int ticks) {
	while (EncoderTicks () < ticks) {
		DriveBackwards (25);
		wait10Msec (10);
	}
	Stop ();
}

void DriveLeftUntilTicks (const int ticks) {
	while (EncoderTicks () < ticks) {
		DriveLeft (100);
		wait10Msec (10);
	}
	Stop ();
}


void DriveForwardUntilTicksOrFrontUS(int ticks, int front) {
	while(EncoderTicks() < ticks && FrontUSDistance(SERVO_DEGREES_FRONT) > front) {
		DriveForward(25);
	}
	Stop();
}

void DriveLeftUntilTicksOrColor(int ticks) {
	while(EncoderTicks() < ticks && ReturnLightVal() < 35) {
		DriveLeft(100);
	}
	if(ReturnLightVal() < 35) {
		PlaySound(soundFastUpwardTones);
	}
	Stop();
}


void Dump () {
	//int initial = servo[autoArm];

	int dump = 0;
	int back = 255;
	servo[autoArm] = dump;
	wait10Msec(250);
	servo[autoArm] = back;
	wait10Msec(150);
}


void DumpCR () {
	//int initial = servo[autoArm];

	servo[autoArm] = 0;
	wait1Msec(1400);
	servo[autoArm] = 255;
	wait1Msec(1400);
	servo[autoArm] = 127;
	wait1Msec(10);
}


void initializeRobot() {
	ClearTimer (T1);
	//orientation = Heading ();
	servo[autoArm] = 127;
	servo[USServo] = SERVO_DEGREES_FRONT;
}

const int TICKS_PER_M = 16000;

void do_main()
{ // Dump ();

	ZeroEncoders ();

	int fwd_ticks = 1.7 * TICKS_PER_M;
	int final_fwd_ticks = 1.95 * TICKS_PER_M;
	int left_ticks = 1.5 * TICKS_PER_M;
	int back_ticks = 1.0 * TICKS_PER_M;

	DriveForwardUntilTicksOrIR (fwd_ticks);

	if(EncoderTicks() < 0.9 * TICKS_PER_M) {
		wait1Msec(100);
		DriveForwardUntilTicks(0.5 * TICKS_PER_M);
		DumpCR ();
	}

	else if(EncoderTicks() > 0.9 * TICKS_PER_M) {
		DriveForwardUntilTicksOrIR(fwd_ticks);
		DumpCR();
	}

	DriveForwardUntilTicks(fwd_ticks);
	DriveForwardUntilTicksOrFrontUS(final_fwd_ticks, 33);
	ZeroEncoders ();
	wait1Msec(500);
	DriveLeftUntilTicks(0.2 * TICKS_PER_M);
	ZeroEncoders();
	wait1Msec(500);
	DriveForwardUntilTicksOrFrontUS(0.2 * TICKS_PER_M, 29);
	ZeroEncoders();
	wait1Msec(500);
	DriveLeftUntilTicksOrColor(left_ticks);
	ZeroEncoders ( );
	wait1Msec(500);
	DriveBackwardsUntilTicks (back_ticks);

	wait10Msec(100);
}

void do_left_test () {
	ZeroEncoders ();
	DriveLeftUntilTicks (TICKS_PER_M);
}

void do_fwd_test () {
	ZeroEncoders ();
	DriveForwardUntilTicks (TICKS_PER_M);
	wait10Msec (100);
	ZeroEncoders ();
	DriveBackwardsUntilTicks (TICKS_PER_M);
}

task main () {
	initializeRobot ();
	//waitForStart();
	do_main ();
}
