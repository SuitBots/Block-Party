//
// TeleOp_functions.h
//
// Copyright (c) 2013 Suit Bots FTC Team 4628
//

//
// Please create an array like this one so the functions will work:
//
// tMotor DriveMotors[] = { DriveL, DriveR };
//
// or if you use Holonomic Drive:
//
// tMotor DriveMotors[] = { DriveFL, DriveFR, DriveBL, DriveBR };
//

#include "Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-gyro.h"


void initializeRobot(tSensors gyro) {
	HTGYROstartCal(gyro);
}

int limitJoy(int joystick) {
	if (abs(joystick) < 10) {
		return 0;
	} else return joystick;
}

int J1X1()  { return limitJoy(joystick.joy1_x1); }       // These lines make pretty variables for the joysticks
int J1X2()  { return limitJoy(joystick.joy1_x2); }       // J is which logitech controller is being used
int J1Y1()  { return limitJoy(joystick.joy1_y1); }       // X or Y is the axis on which the compiler will read values
int J1Y2()  { return limitJoy(joystick.joy1_y2); }       // 1 or 2 is which joystick values will be read from
int J2X1()  { return limitJoy(joystick.joy2_x1); }
int J2X2()  { return limitJoy(joystick.joy2_x2); }
int J2Y1()  { return limitJoy(joystick.joy2_y1); }
int J2Y2()  { return limitJoy(joystick.joy2_y2); }

void tank_drive(tMotor *DriveMotors) {
	motor[DriveMotors[0]] = J1Y1();
	motor[DriveMotors[1]] = J1Y2();
}

void arcade_drive(tMotor *DriveMotors, int size) {
	if (size == 2) {
		motor[DriveMotors[0]] = J1Y2() - J1X2();
		motor[DriveMotors[1]] = J1Y2() + J1X2();
	}
	if (size == 4) {
		motor[DriveMotors[0]] = J1Y2() - J1X2();
		motor[DriveMotors[1]] = J1Y2() + J1X2();
		motor[DriveMotors[3]] = J1Y2() - J1X2();
		motor[DriveMotors[4]] = J1Y2() + J1X2();
	}
}

void operate_FRM(tMotor FRM) {
	if (joy2Btn(5)) {
		motor[FRM] = 100;
		wait1Msec(1);
	}
	else if (joy2Btn(7)) {
		motor[FRM] = -100;
		wait1Msec(1);
	}
	else motor[FRM] = 0;
}

void operate_Lift(tMotor Lift) {
	if (abs(J2Y1()) > 0) {
		motor[Lift] = J2Y1();
		wait1Msec(1);
	}
	else {
		motor[Lift] = 0;
	}
}

void operate_Spinny(TServoIndex spinny) {

	if (joy2Btn(6)) {
		servo[spinny] = 0;
		wait1Msec(1);
	}
	else if (joy2Btn(8)) {
		servo[spinny] = 255;
		wait1Msec(1);
	}
	else {
		servo[spinny] = 127;
	}
}



// for an omniwheel drive train
void omni_drive(tMotor *DriveMotors) {
	motor[DriveMotors[0]] = J1Y1() - (J1X1()/2) - J1X2();
	motor[DriveMotors[1]] = J1Y1() - (J1X1()/2) + J1X2();
	motor[DriveMotors[2]] = J1Y1() + (J1X1()/2) + J1X2();
	motor[DriveMotors[3]] = J1Y1() + (J1X1()/2) - J1X2();
}

static float compassBearing(long time, tSensors gyro) {
	float rotSpeed = HTGYROreadRot(gyro);
	static float heading = rotSpeed * time;
	return heading;
}

//void calibrate_heading() {
//	compassBearing() = 0;
//}

const int MAX_JOY_VAL = 255;

void omnimove_in_direction(int angle, tMotor *DriveMotors, int rotJoy) {

	float xval = MAX_JOY_VAL * sinDegrees(angle);
	float yval = MAX_JOY_VAL * cosDegrees(angle);

	motor[DriveMotors[0]] = -yval + (rotJoy/2) - xval;
	motor[DriveMotors[1]] = -yval - (rotJoy/2) + xval;
	motor[DriveMotors[2]] = yval + (rotJoy/2) + xval;
	motor[DriveMotors[3]] = yval - (rotJoy/2) - xval;
}

void smart_omni_drive(tMotor *DriveMotors, tSensors gyro) {
	// smart means you can passivly rotate and go forward at the same time
	int joystickAngle;
	int angle;

	long time = time1[T1];

	if(abs(J1Y2()) > 20 || abs(J1X2()) > 20) {
		joystickAngle = radiansToDegrees(atan(J1Y2() / J1X2()));

		if (abs(J1X2()) > 20) {
			if(J1X2() > 0) {
				angle = -1 * (joystickAngle - 90);
			}
			else if(J1X2() < 0) {
				angle = -1 * (joystickAngle + 90);
			}
		}
		omnimove_in_direction(angle /*- compassBearing(time, gyro)*/, DriveMotors, J1X1());
	}


	else {
		motor[DriveMotors[0]] = 0;
		motor[DriveMotors[1]] = 0;
		motor[DriveMotors[2]] = 0;
		motor[DriveMotors[3]] = 0;
	}

	writeDebugStreamLine("joystickAngle: %i  compassBearing: %f", joystickAngle, compassBearing(time, gyro));
}
