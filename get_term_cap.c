#include "mynotsominishell.h"

char *get_term_cap(char *cap)
{
  char *str;
  static char area[2048];
  if(!(str=(char *)tgetstr(cap, (char**)(&area))))
    {
      my_str("Error getting term cap\n");
      restore_terminal();
      exit(0);
    }
  return str;
}
