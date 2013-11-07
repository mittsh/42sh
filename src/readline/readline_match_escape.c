#include "readline.h"

inline int              readline_match_excape(int               *state,
                                              char              c)
{
  if (*state == 0 && c == 27)
  {
    *state = 1;
    return (1);
  }

  return (0);
}
