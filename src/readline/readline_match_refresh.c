#include "readline.h"

inline int              readline_match_refresh(char             c)
{
  if (c == 12)
  {
    printf("%c[H%c[J", 27, 27);
    fflush(NULL);
    return (1);
  }

  return (0);
}
