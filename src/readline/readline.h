#ifndef READLINE_H_
# define READLINE_H_

# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdarg.h>
# include <strings.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <time.h>
# include <pwd.h>

# include "../dynamic_string/dynamic_string.h"
# include "../builtin/builtin.h"
# include "../42sh/shell.h"
# include "../builtin/history.h"
# include "ps1/ps1.h"

typedef struct          s_cursor
{
  unsigned int          x;
  unsigned int          y;
}                       s_cursor;

void                    readline_interactive(int                is_print_ast);

bool                    readline_prompt(s_dynamic_string        *dynstr);

void                    readline_clear_after(int                *pos,
                                             s_dynamic_string   *dynstr);

void                    readline_clear_before(int               *pos,
                                              s_dynamic_string  *dynstr);

int                     readline_match_refresh(char             c);

int                     readline_match_next(int                 *state,
                                            char                c,
                                            int                 *pos,
                                            s_dynamic_string    *dynstr);

int                     readline_match_prev(int                 *state,
                                            char                c,
                                            int                 *pos);

int                     readline_match_hisnext(int              *state,
                                               char             c,
                                               int              *pos,
                                               s_dynamic_string *dynstr);

int                     readline_match_hisprev(int              *state,
                                               char             c,
                                               int              *pos,
                                               s_dynamic_string *dynstr);

int                     readline_match_escaped_51(int           *state,
                                                  char          c);

int                     readline_match_escaped_91(int           *state,
                                                  char          c);

int                     readline_match_excape(int               *state,
                                              char              c);

int                     readline_match_del(s_dynamic_string     *dynstr,
                                           int                  *pos,
                                           char                 c,
                                           int                  *state);

int                     readline_match_bkspace(s_dynamic_string *dynstr,
                                               int              *pos,
                                               char             c);
int                     readline_match_beginln(int              *pos,
                                               char             c);

int                     readline_match_endln(s_dynamic_string   *dynstr,
                                             int                *pos,
                                             char               c);

int                     readline_match_d(s_dynamic_string       *dynstr,
                                         int                    *pos,
                                         char                   c);

int                     readline_match_k(s_dynamic_string       *dynstr,
                                         int                    *pos,
                                         char                   c);

void                    readline_match_regular(s_dynamic_string *dynstr,
                                               int              *pos,
                                               char             c);

void                    readline_print_ps1(void);

#endif /* !READLINE_H_ */
