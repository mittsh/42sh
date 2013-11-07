#include "exec.h"

/**
** @brief               Gets arguments number.
** @param argv          Input arguments values list.
** @return              Returns arguments number.
*/
static inline size_t    get_argc(char                   **argv)
{
  int                   i;

  for (i = 0; argv[i] != NULL; i++)
    ;
  return (i);
}

/**
** @brief               Save argument variables before execution.
** @param argv          Input arguments values.
** @return              Returns arguments values.
*/
static inline char      **save_argv(char                **argv)
{
  int                   argc;
  int                   i;
  char                  **argv_old;
  char                  name[11];

  argc = get_argc(argv);
  argv_old = mcalloc(argc + 1, sizeof (char *));

  argv_old[0] = argv[0];
  for (i = 1; i < argc; i++)
  {
      snprintf(name, 10, "$%i", i);
      if (NULL == (argv_old[i] = masso_get(g_shell->vars, name)))
        argv_old[i] = mstring_copy("");
      masso_set(g_shell->vars, name, mstring_copy(argv[i]));
  }

  return (argv_old);
}

int                     exec_func(char                  **argv,
                                  s_list_dup            *list_dup,
                                  int                   *error)
{
  s_instr_func          *instr_func = NULL;
  s_instr               *instr = NULL;
  int                   res;
  char                  **argv_old = NULL;

  argv_old = save_argv(argv);
  instr = masso_get(g_shell->func, argv[0]);
  instr_func = instr->instr;
  res = exec_list_instr(instr_func->list_instr, list_dup, error);

  return (0);
}
