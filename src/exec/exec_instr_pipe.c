#include "exec.h"

/**
** @brief               Sets an error value and returns result.
*/
#define CHECK_ERROR()                                   \
  if (*error != ERROR_NONE)                             \
    return (res);

/**
** @brief               Frees duplication lists and sets pointers to null.
** @param dp            List one
** @param dp2           List two
** @return              void
*/
static void             free_and_null(s_list_dup                **dp,
                                      s_list_dup                **dp2)
{
  mfree(*dp);
  mfree(*dp2);
  *dp = NULL;
  *dp2 = NULL;
}

/**
** @brief               Closes all file descriptors opened by call.
** @param fd_in         Input filedes.
** @param filedes       File descriptor list.
** @param ptr           Check to NULL pointer.
** @return              void
*/
static void             close_fds(int                           *fd_in,
                                  int                           *filedes,
                                  void                          *ptr)
{
  if (*fd_in != STDIN_FILENO)
    mclose(*fd_in);
  if (ptr != NULL)
    mclose(filedes[1]);
  *fd_in = filedes[0];
}

int                     exec_instr_pipe(s_instr                 *instr,
                                        s_list_dup              *list_dup,
                                        int                     *error)
{
  s_instr_pipe          *instr_pipe = NULL;
  int                   filedes[2];
  int                   res = 0;
  s_list_dup            *dp = NULL;
  s_list_dup            *dp2 = NULL;
  s_list_instr_item     *list_instr = NULL;
  int                   fd_in = STDIN_FILENO;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_pipe = instr->instr;

  list_instr = instr_pipe->list_instr->first;
  for (; list_instr != NULL; list_instr = list_instr->next)
  {
    if (list_instr->next != NULL)
      mpipe(filedes);
    if (list_instr->next != NULL)
      dp = list_dup_insert(list_dup, filedes[1], STDOUT_FILENO);

    if (list_instr != instr_pipe->list_instr->first)
      dp2 = list_dup_insert(dp == NULL ? list_dup : dp, fd_in, STDIN_FILENO);

    res = exec_instr(list_instr->elmt, dp2 == NULL ? dp : dp2, error);
    close_fds(&fd_in, filedes, list_instr->next);
    free_and_null(&dp, &dp2);

    CHECK_ERROR()
  }

  return (res);
}
