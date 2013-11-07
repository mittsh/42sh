/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_until           *build_instr_until(s_list_instr         *list_cond,
                                           s_list_instr         *list_instr)
{
  s_instr_until         *res = NULL;

  if ((NULL == list_cond) || (NULL == list_instr))
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_until))))
    return (NULL);

  res->list_instr = list_instr;
  res->list_cond = list_cond;

  return (res);
}

void                    free_instr_until(s_instr_until          *elmt)
{
  if (elmt)
  {
      free_list_instr(elmt->list_instr);
      free_list_instr(elmt->list_cond);
      mfree(elmt);
  }
}
