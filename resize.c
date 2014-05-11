#include "mynotsominishell.h"

void resize()
{
  pid_t pid;
  char *arg[]={"clear", NULL};
  char *dir = (char *)xmalloc(BUF_SZ*sizeof(char));
  dir = getcwd(NULL, BUF_SZ-1);
  dir[BUF_SZ-1] = '\0';

  if((pid=fork())==0)
    {
      execvp(arg[0], arg);
      exit(0);
    }
  else
    {
      wait();
      my_str("minishell:");
      my_str(dir);
      my_char('$');
      my_str(gl_env.input_line);
    }
  free(dir);
  dir=NULL;
}
