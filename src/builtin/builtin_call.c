#include "builtin.h"

/**
** @brief               Gets builtin file descriptor from file descriptors
**                      duplication list.
** @param list_dup      Input file descriptors duplication list.
** @param builtin_fd    IOs streams.
** @return              void
*/
static inline void      builtin_get_fd(s_list_dup               *list_dup,
                                       s_builtin_fd             *builtin_fd)
{
  builtin_fd->in = STDIN_FILENO;
  builtin_fd->out = STDOUT_FILENO;
  builtin_fd->err = STDERR_FILENO;

  for (; list_dup != NULL; list_dup = list_dup->next)
  {
    if (list_dup->fd_out == STDIN_FILENO)
      builtin_fd->in = list_dup->fd_in;
    if (list_dup->fd_out == STDOUT_FILENO)
      builtin_fd->out = list_dup->fd_in;
    if (list_dup->fd_out == STDERR_FILENO)
      builtin_fd->err = list_dup->fd_in;
  }
}

/**
** @brief               Opens a file descriptor for builtin.
** @param builtin_fd    IOs streams.
** @return              void
*/
static inline void      builtin_open_fd(s_builtin_fd            *builtin_fd)
{
  int                   nin;
  int                   nout;
  int                   nerr;

  nin = dup(builtin_fd->in);
  nout = dup(builtin_fd->out);
  nerr = dup(builtin_fd->err);

  builtin_fd->fin = mfdopen(nin, "r");
  builtin_fd->fout = mfdopen(nout, "a");
  builtin_fd->ferr = mfdopen(nerr, "a");
}

/**
** @brief               Closes all builtin file descriptors.
** @param builtin_fd    IOs streams.
** @return              void
*/
static inline void      builtin_close_fd(s_builtin_fd           *builtin_fd)
{
  if (builtin_fd->fin != NULL)
    mfclose(builtin_fd->fin);
  if (builtin_fd->fout != NULL)
    mfclose(builtin_fd->fout);
  if (builtin_fd->ferr != NULL)
    mfclose(builtin_fd->ferr);
}

/**
** @brief               Depanding to the contexts, aliases or unalias
**                      a value.
*/
#define ALIAS_OR_UNALIAS()                              \
  if (strcmp(name, "alias") == 0)                       \
    *status = builtin_alias(argv, &builtin_fd);         \
                                                        \
  if (strcmp(name, "unalias") == 0)                     \
    *status = builtin_unalias(argv, &builtin_fd);

bool                    builtin_call(char                       *name,
                                     char                       **argv,
                                     int                        *status,
                                     s_list_dup                 *list_dup)
{
  s_builtin_fd          builtin_fd;

  *status = 256;

  builtin_get_fd(list_dup, &builtin_fd);
  builtin_open_fd(&builtin_fd);

  if (strcmp(name, "clear") == 0)
    *status = builtin_clear(&builtin_fd);

  if (strcmp(name, "exit") == 0)
    *status = builtin_exit();

  if (strcmp(name, "history") == 0)
    *status = builtin_history(g_shell->queue_history, &builtin_fd);

  if (strcmp(name, "cd") == 0)
    *status = builtin_cd(argv, &builtin_fd);

  if (strcmp(name, "echo") == 0)
    *status = builtin_echo(argv, &builtin_fd);

  ALIAS_OR_UNALIAS();

  if (strcmp(name, "vars") == 0)
    *status = builtin_vars(&builtin_fd);

  if (strcmp(name, "export") == 0)
    *status = builtin_export(argv, &builtin_fd);

  builtin_close_fd(&builtin_fd);

  if (*status == 256)
    return (false);
  else
    return (true);
}

