#include "readline.h"

inline int              readline_match_endln(s_dynamic_string   *dynstr,
                                             int                *pos,
                                             char               c)
{
  if (c == 5)
  {
    printf("%s", dynstr->str + *pos);

    fflush(NULL);

    *pos = dynstr->len;

    return (1);
  }

  return (0);
}
