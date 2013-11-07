#include "readline.h"

inline int              readline_match_d(s_dynamic_string       *dynstr,
                                         int                    *pos,
                                         char                   c)
{
  unsigned int          i = 0;

  if (c == 4)
  {
    if (dynstr->len == 0)
      builtin_exit();

    if (*pos < dynstr->len)
    {
      dynamic_string_remove(dynstr, (*pos));

      printf("%s ", dynstr->str + (*pos));
      for (i = 0; i <= strlen(dynstr->str + (*pos)); i++)
        printf("%c", 8);

      fflush(NULL);
    }

    return (1);
  }

  return (0);
}
