#include "exec.h"

/**
** @brief               A shorter name for inline.
*/
#define INLNE inline

/**
** @brief               Redirects a file tructate or append.
** @param redir         Redirections list.
** @param list_dup      File descriptor duplication list.
** @param error         Error parameter
** @param fd_list       File descritor list.
** @return              Returns new file descriptor duplication list.
*/
static INLNE s_list_dup *instr_redir_add_trunc(s_list_redir     *redir,
                                               s_list_dup       *list_dup,
                                               int              *error,
                                               s_fd_list        **fd_list)
{
  int                   fd;
  s_fd_list             *fd_elmt = NULL;
  int                   mode = 0;

  if (redir->type == AST_REDIR_OUT_TRUNC)
    mode = O_TRUNC;
  if (redir->type == AST_REDIR_OUT_APPEND)
    mode = O_APPEND;

  fd = mopen(redir->word, O_WRONLY | mode | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd < 0)
  {
    fprintf(stderr, "-42sh: %s: Permission denied\n", redir->word);
    *error = ERROR_PERMISSION_DENIED;
    return (list_dup);
  }

  list_dup = list_dup_insert(list_dup, fd, atoi(redir->ionumber));

  fd_elmt = mmalloc(sizeof (s_fd_list));
  fd_elmt->next = *fd_list;
  fd_elmt->fd = fd;
  fd_elmt->list_dup = list_dup;
  *fd_list = fd_elmt;

  return (list_dup);
}

/**
** @brief               Redirects an input file.
** @param redir         Redirections list.
** @param list_dup      File descriptor duplication list.
** @param error         Error parameter
** @param fd_list       File descritor list.
** @return              Returns new file descriptor duplication list.
*/
static INLNE s_list_dup *instr_redir_add_input(s_list_redir     *redir,
                                               s_list_dup       *list_dup,
                                               int              *error,
                                               s_fd_list        **fd_list)
{
  int                   fd;
  s_fd_list             *fd_elmt = NULL;
  int                   mode = 0;

  if (redir->type == AST_REDIR_INPUT)
    mode = O_RDONLY;
  if (redir->type == AST_REDIR_RDWR)
    mode = O_RDWR;

  fd = mopen(redir->word, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd < 0)
  {
    if (errno == EACCES)
      fprintf(stderr, "-42sh: %s: Permission denied\n", redir->word);
    else
      fprintf(stderr, "-42sh: %s: No such file or directory\n", redir->word);
    *error = ERROR_PERMISSION_DENIED;
    return (list_dup);
  }

  list_dup = list_dup_insert(list_dup, fd, atoi(redir->ionumber));

  fd_elmt = mmalloc(sizeof (s_fd_list));
  fd_elmt->next = *fd_list;
  fd_elmt->fd = fd;
  fd_elmt->list_dup = list_dup;
  *fd_list = fd_elmt;

  return (list_dup);
}

/**
** @brief               Adds a new redirection.
** @param redir         Redirections list.
** @param list_dup      File descriptor duplication list.
** @param error         Error parameter
** @param fd_list       File descritor list.
** @return              Returns new file descriptor duplication list.
*/
static INLNE s_list_dup *instr_redir_add(s_list_redir           *redir,
                                         s_list_dup             *list_dup,
                                         int                    *error,
                                         s_fd_list              **fd_list)
{

  if (redir->type == AST_REDIR_OUT_TRUNC ||
      redir->type == AST_REDIR_OUT_APPEND)
    return (instr_redir_add_trunc(redir, list_dup, error, fd_list));

  if (redir->type == AST_REDIR_INPUT ||
      redir->type == AST_REDIR_RDWR)
    return (instr_redir_add_input(redir, list_dup, error, fd_list));

  return (list_dup);
}

/**
** @brief               Closes all redirection file descriptors.
** @param fd_list       File descriptors list.
** @return              void
*/
static inline void      instr_redir_close(s_fd_list             **fd_list)
{
  s_fd_list             *fd_elmt = NULL;
  s_fd_list             *next = NULL;

  fd_elmt = *fd_list;
  while (fd_elmt != NULL)
  {
    next = fd_elmt->next;
    mclose(fd_elmt->fd);
    mfree(fd_elmt->list_dup);
    mfree(fd_elmt);
    fd_elmt = next;
  }

  *fd_list = fd_elmt;
}

int                     exec_instr_redir(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error)
{
  s_instr_redir         *instr_redir = NULL;
  int                   res = 1;
  s_list_redir          *redir = NULL;
  s_fd_list             *fd_list = NULL;

  if (instr == NULL || instr->instr == NULL)
    return (-1);
  instr_redir = instr->instr;

  for (redir = instr_redir->list_redir; redir != NULL; redir = redir->next)
    list_dup = instr_redir_add(redir, list_dup, error, &fd_list);

  if (*error == ERROR_NONE)
    res = exec_instr(instr_redir->instr, list_dup, error);

  instr_redir_close(&fd_list);

  return (res);
}
