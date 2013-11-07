/**
** @file			parse_input_expr.c
** @brief			- input  :=  [ope_low]+
**
** @author			maarek_j
*/

#include <stdlib.h>
#include <unistd.h>

#include "eval_expr.h"
#include "lexer/lexer.h"

s_tree_expr		*parse_input_expr(s_eelex		*lex)
{
  s_token		*tok = NULL;
  s_tree_expr		*res = NULL;

  if (NULL == (tok = eelex_get_token(lex)))
    return (NULL);

  res = parse_ope_or_expr(lex);

  return (res);
}
