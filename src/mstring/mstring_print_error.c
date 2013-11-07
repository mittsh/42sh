#include "mstring.h"

void                    mstring_print_error(char        *str)
{
  write(STDERR_FILENO, str, mstring_len(str));
}
