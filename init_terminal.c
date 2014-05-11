#include "mynotsominishell.h"

void init_terminal()
{
  int fd;
  char *name;
  struct termio line;
  name = ttyname(0);
  fd = open(name, O_WRONLY);
  gl_env.stdio_backup = dup(1);
  dup2(fd, 1);
  ioctl(0, TCGETA, &line);
  gl_env.line_backup=line;
  line.c_cc[VMIN]=READMIN;
  line.c_cc[VTIME]=READTIME;
  line.c_lflag&=~(ICANON|ECHO|ISIG);
  ioctl(0, TCSETA, &line);
}
