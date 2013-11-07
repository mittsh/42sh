#include "readline.h"

static inline int       readline_match_all(int                  *state,
                                           char                 c,
                                           int                  *pos,
                                           s_dynamic_string     *dynstr)
{
  int                   ok = 0;

  ok = 0;
  ok = ok || readline_match_excape(state, c);
  ok = ok || readline_match_escaped_91(state, c);
  ok = ok || readline_match_escaped_51(state, c);

  ok = ok || readline_match_prev(state, c, pos);
  ok = ok || readline_match_next(state, c, pos, dynstr);
  ok = ok || readline_match_hisprev(state, c, pos, dynstr);
  ok = ok || readline_match_hisnext(state, c, pos, dynstr);
  ok = ok || readline_match_del(dynstr, pos, c, state);

  return (ok);
}

bool                    readline_prompt(s_dynamic_string        *dynstr)
{
  int                   pos = 0;
  int                   state = 0;
  char                  c;
  int                   ok = 0;

  readline_print_ps1();

  while (read(STDIN_FILENO, &c, 1) > 0)
  {
    if (c == '\n')
      break;

    ok = readline_match_all(&state, c, &pos, dynstr);

    state = (!ok) ? 0 : state;

    if (readline_match_refresh(c))
      return (false);
    ok = ok || readline_match_bkspace(dynstr, &pos, c);
    ok = ok || readline_match_beginln(&pos, c);
    ok = ok || readline_match_endln(dynstr, &pos, c);
    ok = ok || readline_match_d(dynstr, &pos, c);
    ok = ok || readline_match_k(dynstr, &pos, c);

    if (!ok)
      readline_match_regular(dynstr, &pos, c);
  }

  write(STDOUT_FILENO, "\n", 1);

  return (true);
}
