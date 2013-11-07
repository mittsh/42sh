#include "exec.h"

int                     exec_instr_not(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error)
{
  s_instr_not           *instr_not = NULL;
  int                   res;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_not = instr->instr;

  res = exec_instr(instr_not->instr, list_dup, error);
  if (*error != ERROR_NONE)
    return (1);

  if (res == 0)
    return (1);
  else
    return (0);
}
