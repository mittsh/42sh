#include "lexer.h"

char                    *lexer_match_arithmetic(char            *str)
{
  char                  *tmp = str;
  int                   ct = 0;

  if (*str != '$' || *(str + 1) != '(' || *(str + 2) != '(')
    return (str);

  for (tmp = str + 1; *tmp != '\0'; tmp++)
  {
    if (*tmp == '(')
      ct++;

    if (*tmp == ')')
    {
      ct--;
      if (ct < 0)
        return (str);
      if (ct == 0)
        return (tmp + 1);
    }
  }

  return (str);
}
