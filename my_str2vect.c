#include "../lib/my.h"

/*Precondition: takes a string as input
 *Postcondition: returns a vector as output
 */

char **my_str2vect(char *str)
{
  int max = my_strlen(str);
  int numarg=0;
  int strstart, i;
  int pos=0;
  char **str2vect;

  for(; str[pos]!='\0'; pos++)
    if(str[pos]==' ')
      {
	numarg++;
	while(str[pos]!='\0' && str[pos]==' ')
	  pos++;
      }
  numarg++;

  str2vect = (char **)xmalloc((1+numarg)*sizeof(char *));
  str2vect[numarg]='\0';
  numarg=0;

  for(pos=0; str[pos]!='\0' && pos < max; pos++)
    if(str[pos]!=' ')
      {
	strstart=pos;
	while(str[pos]!='\0' && str[pos]!=' ')
	  pos++;
	str2vect[numarg] = (char *)xmalloc((1+pos-strstart)*sizeof(char));

	for(i=0; strstart<pos; strstart++, i++)
	  str2vect[numarg][i] = str[strstart];
	str2vect[numarg][i] = '\0';
	numarg++;
      }
      
  return str2vect;
}
