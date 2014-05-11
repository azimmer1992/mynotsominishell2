#include "mynotsominishell.h"

void term_standout()
{
  tputs(gl_env.standout, 1, my_termprint);
}

void term_standend()
{
  tputs(gl_env.stand_end, 1, my_termprint);
}

int my_termprint(int n)
{
  return write(1, &n, 1);
}
