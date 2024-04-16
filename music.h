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

float fundamental_freq[] = {16.35, 17.32, 18.35, 19.45, 20.6, 21.83, 23.12, 24.5, 25.96, 27.5, 29.14,30.87}; //C C# D D# E F F# G G# A A# B
Note strToEnum(String note);
String enumToString(Note n);

#endif //MUSIC_H_