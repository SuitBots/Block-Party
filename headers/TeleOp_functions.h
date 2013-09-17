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

int J1X1()  { return joystick.joy1_x1; }       // These lines make pretty variables for the joysticks
int J1X2()  { return joystick.joy1_x2; }       // J is which logitech controller is being used
int J1Y1()  { return joystick.joy1_y1; }       // X or Y is the axis on which the compiler will read values
int J1Y2()  { return joystick.joy1_y2; }       // 1 or 2 is which joystick values will be read from
int J2X1()  { return joystick.joy2_x1; }
int J2X2()  { return joystick.joy2_x2; }
int J2Y1()  { return joystick.joy2_y1; }
int J2Y2()  { return joystick.joy2_y2; }

void tank_drive(tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 2) {
    writeDebugStream('Error: there must be exactly two motors for drive function');
    return;
  }
  DriveMotors[0] = J1Y1();
  DriveMotors[1] = J1Y2();
}

void arcade_drive(tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 2) {
    writeDebugStream('Error: there must be exactly two motors for drive function');
    return;
  }
  DriveMotors[0] = J1Y2() - J1X2();
  DriveMotors[1] = J1Y2() + J1X2();
}

// for an omniwheel drive train
void omni_drive(tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 4) {
    writeDebugStream('Error: there must be exactly four motors for drive function');
    return;
  }
  DriveMotors[0] = J1Y2() - J1X2() + J1X1();
  DriveMotors[1] = J1Y2() + J1X2() - J1X1();
  DriveMotors[2] = J1Y2() - J1X2() - J1X1();
  DriveMotors[3] = J1Y2() + J1X2() + J1X1();
}

int compassBearing() { return 0; } // TODO: figure out a rotation sensor

void omnimove_in_direction(int angle) {
  float xval = MAX_JOY_VAL * cos(angle);
  float yval = MAX_JOY_VAL * sin(angle);

  motor[DriveFR] = yval - xval + J1X1();
  motor[DriveFL] = yval + xval - J1X1();
  motor{DriveBL] = yval - xval - J1X1();
  motor{DriveBR] = yval + xval + J1X1();
}

void smart_omni_drive(tMotor *DriveMotors, size_t numMotors) {
  // smart means you can passivly rotate and go forward at the same time
  if (numMotors != 4) {
    writeDebugStream('Error: there must be exactly four motors for drive function');
    return;
  }
  int joystickAngle = atan(J1Y2() / J1X2());
  move_in_direction(joystickAngle - compassBearing());
}
