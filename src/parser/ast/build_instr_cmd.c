/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_cmd     *build_instr_cmd(s_list_words           *list_words)
{
  s_instr_cmd   *res = NULL;

  if (NULL == (res = mmalloc(sizeof (s_instr_cmd))))
    return (NULL);

  res->list_words = list_words;

  return (res);
}

void            free_instr_cmd(s_instr_cmd              *elmt)
{
  if (elmt)
  {
      free_list_words(elmt->list_words);
      mfree(elmt);
  }
}
