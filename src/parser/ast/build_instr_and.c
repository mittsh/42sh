/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_and     *build_instr_and(s_instr        *instr_l,
                                 s_instr        *instr_r)
{
  s_instr_and   *res = NULL;

  if ((NULL == instr_l) || (NULL == instr_r))
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_and))))
    return (NULL);

  res->instr_l = instr_l;
  res->instr_r = instr_r;

  return (res);
}

void            free_instr_and(s_instr_and      *elmt)
{
  if (elmt)
  {
      free_instr(elmt->instr_l);
      free_instr(elmt->instr_r);
      mfree(elmt);
  }
}
