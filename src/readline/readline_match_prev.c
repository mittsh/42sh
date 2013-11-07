#include "readline.h"

inline int              readline_match_prev(int                 *state,
                                            char                c,
                                            int                 *pos)
{
  if ((*state == 2 && c == 'D') || c == 2)
  {
    if ((*pos) > 0)
    {
      printf("%c", 8);
      *pos = (*pos) - 1;
    }
    *state = 0;

    fflush(NULL);

    return (1);
  }

  return (0);
}
