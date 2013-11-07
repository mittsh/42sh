#include "readline.h"

inline int              readline_match_escaped_51(int           *state,
                                                  char          c)
{
  if (*state == 2 && c == 51)
  {
    *state = 3;
    return (1);
  }

  return (0);
}
