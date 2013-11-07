#include "readline.h"

inline int              readline_match_beginln(int              *pos,
                                               char             c)
{
  int                   i = 0;

  if (c == 1)
  {
    for (i = 0; i < *pos; i++)
      printf("%c", 8);

    fflush(NULL);

    *pos = 0;

    return (1);
  }

  return (0);
}
