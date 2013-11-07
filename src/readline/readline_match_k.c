#include "readline.h"

inline int              readline_match_k(s_dynamic_string       *dynstr,
                                         int                    *pos,
                                         char                   c)
{
  if (c == 11)
  {
    readline_clear_after(pos, dynstr);

    fflush(NULL);

    return (1);
  }

  return (0);
}
