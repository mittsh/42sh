#include "mstring.h"

int                     mstring_atoi(char               *str)
{
  int                   res = 0;
  int                   puiss = 1;
  int                   len = 0;

  if (str == NULL)
    return (0);

  for (; str[len] != '\0'; len++)
  {
    if (str[len] < '0' || str[len] > '9')
      return (0);
  }

  for (len--; len >= 0; len--)
  {
    res += (str[len] - '0') * puiss;
    puiss *= 10;
  }

  return (res);
}
