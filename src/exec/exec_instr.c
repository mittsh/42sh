#include "exec.h"

/*
** To fix a norm bug
*/
#define INSTR instr
#define LIST_DUP list_dup
#define ERROR error

/**
** @brief               Executes an instruction depanding to its type.
*/
#define CASE_EXEC(TYPEMAJ, TYPE)                                \
  case AST_INSTR_ ## TYPEMAJ:                                   \
    res = (exec_instr_ ## TYPE(INSTR, LIST_DUP, ERROR));        \
    break

/*
** ToDo
** CASE_EXEC(PAREN, paren);
*/
int                     exec_instr(s_instr                      *instr,
                                   s_list_dup                   *list_dup,
                                   int                          *error)
{
  char                  res = 0;
  char                  *res_str = NULL;

  if (instr == NULL)
    return (-1);

  switch (instr->type)
  {
    CASE_EXEC(AND, and);
    CASE_EXEC(OR, or);
    CASE_EXEC(NOT, not);
    CASE_EXEC(PIPE, pipe);
    CASE_EXEC(REDIR, redir);
    CASE_EXEC(IF, if);
    CASE_EXEC(FOR, for);
    CASE_EXEC(WHILE, while);
    CASE_EXEC(UNTIL, until);
    CASE_EXEC(CASE, case);
    CASE_EXEC(CMD, cmd);
    CASE_EXEC(FUNC, func);
    CASE_EXEC(BRACK, brack);
    default:
      return (-1);
  }

  sprintf(res_str = mmalloc(16), "%d", res);
  masso_set(g_shell->vars, "?", res_str);

  return (res);
}
