/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_case    *build_instr_case(char                  *word,
                                  s_list_c_items        *list_c_items)
{
  s_instr_case  *res = NULL;

  if (NULL == (res = mmalloc(sizeof (s_instr_case))))
    return (NULL);

  res->word = word;
  res->list_c_items = list_c_items;

  return (res);
}

void            free_instr_case(s_instr_case            *elmt)
{
  if (elmt)
  {
      mfree(elmt->word);
      free_list_c_items(elmt->list_c_items);
      mfree(elmt);
  }
}
