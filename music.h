#ifndef MUSIC_H_
#define MUSIC_H_
#include "Arduino.h"
enum Note{
  C = 0,
  C_S,
  D,
  D_S,
  E,
  F,
  F_S,
  G,
  G_S,
  A,
  A_S,
  B
};
Note strToEnum(String note);
String enumToString(Note n);

#endif //MUSIC_H_