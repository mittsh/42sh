#include "shell.h"

/**
** @brief               Frees all shell variables or aliases.
** @param vars          Input variables.
** @return              void
*/
static inline void      free_variables(s_masso          *vars)
{
  int                   i = 0;
  int                   size = 0;
  s_masso_data          *array = NULL;

  array = vars->array;
  size = vars->size;
  for (i = 0; i < size; i++)
    mfree(array[i].value);

  masso_free(vars);
}

/**
** @brief               Frees all shell functions.
** @param funcs         Input functions.
** @return              void
*/
static inline void      free_functions(s_masso          *funcs)
{
  int                   i = 0;
  int                   size = 0;
  s_masso_data          *array = NULL;

  array = funcs->array;
  size = funcs->size;
  for (i = 0; i < size; i++)
    free_instr(array[i].value);

  masso_free(funcs);
}

void                    free_shell(s_shell              *shell)
{
  history_save(shell->queue_history);

  free_history_queue(shell->queue_history);
  free_variables(shell->vars);
  free_functions(shell->func);
  free_variables(shell->alias);

  mstream_close();
  mmalloc_free();

  free(shell);
}
