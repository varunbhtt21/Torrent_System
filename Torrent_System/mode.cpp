#include "headers.h"

struct editorConfig {
  struct termios orig_termios;
};
struct editorConfig E;
void die(const char *s) {
  perror(s);
  exit(1);
};


void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
   if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = E.orig_termios;
  raw.c_lflag &= ~(ECHO |ICANON /*|ISIG*/ );
//  raw.c_cc[VMIN] = 0;
//  raw.c_cc[VTIME] = 100;
 if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");

}
