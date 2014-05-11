#include "mynotsominishell.h"

void init_caps()
{
  char *term;
  term = getenv("TERM");
  if(!term)
    {
      my_str("Error initializing caps\n");
      restore_terminal();
      exit(0);
    }
  char bp[2048];
  tgetent(bp, term);
  gl_env.cut = (char *)xmalloc(2*sizeof(char));
  gl_env.cut[0] = CUT;
  gl_env.cut[1] = '\0';

  gl_env.paste = (char *)xmalloc(2*sizeof(char));
  gl_env.paste[0] = PASTE;
  gl_env.paste[1] = '\0';

  gl_env.movestart = (char *)xmalloc(2*sizeof(char));
  gl_env.movestart[0] = MOVESTART;
  gl_env.movestart[1] = '\0';

  gl_env.moveend = (char *)xmalloc(2*sizeof(char));
  gl_env.moveend[0] = MOVEEND;
  gl_env.moveend[1] = '\0';

  gl_env.clear = (char *)xmalloc(2*sizeof(char));
  gl_env.clear[0] = CLEAR;
  gl_env.clear[1] = '\0';

  gl_env.standout = get_term_cap(STANDOUT);
  gl_env.stand_end = get_term_cap(STAND_END);
  gl_env.left = get_term_cap(LEFT);
  gl_env.right = get_term_cap(RIGHT);
  gl_env.up = get_term_cap(UP);
  gl_env.down = get_term_cap(DOWN);
}
