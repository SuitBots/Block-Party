#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     DriveL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     DriveR,            tmotorTetrix, openLoop, reversed, encoder)

#include "TeleOp_functions.h"

const tMotor DriveMotors[] = { DriveL, DriveR };

task main() {
  waitForStart();
  while (true) {
    arcade_drive(DriveMotors[], 2);
    getJoystickSettings(joystick);
  }
}
