//
// vector.h
//
// Copyright (c) 2013 Suit Bots 4628
//

#include "typedefs.h"

long magnitude(vect vector) {
  long mag;
  mag += vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
  mag = sqrt(mag);
  return mag;
}

int directionXY(vect vector) {
  int m = vector.y / vector.x;
  if (vect.x < 0)
    m = atan(m) + 180;
  else if (m == nan && vect.y > 0)
    m = 90;
  else if (m == nan && vect.y < 0)
    m = 270;
  else
    m = atan(m);
  return m;
}

int directionXZ(vect vector) {
  int m = vector.z / vector.x;
  if (vect.x < 0)
    m = atan(m) + 180;
  else if (m == nan && vect.z > 0)
    m = 90;
  else if (m == nan && vect.z < 0)
    m = 270;
  else
    m = atan(m);
  return m;
}

vect add(vect vect1, vect vect2) {
  vect vector = { vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z };
  return vector;
}

vect mult(long scalar, vect vector) {
  vect vector = { vector.x * scalar, vector.y * scalar, vector.z * scalar };
  return vector;
}

vect dot_prod(vect vect1, vect vect2) {
  vect vector = { vect1.x * vect2.x, vect1.y * vect2.y, vect1.z * vect2.z };
  return vector;
}

vect unit_vector(vect vector) {
  return mult(1/magnitude(vector), vector);
}

bool equivalent(vect vect1, vect vect2) {
  if (! magnitude(vect1) == magnitude(vect2))
    return false;
  if (! directionXY(vect1) == directionXY(vect2))
    return false;
  if (! directionXZ(vect1) == directionXZ(vect2))
    return false;
  return true;
}

void useless_val_warning(long useless_val) {
  write_debug_stream("WARNING: %ld has no meaning", useless_val);
}
