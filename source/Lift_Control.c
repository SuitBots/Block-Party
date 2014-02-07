#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     IR,             sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     DriveFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     DriveBL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     DriveFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     DriveBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     spinny,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     EG,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     FRM,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     Lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    autoArm,              tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    spinny,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)

task main()
{
	//
	// "Hi-jack" buttons for user program control.
	//
	nNxtButtonTask  = -2;   // Grab control of the buttons. '-3' is invalid for task, so no task will be
	// executed when a button is pressed.

	//
	// Note: program cannot be terminated if we hijack the 'exit' button. So there has to be an escape sequence
	//       that will return buttons to system control! We'll use a triple click
	//
	nNxtExitClicks  = 3; // Triple clicking EXIT button will terminate program
	//
	// Do nothing. Just keep waiting
	//
	while (true)
	{
		//
		// Some dummy code to do some work. In this case we'll simply display a count of the number of times
		// each button has been pressed.
		//
		string sTemp;
		TButtons nBtn;

		//
		// Update count of times each button is pushed. If using this program as a template, replace these
		// statements with your own custom action.
		//
		while (true) // wait for button press
		{
			nBtn = nNxtButtonPressed;
			if (nBtn != -1)
				break;
		}

		if(nBtn == 2) {
			motor[Lift] = -100;
			wait1Msec(10);
		}

		else if(nBtn == 1) {
			motor[Lift] = 100;
			wait1Msec(10);
		}

		else{
			motor[Lift] = 0;
			wait1Msec(10);
		}
	}
}
