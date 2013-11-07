/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_if              *build_instr_if(s_list_instr            *list_cond,
                                        s_list_instr            *list_instr_t,
                                        s_instr                 *instr_f)
{
  s_instr_if            *res = NULL;

  if (NULL == list_instr_t)
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_if))))
    return (NULL);

  res->list_cond = list_cond;
  res->list_instr_t = list_instr_t;
  res->instr_f = instr_f;

  return (res);
}

void                    free_instr_if(s_instr_if                *elmt)
{
  if (elmt)
  {
      free_list_instr(elmt->list_cond);
      free_list_instr(elmt->list_instr_t);
      free_instr(elmt->instr_f);
      mfree(elmt);
  }
}
