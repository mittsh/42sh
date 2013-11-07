/**
** @file		parse_paren_expr.c
** @brief		- paren  ::=  '(' [ope_low] ')' | NUM
**
**
** @author		maarek_j
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "eval_expr.h"
#include "lexer/lexer.h"

s_tree_expr		*parse_paren_expr(s_eelex		*lex)
{
  s_token		*tok = NULL;
  s_tree_expr		*res = NULL;

  if (NULL == (tok = eelex_get_token(lex)))
    return (NULL);

  if (tok->type == TK_PAREN_BEGIN)
  {
      eelex_eat_token(lex);
      res = parse_ope_or_expr(lex);
      if (NULL == (tok = eelex_get_token(lex)))
	return (NULL);
      if (tok->type != TK_PAREN_END)
	return (NULL);
  }
  if (tok->type == TK_NUM)
    res = (build_tree_expr(EXPR_TYPE_NUM, mstring_copy(tok->str), NULL, NULL));

  eelex_eat_token(lex);

  return (res);
}
