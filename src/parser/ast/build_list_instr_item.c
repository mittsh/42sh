/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_list_instr_item       *build_list_instr_item(s_instr                  *elmt,
					       s_list_instr_item	*next,
					       bool			bg)
{
  s_list_instr_item	*res = NULL;

  if (NULL == (res = mmalloc(sizeof (s_list_instr_item))))
    return (NULL);

  res->elmt = elmt;
  res->next = next;
  res->bg = bg;

  return (res);
}

void			free_list_instr_item(s_list_instr_item		*elmt)
{
  if (elmt)
  {
      if (elmt->elmt)
        free_instr(elmt->elmt);

      if (NULL != elmt->next)
        free_list_instr_item(elmt->next);
  }

  mfree(elmt);
}
