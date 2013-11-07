#include "mstring.h"

int                     mstring_len(char        *str)
{
  int                   res = 0;

  for (; *str != '\0'; str++)
    res++;

  return (res);
}
