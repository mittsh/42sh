#include "exec.h"
#include "../parser/ast.h"

/*
** Do not forget
** masso_unlink(g_shell->func, instr_func->name);
*/
int                     exec_instr_func(s_instr                 *instr,
                                        s_list_dup              *list_dup,
                                        int                     *error)
{
  s_instr_func          *instr_func = NULL;
  s_instr               *aux = NULL;

  list_dup = list_dup;
  *error = *error;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr->can_free = false;
  instr_func = instr->instr;
  if (instr_func == NULL || instr_func->list_instr == NULL ||
      instr_func->name == NULL)
    return (258);

  aux = masso_get(g_shell->func, instr_func->name);
  if (aux)
  {
      aux->can_free = true;
      free_instr(aux);
      masso_set(g_shell->func, mstring_copy(instr_func->name), instr);
  }
  else
    masso_add(g_shell->func, mstring_copy(instr_func->name), instr);

  return (0);
}

