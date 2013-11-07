#include "exec.h"
#include "../42sh/shell.h"
#include "../masso/masso.h"

/**
** @brief               Builts the arguments array for list.
** @param list_word     Input words list.
** @return              Returns arguments list.
*/
static char             **build_words_array(s_list_words        *list_word)
{
  char                  **words = NULL;
  s_list_words          *list_cur = NULL;
  int                   len = 0;
  int                   i = 0;

  for (list_cur = list_word; list_cur != NULL; list_cur = list_cur->next)
    len++;

  if ((words = mmalloc(sizeof (long int) * (len + 1))) == NULL)
    return (NULL);

  for (list_cur = list_word; list_cur != NULL; list_cur = list_cur->next)
  {
    words[i] = mstring_copy(list_cur->word);
    i++;
  }
  words[i] = NULL;

  return (words);
}

/**
** @brief               Frees an argument array.
** @param words         Input argument array.
** @return              void
*/
static inline void      free_words_array(char                   **words)
{
  int                   i = 0;

  for (i = 0; words[i] != NULL; i++)
    mfree(words[i]);
}

/**
** @brief               Executes one of the node children.
** @param list_dup      File descriptors duplication list.
** @param expwords      Calling arguments.
** @return              void
*/
static inline void      exec_child(s_list_dup                   *list_dup,
                                   char                         **expwords)
{
  for (; list_dup != NULL; list_dup = list_dup->next)
    dup2(list_dup->fd_in, list_dup->fd_out);

  if (execvp(expwords[0], expwords) < 0)
    printf("-%s: %s: command not found\n", "42sh", expwords[0]);

  builtin_exit();
}

/**
** @brief               Frees memeory and returns status.
** @param expwords      Allocated arguments before expansion.
** @param words         Allocated arguments after expansion.
*/
static inline int       free_memory_return(char                 **expwords,
                                           char                 **words,
                                           int                  status)
{
  free_words_array(expwords);
  mfree(words);
  mfree(expwords);

  return (status);
}

/**
** @brief               Is calling command is not an alias and not a function.
*/
#define IS_NONE 0

/**
** @brief               If calling command is an alias call.
*/
#define IS_ALIAS 1

/**
** @brief               If calling command is a shell function.
*/
#define IS_FUNC 2

/**
** @brief               Checks if a command is an alias, a function or other.
** @param word          Input string name.
** @return              Returns IS_NONE, IS_FUNC, or IS_ALIAS.
*/
static inline int       check_func_alias(char                   *word)
{
  if (NULL != masso_get(g_shell->alias, word))
    return (IS_ALIAS);

  if (NULL != masso_get(g_shell->func, word))
    return (IS_FUNC);

  return (IS_NONE);
}

/**
** @brief               Executes an instruction commmand from arguments array.
** @param words         Input arguments array.
** @param list_dup      Input file descriptor duplication list.
** @param error         Error return pointer.
** @return              Returns the value of the command execution.
*/
static inline int       exec_instr_cmd_words(char               **words,
                                             s_list_dup         *list_dup,
                                             int                *error);

/**
** @brief               Calls to an alias command.
** @param expwords      Input arguments array.
** @param list_dup      Input file descriptor duplication list.
** @param error         Error return pointer.
** @param alias_or_func IS_FUNC, IS_ALIAS or IS_NONE.
** @return              Returns the shell execution value.
*/
static inline int       call_func_alias(char                    **expwords,
                                        s_list_dup              *list_dup,
                                        int                     *error,
                                        int                     alias_or_func)
{
  char                  *aux = NULL;

  if (IS_FUNC == alias_or_func)
    return (exec_func(expwords, list_dup, error));

  if (IS_ALIAS == alias_or_func)
  {
      aux = expwords[0];
      expwords[0] = mstring_copy(masso_get(g_shell->alias, expwords[0]));
      mfree(aux);
      return (exec_instr_cmd_words(expwords, list_dup, error));
  }

  return (1);
}

static inline int       exec_instr_cmd_words(char               **words,
                                             s_list_dup         *list_dup,
                                             int                *error)
{
  pid_t                 pid = 0;
  char                  **expwords = NULL;
  int                   status = 0;
  int                   alias_or_func;

  expwords = vars_expand_all(words, error);

  if (ERROR_EVALEXPR == *error)
    return (1);

  if (IS_NONE != (alias_or_func = check_func_alias(expwords[0])))
    return (call_func_alias(expwords, list_dup, error, alias_or_func));

  if (builtin_call(expwords[0], expwords, &status, list_dup) == true ||
      vars_register(expwords[0]))
    return (free_memory_return(expwords, words, status));
  if ((pid = fork()) == 0)
    exec_child(list_dup, expwords);
  else
  {
    waitpid(pid, &status, 0);
    status = WEXITSTATUS(status);
  }

  return (free_memory_return(expwords, words, status));
}

int                     exec_instr_cmd(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error)
{
  s_instr_cmd           *instr_cmd = NULL;
  char                  **words = NULL;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_cmd = instr->instr;
  words = build_words_array(instr_cmd->list_words);

  return (exec_instr_cmd_words(words, list_dup, error));
}
