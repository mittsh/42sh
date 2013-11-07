#include "mstring.h"

void                    mstring_print(char      *str)
{
  write(STDOUT_FILENO, str, mstring_len(str));
}
