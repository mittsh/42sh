#include "readline.h"

inline int              readline_match_bkspace(s_dynamic_string *dynstr,
                                               int              *pos,
                                               char             c)
{
  unsigned int          i = 0;

  if (c == 127)
  {
    if (*pos > 0)
    {
      dynamic_string_remove(dynstr, (*pos) - 1);

      printf("%c%s ", 8, dynstr->str + (*pos) - 1);
      for (i = 0; i <= strlen(dynstr->str + (*pos) - 1); i++)
        printf("%c", 8);

      fflush(NULL);

      *pos = (*pos) - 1;
    }

    return (1);
  }

  return (0);
}
