#include "readline.h"

inline void             readline_clear_after(int                *pos,
                                             s_dynamic_string   *dynstr)
{
  int                   i = 0;
  int                   oldlen = 0;

  oldlen = dynstr->len;

  for (i = *pos; i < oldlen; i++)
    printf(" ");

  for (i = *pos; i < oldlen; i++)
    printf("%c", 8);

  for (i = *pos; i < oldlen; i++)
    dynamic_string_remove(dynstr, *pos);
}
