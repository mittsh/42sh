#include "exec.h"

int                     exec_instr_brack(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error)
{
  int                   res;
  s_instr_brack         *instr_brack = NULL;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_brack = instr->instr;

  res = exec_list_instr(instr_brack->list_instr, list_dup, error);

  return (res);
}
