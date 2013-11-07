#include "mstring.h"

int                     mstring_haschar(char    *str,
                                        char    c)
{
  if (str == NULL)
    return (0);

  for (; *str != '\0'; str++)
    if (*str == c)
      return (1);

  return (0);
}
