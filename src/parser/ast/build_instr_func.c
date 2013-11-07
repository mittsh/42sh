/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_func            *build_instr_func(char                  *name,
                                          s_list_instr          *list_instr)
{
  s_instr_func          *res = NULL;

  if ((NULL == name) || (NULL == list_instr))
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_pipe))))
    return (NULL);

  res->name = name;
  res->list_instr = list_instr;

  return (res);
}

void                    free_instr_func(s_instr_func            *elmt)
{
  if (elmt)
  {
      free_list_instr(elmt->list_instr);
      mfree(elmt->name);
      mfree(elmt);
  }
}
