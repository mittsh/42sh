/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_brack           *build_instr_brack(s_list_instr         *list_instr)
{
  s_instr_brack         *res = NULL;

  if (NULL == (res = mmalloc(sizeof (s_instr_brack))))
    return (NULL);

  res->list_instr = list_instr;

  return (res);
}

void            free_instr_brack(s_instr_brack                  *elmt)
{
  if (elmt)
  {
      free_list_instr(elmt->list_instr);
      mfree(elmt);
  }
}
