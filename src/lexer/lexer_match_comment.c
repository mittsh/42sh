#include "lexer.h"

inline char             *lexer_match_comment(char               *str)
{
  char                  *tmp = str;

  if (*str != '#')
    return (str);

  for (tmp = str + 1; *tmp != '\0'; tmp++)
  {
    if (*tmp == '\n')
      return (tmp);
  }

  return (tmp);
}
