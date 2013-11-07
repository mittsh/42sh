/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

t_ast                   *parse_input(s_lexer                    *lex)
{
  s_token               *tok = NULL;
  t_ast                 *ast = NULL;

  tok = skip_newline(lex);
  if (NULL == tok)
    return (NULL);

  ast = parse_list(lex);

  tok = skip_newline(lex);

  return (ast);
}
