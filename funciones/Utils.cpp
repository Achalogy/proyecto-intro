#include "Utils.h"

int convertirAEntero(char str)
{
  return (
      (str == 'A') || (str == 'a') || (str == '1') ? 1 : (str == 'B') || (str == 'b') || (str == '2') ? 2
                                                     : (str == 'C') || (str == 'c') || (str == '3')   ? 3
                                                     : (str == 'D') || (str == 'd') || (str == '4')   ? 4
                                                     : (str == 'E') || (str == 'e') || (str == '5')   ? 5
                                                     : (str == 'F') || (str == 'f') || (str == '6')   ? 6
                                                     : (str == 'G') || (str == 'g') || (str == '7')   ? 7
                                                     : (str == 'H') || (str == 'h') || (str == '8')   ? 8
                                                                                                      : 0);
}

char convertirAChar(int x)
{
  return (
      (x == 1) ? 'A' : (x == 2) ? 'B'
                   : (x == 3)   ? 'C'
                   : (x == 4)   ? 'D'
                   : (x == 5)   ? 'E'
                   : (x == 6)   ? 'F'
                   : (x == 7)   ? 'G'
                   : (x == 8)   ? 'H'
                                : ' ');
}