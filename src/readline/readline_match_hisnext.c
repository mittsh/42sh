#include "readline.h"

inline int              readline_match_hisnext(int              *state,
                                               char             c,
                                               int              *pos,
                                               s_dynamic_string *dynstr)
{
  char                  *str = NULL;

  if ((*state == 2 && c == 'B') || c == 14)
  {
    history_next(g_shell->queue_history);
    str = history_current(g_shell->queue_history);

    readline_clear_after(pos, dynstr);
    readline_clear_before(pos, dynstr);

    printf("%s", str);
    dynamic_string_pushs(dynstr, str);

    *pos = strlen(str);

    fflush(NULL);

    *state = 0;

    return (1);
  }

  return (0);
}
