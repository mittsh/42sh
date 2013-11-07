/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_LIST_RETURN(List_instr)            \
  {                                             \
    if (List_instr)                             \
      free_list_instr(List_instr);              \
    return (NULL);                              \
  }

s_instr                         *parse_rule_while(s_lexer       *lex)
{
  s_list_instr                  *list_cond = NULL;
  s_list_instr                  *list_instr = NULL;
  s_token                       *tok;

  if ((NULL == (tok = lexer_pop_token(lex))) ||
      (strcmp(tok->str, "while")))
    return (NULL);

  if (NULL == (list_cond = parse_compound_list(lex)))
    return (NULL);

  if (NULL == (list_instr = parse_do_group(lex)))
    FREE_LIST_RETURN(list_cond);

  return (build_instr(AST_INSTR_WHILE,
                      build_instr_while(list_cond, list_instr)));
}
