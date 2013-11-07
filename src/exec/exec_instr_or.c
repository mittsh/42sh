#include "exec.h"

int                     exec_instr_or(s_instr                   *instr,
                                      s_list_dup                *list_dup,
                                      int                       *error)
{
  s_instr_or            *instr_or = NULL;
  int                   res_l = 0;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_or = instr->instr;

  res_l = exec_instr(instr_or->instr_l, list_dup, error);
  if (error != ERROR_NONE)
    return (res_l);

  if (res_l == 0)
    return (res_l);
  else
    return (exec_instr(instr_or->instr_r, list_dup, error));
}
