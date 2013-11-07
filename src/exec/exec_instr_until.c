#include "exec.h"

int                     exec_instr_until(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error)
{
  s_instr_until         *instr_until = NULL;
  int                   res = 0;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_until = instr->instr;

  while ((res = exec_list_instr(instr_until->list_cond,
                                list_dup, error)) != 0)
    if (error != ERROR_NONE)
      return (res);

  return (res);
}
