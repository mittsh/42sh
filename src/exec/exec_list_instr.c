#include "exec.h"

int                     exec_list_instr(s_list_instr            *list_instr,
                                        s_list_dup              *list_dup,
                                        int                     *error)
{
  int                   res = 0;
  s_list_instr_item     *itm = NULL;

  if (list_instr == NULL)
    return (-1);

  itm = list_instr->first;
  for (; itm != NULL; itm = itm->next)
  {
    res = exec_instr(itm->elmt, list_dup, error);
    if (*error != ERROR_NONE)
      return (res);
  }

  return (res);
}
