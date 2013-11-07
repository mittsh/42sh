#include "readline.h"

inline int              readline_match_del(s_dynamic_string     *dynstr,
                                           int                  *pos,
                                           char                 c,
                                           int                  *state)
{
  unsigned int          i = 0;

  if ((*state) == 3 && c == 126)
  {
    if (*pos < dynstr->len)
    {
      dynamic_string_remove(dynstr, (*pos));

      printf("%s ", dynstr->str + (*pos));
      for (i = 0; i <= strlen(dynstr->str + (*pos)); i++)
        printf("%c", 8);

      fflush(NULL);
    }

    *state = 0;

    return (1);
  }

  return (0);
}
