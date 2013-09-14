//
// typedefs.h
//
// Copyright (c) 2013 Suit Bots 4628
//

typedef enum { FORWARD, BACKWARD, LEFT, RIGHT } direction_t;

typedef struct {
  long x;
  long y;
  long z;
} vect;

typedef enum { L_OUT, L_IN, R_IN, R_OUT } crate_t;
