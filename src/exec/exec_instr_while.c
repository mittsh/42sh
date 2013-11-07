#include "exec.h"

int                     exec_instr_while(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error)
{
  s_instr_while         *instr_while = NULL;
  int                   res = 0;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_while = instr->instr;

  while ((res = exec_list_instr(instr_while->list_cond,
                                list_dup, error)) == 0)
    if (error != ERROR_NONE)
      return (res);

  return (res);
}
