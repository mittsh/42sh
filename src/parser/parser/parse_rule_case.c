#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_LCITEMS_RETURN(List_citems)                       \
  {                                                            \
    if (List_citems)                                           \
      free_list_c_items(List_citems);                          \
    return (NULL);                                             \
  }

s_instr                 *parse_rule_case(s_lexer              *lex)
{
  s_token               *tok = NULL;
  char                  *word = NULL;
  s_list_c_items        *list_c_items = NULL;

  if ((NULL == (tok = lexer_pop_token(lex))) || (strcmp(tok->str, "case")))
    return (NULL);

  if ((NULL == (tok = lexer_pop_token(lex))) || (NULL == (word = tok->str)))
    return (NULL);

  while ((NULL != (tok = lexer_get_token(lex))) && (tok->type == TK_NEWLINE))
         lexer_eat_token(lex);
  if (NULL == tok)
    return (NULL);

  if ((NULL == (tok = lexer_pop_token(lex))) || (strcmp(tok->str, "in")))
    return (NULL);

  while ((NULL != (tok = lexer_get_token(lex))) && (tok->type == TK_NEWLINE))
    lexer_eat_token(lex);

  if (NULL == tok)
    return (NULL);

  if ((NULL == (list_c_items = parse_case_clause(lex))) &&
      ((NULL == (tok = lexer_get_token(lex))) || strcmp(tok->str, "esac")))
    FREE_LCITEMS_RETURN(list_c_items);

  if ((NULL == (tok = lexer_pop_token(lex))) || (strcmp(tok->str, "esac")))
    FREE_LCITEMS_RETURN(list_c_items);

  return (build_instr(AST_INSTR_CASE,
                      build_instr_case(mstring_copy(word), list_c_items)));
}
