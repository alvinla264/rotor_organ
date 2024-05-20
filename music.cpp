
#include "music.h"

Note strToEnum(String note){
  if(note == "C") return C;
  else if(note == "C#") return C_S;
  else if(note == "D") return D;
  else if(note == "D#") return D_S;
  else if(note == "E") return E;
  else if(note == "F") return F;
  else if(note == "F#") return F_S;
  else if(note == "G") return G;
  else if(note == "G#") return G_S;
  else if(note == "A") return A;
  else if(note == "A#") return A_S;
  else if(note == "B") return B;
  else return C;
}

String enumToString(Note n){
  switch(n){
    case C:
      return "C";
    case C_S:
      return "C#";
    case D:
      return "D";
    case D_S:
      return "D#";
    case E:
      return "E";
    case F:
      return "F";
    case F_S:
      return "F#";
    case G:
      return "G";
    case G_S:
      return "G#";
    case A:
      return "A";
    case A_S:
      return "A#";
    case B:
      return "B";
    default:
      return "C";
  }
}