//
// preprocessor_checks.h
//
// Copyright (c) Fletcher Porter 2013
//

// use this in your RobotC programs by placing the file in an include directory
// and writing this in your program:
// #include 'preprocessor_checks.h'

#ifndef ROBOTC
#error You need to compile this in RobotC
#endif

#ifndef NXT
#warning You do not currently have NXT mode active on your compiler
#endif

#ifndef TETRIX
#warning You do not currently have Tetrix mode active on your compiler
#endif

#ifndef FTC
#warning You do not currently have FTC mode active on your compiler
#endif

#if firmwareVersion < 0 // TODO: change 0 to latest firmware verison
#warning You do not currently have the latest firmware
#endif

#define PREPROCESSOR_CHECKS_EXECUTED
// You can use this to only run your program if the checks have gon through
// ex: 
// #ifdef preprocessor_checks_executed
// run_the_program();
// #else
// dont_run_the_program();
// #endif
