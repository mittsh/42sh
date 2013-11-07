#include "readline.h"

void                    readline_match_regular(s_dynamic_string *dynstr,
                                               int              *pos,
                                               char             c)
{
  unsigned int          i = 0;
  char                  *termtype;
  static char           term_buffer[2048];

  termtype = getenv("TERM");
  if (termtype == 0)
    exit(1);
  tgetent(term_buffer, termtype);

  if (c == '\t')
    return;

  dynamic_string_insert(dynstr, c, *pos);
  history_update(g_shell->queue_history, dynstr->str);

  printf("%s", dynstr->str + (*pos));
  for (i = 0; i < strlen(dynstr->str + (*pos)); i++)
    printf("%c", 8);

  printf("%c", c);

  if (((dynstr->len + 7) % tgetnum("co")) == 0)
    printf("\n");

  fflush(stdout);

  *pos = (*pos) + 1;
}
