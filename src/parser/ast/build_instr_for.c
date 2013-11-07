/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_for             *build_instr_for(char                   *var_name,
                                         s_list_words           *list_words,
                                         s_list_instr           *list_instr)
{
  s_instr_for           *res = NULL;

  if ((NULL == list_instr) || (NULL == var_name))
    return (NULL);

  if (NULL == (res = mmalloc(sizeof (s_instr_for))))
    return (NULL);

  res->list_instr = list_instr;
  res->list_words = list_words;
  res->var_name = var_name;

  return (res);
}

void                    free_instr_for(s_instr_for              *elmt)
{
  if (elmt)
  {
      free_list_instr(elmt->list_instr);
      free_list_words(elmt->list_words);
      mfree(elmt->var_name);
      mfree(elmt);
  }
}
