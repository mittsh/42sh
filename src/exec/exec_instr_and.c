#include "exec.h"

int                     exec_instr_and(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error)
{
  s_instr_and           *instr_and = NULL;
  int                   res_l = 0;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_and = instr->instr;
  res_l = exec_instr(instr_and->instr_l, list_dup, error);

  if (res_l == 0)
    return (exec_instr(instr_and->instr_r, list_dup, error));
  else
    return (res_l);
}
