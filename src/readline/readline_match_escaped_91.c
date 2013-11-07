#include "readline.h"

inline int              readline_match_escaped_91(int           *state,
                                                  char          c)
{
  if (*state == 1 && c == 91)
  {
    *state = 2;
    return (1);
  }

  return (0);
}
