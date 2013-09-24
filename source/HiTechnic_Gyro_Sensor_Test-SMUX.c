#pragma config(Sensor, S1,     SMUX,              sensorAnalogInactive)


#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-gyro.h"


const tMUXSensor HTGYRO = msensor_S1_1;



task main () {

  eraseDisplay();
  while(true) {
      eraseDisplay();
      nxtDisplayTextLine(1, "Resetting");
      nxtDisplayTextLine(2, "offset");
      wait1Msec(500);

      // Start the calibration and display the offset
      nxtDisplayTextLine(2, "Offset: %f", HTGYROstartCal(GYRO));


    while(nNxtButtonPressed != kEnterButton) {
      eraseDisplay();

      nxtDisplayTextLine(1, "Reading");
      // Read the current calibration offset and display it
      nxtDisplayTextLine(2, "Offset: %4f", HTGYROreadCal(GYRO));

      nxtDisplayClearTextLine(4);
      // Read the current rotational speed and display it
      nxtDisplayTextLine(4, "Gyro:   %4f", HTGYROreadRot(GYRO));
      nxtDisplayTextLine(6, "Press enter");
      nxtDisplayTextLine(7, "to reset zero");
      wait1Msec(100);
    }
  }
}
