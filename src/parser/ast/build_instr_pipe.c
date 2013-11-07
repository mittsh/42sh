#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_pipe            *build_instr_pipe(s_list_instr          *list_instr)
{
  s_instr_pipe          *res = NULL;

  if (NULL == list_instr)
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_pipe))))
    return (NULL);

  res->list_instr = list_instr;

  return (res);
}

void                    free_instr_pipe(s_instr_pipe            *elmt)
{
  if (elmt)
  {
    free_list_instr(elmt->list_instr);
    mfree(elmt);
  }
}
