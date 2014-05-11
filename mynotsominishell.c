#include "mynotsominishell.h"

int main()
{
  gl_env.pos = 0;
  gl_env.clipboard = (char *)xmalloc(BUF_SZ*sizeof(char));
  char *dir = (char *)xmalloc(BUF_SZ*sizeof(char));
  pid_t pid;
  char **vect;
  int n;
  char *buf;
  signal(SIGINT, restore_terminal);
  init_terminal();
  init_caps();
  signal(SIGWINCH, resize);
  while(1)
    {
      gl_env.input_line = (char *)xmalloc(BUF_SZ*sizeof(char));
      dir = getcwd(NULL, BUF_SZ-1);
      dir[BUF_SZ-1] = '\0';
      my_str("minishell:");
      my_str(dir);
      my_char('$');
      while(1)
	{
	  buf = (char *)xmalloc(4*sizeof(int));
	  n = read(0, buf, READMIN);
	  buf[n]='\0';
	  if(!my_strcmp(buf, gl_env.moveend))
	    {
	      gl_env.pos = my_strlen(gl_env.input_line)-1;
	    }
	  else if(!my_strcmp(buf, gl_env.movestart))
	    {
	      gl_env.pos = 0;
	    }
	  else if(!my_strcmp(buf, gl_env.cut))
	    {
	      for(n=0; n+gl_env.pos<my_strlen(gl_env.input_line); n++)
		{
		  gl_env.clipboard[n]=gl_env.input_line[n+gl_env.pos];
		  gl_env.input_line[n+gl_env.pos]='\0';
		}
	    }
	  else if(!my_strcmp(buf, gl_env.paste))
	    {
	      for(n=0; n<my_strlen(gl_env.clipboard); n++)
		gl_env.input_line[n+gl_env.pos]=gl_env.clipboard[n];
	    }
	  else if(!my_strcmp(buf, gl_env.clear))
	    {
	      resize();
	    }
	  else if(!my_strcmp(buf, "\n"))
	    {
	      gl_env.input_line[my_strlen(gl_env.input_line)] = '\0';
	      break;
	    }
	  else if(!my_strcmp(buf, gl_env.left))
	    {
	      if(gl_env.pos > 0)
		gl_env.pos--;
	    }
	  else if(!my_strcmp(buf, gl_env.right))
	    {
	      if(!(gl_env.pos >= my_strlen(gl_env.input_line)-1))
		gl_env.pos++;
	    }
	  else
	    {
	      gl_env.input_line[gl_env.pos] = buf[0];
	      gl_env.pos++;
	      my_char(buf[0]);
	    }
	  free(buf);
	  buf = NULL;
	}
      vect = my_str2vect(gl_env.input_line);
      if(!my_strcmp(vect[0],"cd"))
	chdir(vect[1]);
      else if(!my_strcmp(vect[0],"exit"))
	{
	  my_str("The NSA sends its regards.\n");
	  break;
	}
      else
	{
	  if((pid=fork())==0)
	    {
	      if(execvp(vect[0],vect)<0)
		{
		  my_str(vect[0]);
		  my_str(":This is an invalid command\n");
		  exit(0);
		}
	      exit(0);
	    }
	  else
	    wait();
	}
      free(gl_env.input_line);
      gl_env.input_line = NULL;
      for(n=0; vect[n]!='\0'; n++)
	{
	  free(vect[n]);
	  vect[n]=NULL;
	}
    }
  restore_terminal();
  return 0;
}
