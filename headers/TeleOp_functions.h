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

#include "hitechnic-gyro.h"


void initializeRobot(tSensors gyro) {

}

int limitJoy(int joystick) {
	if (abs(joystick) < 20) {
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
		wait1Msec(10);
	}

	else if (joy2Btn(7)) {
		motor[FRM] = -100;
		wait1Msec(20);
	}

	else motor[FRM] = 0;
}

void operate_FRM_Slow(tMotor FRM) {
	if (joy2Btn(1)) {
		motor[FRM] = 10;
		wait1Msec(10);
	}
	else if (joy2Btn(3)) {
		motor[FRM] = -10;
		wait1Msec(10);
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

void operate_Spinny(tMotor spinny) {

	if (joy2Btn(6)) {
		motor[spinny] = 100;
		wait1Msec(1);
	}
	else if (joy2Btn(8)) {
		motor[spinny] = -100;
		wait1Msec(1);
	}
	else {
		motor[spinny] = 0;
	}
}

void operate_EG(tMotor EG) {

	if (abs(J2Y2()) > 10) {
		motor[EG] = J2Y2();
		wait1Msec(1);
	}
	else {
		motor[EG] = 0;
	}
}

//int getRotation(char sensorName) {
//	float rotSpeed = 0;
//	float heading = 0;

//	// Calibrate the gyro, make sure you hold the sensor still
//	HTGYROstartCal(sensorName);

//	// Reset the timer.
//	time1[T1] = 0;

//	while (true) {
//		// Wait until 20ms has passed
//		while (time1[T1] < 20)
//			wait1Msec(1);

//		// Reset the timer
//		time1[T1]=0;

//		// Read the current rotation speed
//		rotSpeed = HTGYROreadRot(sensorName);

//		// Calculate the new heading by adding the amount of degrees
//		// we've turned in the last 20ms
//		// If our current rate of rotation is 100 degrees/second,
//		// then we will have turned 100 * (20/1000) = 2 degrees since
//		// the last time we measured.
//		heading += rotSpeed * 0.02;

//		return heading;
//	}
//}


// for an omniwheel drive train
void omni_drive(tMotor *DriveMotors) {
	motor[DriveMotors[0]] = J1Y1() + (J1X1()/2) + J1X2();
	motor[DriveMotors[1]] = J1Y1() + (J1X1()/2) - J1X2();
	motor[DriveMotors[2]] = J1Y1() - (J1X1()/2) - J1X2();
	motor[DriveMotors[3]] = J1Y1() - (J1X1()/2) + J1X2();
}


void omni_drive_const(tMotor *DriveMotors, int constant) {

	int crab = (J1Y1()*constant);
	writeDebugStreamLine("joystickAngle: %i  ", crab);

	motor[DriveMotors[0]] = J1Y1() + (J1X1()/2) + J1X2();
	motor[DriveMotors[1]] = J1Y1() + (J1X1()/2) - J1X2() * 0.45;
	motor[DriveMotors[2]] = J1Y1() - (J1X1()/2) - J1X2();
	motor[DriveMotors[3]] = J1Y1() - (J1X1()/2) + J1X2() * 0.45;


}

//int rotation(char sensorName) {
//	int wantedRotSpeed = 0;
//	int realRotSpeed = 0;
//	int conversion = 0;

//	realRotSpeed = HTGYROreadRot(sensorName);

//	wantedRotSpeed = J1X2() * conversion;

//	int correction = wantedRotSpeed - realRotSpeed;

//	return (correction/conversion);
//}


//void omni_drive_gyro(tMotor *DriveMotors) {
//	motor[DriveMotors[0]] = J1Y1() + rotation() - J1X2();
//	motor[DriveMotors[1]] = J1Y1() + rotation() + J1X2();
//	motor[DriveMotors[2]] = J1Y1() - rotation() + J1X2();
//	motor[DriveMotors[3]] = J1Y1() - rotation() - J1X2();
//}


//static float compassBearing(long time, tSensors gyro) {
//	float rotSpeed = HTGYROreadRot(gyro);
//	static float heading = rotSpeed * time;
//	return heading;
//}

//void calibrate_heading() {
//	compassBearing() = 0;
//}

const int MAX_JOY_VAL = 255;

void omnimove_in_direction(int angle, tMotor *DriveMotors, int rotJoy) {

	float xval = MAX_JOY_VAL * sinDegrees(angle);
	float yval = MAX_JOY_VAL * cosDegrees(angle);

	motor[DriveMotors[0]] = yval + (rotJoy/2) - xval;
	motor[DriveMotors[1]] = yval + (rotJoy/2) + xval;
	motor[DriveMotors[2]] = yval - (rotJoy/2) + xval;
	motor[DriveMotors[3]] = yval - (rotJoy/2) - xval;
}

void smart_omni_drive(tMotor *DriveMotors, tSensors gyro) {
	// smart means you can passivly rotate and go forward at the same time
	int joystickAngle;
	int angle;

	//long time = time1[T1];

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

	//writeDebugStreamLine("joystickAngle: %i  compassBearing: %f", joystickAngle, compassBearing(time, gyro));
}
