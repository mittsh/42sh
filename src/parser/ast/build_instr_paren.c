/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_paren           *build_instr_paren(s_list_instr         *list_instr)
{
  s_instr_paren         *res = NULL;

  if (NULL == list_instr)
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_paren))))
    return (NULL);

  res->list_instr = list_instr;

  return (res);
}

void                    free_instr_paren(s_instr_paren          *elmt)
{
  if (elmt)
  {
      free_list_instr(elmt->list_instr);
      mfree(elmt);
  }
}
