#include "readline.h"

inline int              readline_match_next(int                 *state,
                                            char                c,
                                            int                 *pos,
                                            s_dynamic_string    *dynstr)
{
  if ((*state == 2 && c == 'C') || c == 6)
  {
    if ((*pos) < dynstr->len)
    {
      printf("%c", dynstr->str[(*pos)]);
      *pos = (*pos) + 1;
    }
    *state = 0;

    fflush(NULL);

    return (1);
  }

  return (0);
}
