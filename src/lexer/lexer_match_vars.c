#include "lexer.h"

char                    *lexer_match_vars(char                  *str)
{
  char                  *tmp = NULL;

  if (*str != '$' || *(str + 1) != '{')
    return (str);

  for (tmp = str; *tmp != '\0'; tmp++)
  {
    if (*tmp == '}')
      return (tmp + 1);
  }

  return (str);
}
