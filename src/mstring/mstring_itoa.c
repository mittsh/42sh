#include "mstring.h"

char                    *mstring_itoa(int               n)
{
  char                  *res = NULL;

  res = mstring_itoa_base(n, 10);

  return (res);
}
