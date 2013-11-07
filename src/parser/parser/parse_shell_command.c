/**
** @author maarek_j
** @date Wed Nov 10 14:44:00 2010
*/
#include <stdbool.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_LIST_RETURN(List_instr)            \
  {                                             \
    if (List_instr)                             \
      free_list_instr(List_instr);              \
    return (NULL);                              \
  }

static s_instr                  *subcmd(s_token                 *tok,
                                        s_lexer                 *lex,
                                        s_list_instr            *list_canfree)
{
  s_instr                       *instr = NULL;

  if (0 == strcmp(tok->str, "for"))
    instr = parse_rule_for(lex);
  if (0 == strcmp(tok->str, "until"))
    instr = parse_rule_until(lex);
  if (0 == strcmp(tok->str, "while"))
    instr = parse_rule_while(lex);
  if (0 == strcmp(tok->str, "case"))
    instr = parse_rule_case(lex);
  if (0 == strcmp(tok->str, "if"))
    instr = parse_rule_if(lex);

  if (NULL == instr)
    FREE_LIST_RETURN(list_canfree);

  return (instr);
}

s_instr                         *parse_shell_command(s_lexer    *lex)
{
  s_token                       *tok = NULL;
  s_list_instr                  *list_instr = NULL;

  if (NULL == (tok = lexer_get_token(lex)))
    return (NULL);

  if ('(' == tok->str[0])
  {
      lexer_eat_token(lex);
      if ((NULL == (list_instr = parse_compound_list(lex))) ||
          (NULL == (tok = lexer_pop_token(lex))) ||
          (')' != tok->str[0]))
        FREE_LIST_RETURN(list_instr);

      return (build_instr(AST_INSTR_PAREN, build_instr_paren(list_instr)));
  }

  if ('{' == tok->str[0])
  {
      lexer_eat_token(lex);
      if (NULL == (list_instr = parse_compound_list(lex)))
        FREE_LIST_RETURN(list_instr);
      if (NULL == (tok = lexer_pop_token(lex)))
        FREE_LIST_RETURN(list_instr);
      if ('}' != tok->str[0])
        FREE_LIST_RETURN(list_instr);
      return (build_instr(AST_INSTR_BRACK, build_instr_brack(list_instr)));
  }

  return (subcmd(tok, lex, list_instr));
}
