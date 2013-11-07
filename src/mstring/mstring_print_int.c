#include "mstring.h"

void                    mstring_print_int(int           i)
{
  mstring_print(mstring_itoa(i));
}
