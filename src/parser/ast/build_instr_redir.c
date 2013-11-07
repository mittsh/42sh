/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

s_instr_redir           *build_instr_redir(s_instr              *instr,
                                           s_list_redir         *list_redir)
{
  s_instr_redir         *res = NULL;

  if (NULL == (res = mmalloc(sizeof (s_instr_redir))))
    return (NULL);

  res->instr = instr;
  res->list_redir = list_redir;

  return (res);
}

void                    free_instr_redir(s_instr_redir          *elmt)
{
  if (elmt)
  {
      free_instr(elmt->instr);
      free_list_redir(elmt->list_redir);
      mfree(elmt);
  }
}

