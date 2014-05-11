#include "mynotsominishell.h"

void restore_terminal()
{
  ioctl(0, TCSETA, (gl_env.line_backup));
  dup2(gl_env.stdio_backup, 1);
}
