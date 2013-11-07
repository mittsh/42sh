#include "exec.h"

int                     exec_instr_if(s_instr                   *instr,
                                      s_list_dup                *list_dup,
                                      int                       *error)
{
  s_instr_if            *instr_if = NULL;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_if = instr->instr;

  if (instr_if->list_cond == NULL ||
      exec_list_instr(instr_if->list_cond, list_dup, error) == 0)
  {
    if (*error == ERROR_EVALEXPR)
      return (1);
    return (exec_list_instr(instr_if->list_instr_t, list_dup, error));
  }

  return (exec_instr(instr_if->instr_f, list_dup, error));
}
