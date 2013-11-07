#include "mstring.h"

int                     mstring_compare(char    *str1,
                                        char    *str2)
{
  while (*str1 != '\0' && *str2 != '\0')
  {
    if (*str1 != *str2)
      break;

    str1++;
    str2++;
  }

  return (*str1 == *str2);
}
