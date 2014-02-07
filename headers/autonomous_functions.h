//
// autonomous_functions.h
//
// Copyright (c) 2013 Suit Bots FTC Team 4628
//

//
// Please create an array like this one so the drive functions will work
//
// tMotor DriveMotors[] = { DriveL, DriveR };
//
// or for Holonomic Drive:
//
// tMotor DriveMotors[] = { DriveFL, DriveFR, DriveBL, DriveBR };
//


#include "AdvancedSensors.c"

//#include "typedefs.h"
//#include "vector.h"

bool EncoderValReached(long MaxVal, tMotor motor) {
	if (MaxVal >= 0) {
		int threshold = MaxVal + 100; //TODO: adjust constant
		if (nMotorEncoder[motor] >= MaxVal
			&& nMotorEncoder[motor] < MaxVal + threshold) {
			return true;
		}
		return false;
	}
	else {
		int threshold = MaxVal - 100; //TODO: adjust constant
		if (nMotorEncoder[motor] <= MaxVal
			&& nMotorEncoder[motor] > MaxVal + threshold) {
			return true;
		}
		return false;
	}
}

void GoToEncoderVal(long EncoderVal, tMotor amotor) {
	while (! EncoderValReached(EncoderVal, amotor)) {
		motor[amotor] = 100;
	}
	motor[amotor] = 0;
	nMotorEncoder[amotor] = 0;
}

void GoToEncoderVal_omni(long EncoderVal,int angle, tMotor *DriveMotors) {
	float xval = MAX_JOY_VAL * cos(angle);
	float yval = MAX_JOY_VAL * sin(angle);

	while (! EncoderValReached(EncoderVal, DriveMotors[0])) {
		motor[DriveMotors[0]] = yval - xval + J1X1();
	}
	motor[DriveMotors[0]] = 0;
	nMotorEncoder[DriveMotors[0]] = 0;

	while (! EncoderValReached(EncoderVal, DriveMotors[1])) {
		motor[DriveMotors[1]] = yval + xval - J1X1();
	}
	motor[DriveMotors[1]] = 0;
	nMotorEncoder[DriveMotors[1]] = 0;

	while (! EncoderValReached(EncoderVal, DriveMotors[2])) {
		motor[DriveMotors[2]] = yval - xval - J1X1();
	}
	motor[DriveMotors[2]] = 0;
	nMotorEncoder[DriveMotors[2]] = 0;

	while (! EncoderValReached(EncoderVal, DriveMotors[3])) {
		motor[DriveMotors[3]] = yval + xval + J1X1();
	}
	motor[DriveMotors[3]] = 0;
	nMotorEncoder[DriveMotors[3]] = 0;
}

void omnimove_for_length_time(int timeMS, const tMotor *DriveMotors) {
	motor[DriveMotors[0]] = -30;
	motor[DriveMotors[1]] = -100;
	motor[DriveMotors[2]] = -30;
	motor[DriveMotors[3]] = -100;
	wait1Msec(timeMS);
	motor[DriveMotors[0]] = 0;
	motor[DriveMotors[1]] = 0;
	motor[DriveMotors[2]] = 0;
	motor[DriveMotors[3]] = 0;
}

const int FRICTION = 0; //TODO: adjust

void rotate(int degrees, tMotor *DriveMotors) {
	const float scale_factor = 0; //TODO: adjust
	long encoderVal = degrees * scale_factor * FRICTION;
	if (degrees >= 0) {
		GoToEncoderVal(DriveMotors[0], -encoderVal);
		GoToEncoderVal(DriveMotors[1], encoderVal);
	}
	else {
		GoToEncoderVal(DriveMotors[0], encoderVal);
		GoToEncoderVal(DriveMotors[1], -encoderVal);
	}
}

void move(int distanceCM, tMotor *DriveMotors) {
	const float scale_factor = 0; //TODO: adjust
	long encoderVal = distanceCM * scale_factor * FRICTION;
	GoToEncoderVal(DriveMotors[0], encoderVal);
	GoToEncoderVal(DriveMotors[1], encoderVal);
}

//void vector_move(vect vector, tMotor *DriveMotors) {
//  long Magnitude2CMScale = 0; //TODO: adjust
//  rotate(*DriveMotors, directionXZ(vector), numMotors);
//  move(*DriveMotors, mult(mag2cm_scale, magnitude(vector));
//}

//void omnimove(int distanceCM, direction_t direction, tMotor *DriveMotors) {
//	const float scale_factor = 0; //TODO: adjust
//	long encoderVal = distanceCM * scale_factor * FRICTION;
//	switch (direction) {
//	case FORWARD:
//		encoderVal *= -1;
//	case BACKWARD:
//		GoToEncoderVal(DriveMotors[0], -encoderVal);
//		GoToEncoderVal(DriveMotors[1], -encoderVal);
//		GoToEncoderVal(DriveMotors[2], -encoderVal);
//		GoToEncoderVal(DriveMotors[3], -encoderVal);
//		break;
//	case LEFT:
//		encoderVal *= -1;
//	case RIGHT:
//		GoToEncoderVal(DriveMotors[0], encoderVal);
//		GoToEncoderVal(DriveMotors[1], -encoderVal);
//		GoToEncoderVal(DriveMotors[2], -encoderVal);
//		GoToEncoderVal(DriveMotors[3], encoderVal);
//		break;
//	}
//}

void omnirotate(int degrees, tMotor *DriveMotors) {
	const float scale_factor = 0; //TODO: adjust
	long encoderVal = degrees * scale_factor * FRICTION;
	if (degrees >= 0) {
		GoToEncoderVal(DriveMotors[0], -encoderVal);
		GoToEncoderVal(DriveMotors[1], encoderVal);
		GoToEncoderVal(DriveMotors[2], -encoderVal);
		GoToEncoderVal(DriveMotors[3], encoderVal);
	}
	else {
		GoToEncoderVal(DriveMotors[0], encoderVal);
		GoToEncoderVal(DriveMotors[1], -encoderVal);
		GoToEncoderVal(DriveMotors[2], encoderVal);
		GoToEncoderVal(DriveMotors[3], -encoderVal);
	}
}

int compassBearing() { return 0; } // TODO: figure out a rotation sensor

// rotate in an "s"-like way. (What does this do?)
void srotate(int degrees, tMotor *DriveMotors) {
	if (degrees >= 0) {
		while (compassBearing() < degrees) {
			motor[DriveMotors[0]] = -degrees;
			motor[DriveMotors[1]] = degrees;
		}
	}
	else {
		while (compassBearing() > (360 + degrees)) {
			;
		}
	}
}

void somnirotate(int degrees, tMotor *DriveMotors) {
	int scale_factor;
	int encoderVal = degrees * scale_factor * FRICTION;
	if (degrees >= 0) {
		while (compassBearing() < degrees) {
			motor[DriveMotors[0]] = -encoderVal;
			motor[DriveMotors[1]] = encoderVal;
			motor[DriveMotors[2]] = -encoderVal;
			motor[DriveMotors[3]] = encoderVal;
		}
	}
	else {
		while (compassBearing() > (360 + degrees)) {
			motor[DriveMotors[0]] = encoderVal;
			motor[DriveMotors[1]] = -encoderVal;
			motor[DriveMotors[2]] = encoderVal;
			motor[DriveMotors[3]] = -encoderVal;
		}
	}
}
