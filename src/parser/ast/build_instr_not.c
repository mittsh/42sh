/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_not             *build_instr_not(s_instr                *instr)
{
  s_instr_not           *res = NULL;

  if (NULL == instr)
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_not))))
    return (NULL);

  res->instr = instr;

  return (res);
}

void            free_instr_not(s_instr_not                      *elmt)
{
  if (elmt)
  {
      free_instr(elmt->instr);
      mfree(elmt);
  }
}
