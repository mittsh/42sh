/**
** @author maarek_j
** @date Thu Nov 11 20:04:07 2010
*/

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

inline s_token          *skip_newline(s_lexer           *lex)
{
  s_token               *tok = NULL;

  while ((NULL != (tok = lexer_get_token(lex))) &&
         (tok->type == TK_NEWLINE))
    lexer_eat_token(lex);

  return (tok);
}
