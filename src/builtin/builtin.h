#ifndef BUILTIN_H_
# define BUILTIN_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <stdbool.h>
# include <string.h>
# include "history.h"

# include "../42sh/shell.h"
# include "history.h"
# include "../exec/exec.h"
# include "../parser/ast.h"
# include "../lexer/lexer.h"

/**
** @brief               Represent an opened streams for builtins IOs.
** @param in            Standard input file descriptor.
** @param out           Standard output file descriptor.
** @param err           Standard error file descriptor.
** @param fin           Standard input stream.
** @param out           Standard output stream.
** @param err           Standard error stream.
*/
typedef struct          builtin_fd
{
  int                   in;
  int                   out;
  int                   err;
  FILE                  *fin;
  FILE                  *fout;
  FILE                  *ferr;
}                       s_builtin_fd;

/**
** @brief               Builtin echo options.
** @param nflag         Is true when option n is activated.
** @param eflag         Is true when option e is activated.
** @param eeflag        Is true when option ee is activated.
*/
struct                  s_echo_opt
{
  bool                  nflag;
  bool                  eflag;
  bool                  eeflag;
  int                   dec;
};

/**
** @brief               Calls a builtin
** @param name          Builtin name.
** @param argv          Input arguments.
** @param int           Return status value.
** @param list_dup      File descriptors duplication list.
** @return              Returns true in case of calling success, false else.
*/
bool                    builtin_call(char                       *name,
                                     char                       **argv,
                                     int                        *status,
                                     s_list_dup                 *list_dup);

/**
** @brief               Builtin cd : changes current directory.
** @param argv          Input arguments.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_cd(char                         **argv,
                                   s_builtin_fd                 *builtin_fd);

/**
** @brief               Builtin alias : creates or changes an alias.
** @param argv          Input arguments.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_alias(char                      **argv,
                                      s_builtin_fd              *builtin_fd);

/**
** @brief               Builtin unalias : removes an alias.
** @param argv          Input arguments.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_unalias(char                    **argv,
                                        s_builtin_fd            *builtin_fd);

/**
** @brief               Builtin echo : prints input arguments on STDOUT.
** @param argv          Input arguments.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_echo(char                       **argv,
                                     s_builtin_fd               *builtin_fd);

/**
** @brief               Builtin clear : clears terminal.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_clear(s_builtin_fd              *builtin_fd);

/**
** @brief               Builtin exit : exits shell.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_exit(void);

/**
** @brief               Builtin vars : a 42sh new builtin,
**                      shows current variables.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_vars(s_builtin_fd               *builtin_fd);

/**
** @brief               Builtin history : shows current commands history.
** @param hist_q        History queue.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_history(s_queue_history         *hist_q,
                                        s_builtin_fd            *builtin_fd);

/**
** @brief               Builtin export : exports an environment variable.
** @param argv          Input arguments.
** @param builtin_fd    IO streams.
** @return              Returns the execution return value of builtin.
*/
int                     builtin_export(char                     **argv,
                                       s_builtin_fd             *builtin_fd);

#endif /* !BUILTIN_H_ */
