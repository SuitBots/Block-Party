//
// basic_functions.h
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

bool EncoderValReached(long MaxVal, tMotor motor) {
  int threshold = MaxVal + 100; //TODO: adjust constant
  if (nMotorEncoder[motor] >= MaxVal
      && nMotorEncoder[motor] < MaxVal + threshold) {
    return true;
  }
  return false;
}

void GoToEncoderVal(long EncoderVal, tMotor motor) {
  while (! EncoderValReached(motor, EncoderVal)) {
    motor[motor] = 100;
  }
  motor[motor] = 0;
  nMotorEncoder[motor] = 0;
}

const int FRICTION = 0; //TODO: adjust

void rotate(int degrees, tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 2) {
    writeDebugStream('Error: there must be exactly two motors for drive function');
    return;
  }
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

void move(int distanceCM, tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 2) {
    writeDebugStream('Error: there must be exactly two motors for drive function');
    return;
  }
  const float scale_factor = 0; //TODO: adjust
  long encoderVal = distanceCM * scale_factor * FRICTION;
  GoToEncoderVal(DriveMotors[0], encoderVal);
  GoToEncoderVal(DriveMotors[1], encoderVal);
}

void vect_move(vect vector, tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 2) {
    writeDebugStream('Error: there must be exactly two motors for drive function');
    return;
  }
  long mag2cm_scale = 0; //TODO: adjust
  rotate(*DriveMotors, directionXZ(vector), numMotors);
  move(*DriveMotors, mult(mag2cm_scale, magnitude(vector));
}

void omnimove(int distanceCM, tMotor *DriveMotors, size_t numMotors, direction_t direction) {
  if (numMotors != 4) {
    writeDebugStream('Error: there must be exactly four motors for drive function');
    return;
  }
  const float scale_factor = 0; //TODO: adjust
  long encoderVal = distanceCM * scale_factor * FRICTION;
  switch (direction) {
  case FORWARD:
    encoderVal *= -1;
  case BACKWARD:
    GoToEncoderVal(DriveMotors[0], -encoderVal);
    GoToEncoderVal(DriveMotors[1], -encoderVal);
    GoToEncoderVal(DriveMotors[2], -encoderVal);
    GoToEncoderVal(DriveMotors[3], -encoderVal);
    break;
  case LEFT:
    encoderVal *= -1;
  case RIGHT:
    GoToEncoderVal(DriveMotors[0], encoderVal);
    GoToEncoderVal(DriveMotors[1], -encoderVal);
    GoToEncoderVal(DriveMotors[2], -encoderVal);
    GoToEncoderVal(DriveMotors[3], encoderVal);
    break;
  }
}

void omnirotate(int degrees, tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 4) {
    writeDebugStream('Error: there must be exactly four motors for drive function');
    return;
  }
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

void srotate(int degrees, tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 2) {
    writeDebugStream('Error: there must be exactly two motors for drive function');
    return;
  }
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

void somnirotate(int degrees, tMotor *DriveMotors, size_t numMotors) {
  if (numMotors != 4) {
    writeDebugStream('Error: there must be exactly four motors for drive function');
    return;
  }
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
