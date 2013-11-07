/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/

#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"

#define ELMT_INSTR elmt->instr

#define CASE_FREE(TYPEMAJ, TYPE)                                \
  case AST_INSTR_ ## TYPEMAJ:                                   \
    free_instr_ ## TYPE(ELMT_INSTR);                            \
    break

s_instr         *build_instr(e_instr_type       type,
                             void               *instr)
{
  s_instr       *res = NULL;

  if (NULL == (res = mmalloc(sizeof (s_instr))))
    return (NULL);

  res->type = type;
  res->instr = instr;
  res->can_free = true;
  return (res);
}

void            free_instr(s_instr              *elmt)
{
  if (elmt)
  {
      if (false == elmt->can_free)
        return;
      switch (elmt->type)
      {
          CASE_FREE(AND, and);
          CASE_FREE(OR, or);
          CASE_FREE(NOT, not);
          CASE_FREE(BRACK, brack);
          CASE_FREE(PAREN, paren);
          CASE_FREE(PIPE, pipe);
          CASE_FREE(REDIR, redir);
          CASE_FREE(FUNC, func);
          CASE_FREE(IF, if);
          CASE_FREE(FOR, for);
          CASE_FREE(WHILE, while);
          CASE_FREE(UNTIL, until);
          CASE_FREE(CASE, case);
          CASE_FREE(CMD, cmd);
      }
      mfree(elmt);
  }
}
