/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_LIST_RETURN(List_instr)                           \
  {                                                            \
    if (List_instr)                                            \
      free_list_instr(List_instr);                             \
    return (NULL);                                             \
  }

s_list_instr                    *parse_do_group(s_lexer         *lex)
{
  s_list_instr                  *list_instr = NULL;
  s_token                       *tok;

  if ((NULL == (tok = lexer_pop_token(lex))) ||
      (strcmp(tok->str, "do")))
    return (NULL);

  if (NULL == (list_instr = parse_compound_list(lex)))
    return (NULL);

  if ((NULL == (tok = lexer_pop_token(lex))) ||
      (strcmp(tok->str, "done")))
    FREE_LIST_RETURN(list_instr);

  return (list_instr);
}
