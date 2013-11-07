#include "readline.h"

inline void             readline_clear_before(int               *pos,
                                              s_dynamic_string  *dynstr)
{
  int                   i = 0;

  for (i = 0; i < *pos; i++)
    printf("%c", 8);

  printf("%s", dynstr->str + *pos);

  for (i = 0; i < *pos; i++)
    printf(" ");

  for (i = 0; i < dynstr->len; i++)
    printf("%c", 8);

  for (i = 0; i < *pos; i++)
    dynamic_string_remove(dynstr, 0);

  *pos = 0;
}
