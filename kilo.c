#include "stdlib.h"
#include "termios.h"
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);//store current terminal attributes into global var orig_termios
  atexit(disableRawMode);//call disableRawMode when the program exits
  
  struct termios raw = orig_termios;//modify values of original terminal attributes
  raw.c_lflag &= ~(ECHO | ICANON);//(Turn off echoing and canonical mode)

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);//pass modified attributes to tcsetattr
}

int main() {
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');//read 1 byte from stdin until...
  return 0; 
}
