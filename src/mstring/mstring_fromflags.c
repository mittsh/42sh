#include "mstring.h"

char                    *mstring_fromflags(char *begin,
                                           char *end)
{
  int                   len = 0;
  char                  *str = NULL;
  char                  *res = NULL;
  char                  *res_ref = NULL;

  if (begin == NULL || end == NULL)
    return (NULL);

  for (str = begin; str != end; str++)
    len++;

  if ((res = mmalloc(len + 1)) == NULL)
    return (NULL);

  res_ref = res;
  for (str = begin; str != end; str++)
  {
    *res = *str;
    res++;
  }

  *res = '\0';

  return (res_ref);
}
