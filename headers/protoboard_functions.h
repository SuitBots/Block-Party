//
// protoboard_functions.h
//
// Copyright (c) 2013 Suit Bots FTC Team 4628
//

//
// In every program you must define the value of "numStages"
//

#include "drivers/hitechnic-protoboard.h"

void setVariables(int numStages) {
	//send the arduino the number of variables required for the program

}


void getValues(int numStages, int *EncoderChange, long BoardValue) {
	for (int i = 0; i < numStages; ++i) {
		// set array value to analog value from the protoboard
		EncoderChange[i] = BoardValue;

	}
}
