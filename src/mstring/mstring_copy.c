#include "mstring.h"

char                    *mstring_copy(char      *str)
{
  int                   len = 0;
  char                  *copy = NULL;
  char                  *copy_ref;

  if (str == NULL)
    return (NULL);

  len = mstring_len(str);

  if ((copy = mmalloc(len + 1)) == NULL)
    return (NULL);

  copy_ref = copy;
  while (*str != '\0')
  {
    *copy = *str;
    copy++;
    str++;
  }
  *copy = '\0';

  return (copy_ref);
}
