/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_list_instr            *build_list_instr(void)
{
  s_list_instr          *res = NULL;

  if (NULL == (res = mmalloc(sizeof (s_list_instr))))
    return (NULL);

  res->first = NULL;
  res->last = NULL;

  return (res);
}

void                    free_list_instr(s_list_instr            *elmt)
{
  if (NULL != elmt)
  {
      if (elmt->first)
        free_list_instr_item(elmt->first);
      mfree(elmt);
  }
}
