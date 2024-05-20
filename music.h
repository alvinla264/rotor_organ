/*
Title: music.cpp
Author: Alvin La
Date: 05/20/2024
Description: This file contains the Note enum as well as functions to convert enum to string and vice versa
*/
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