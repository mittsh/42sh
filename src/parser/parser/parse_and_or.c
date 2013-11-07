/**
** @author maarek_j
** @date Wed Nov 10 14:44:00 2010
*/

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_INSTR_RETURN(Instr1, Instr2)           \
  {                                                 \
    if (Instr1)                                     \
      free_instr(Instr1);                           \
    if (Instr2)                                     \
      free_instr(Instr2);                           \
    return (NULL);                                  \
  }

s_instr                 *parse_and_or(s_lexer           *lex)
{
  s_instr               *instr_l = NULL;
  s_instr               *instr_r = NULL;
  s_token               *tok = NULL;

  if (NULL == (instr_l = parse_pipeline(lex)))
    return (NULL);

  if ((NULL == (tok = lexer_get_token(lex))) ||
      ((0 != strcmp(tok->str, "||")) && (0 != strcmp(tok->str, "&&"))))
    return (instr_l);

  lexer_eat_token(lex);

  if (NULL == skip_newline(lex))
    FREE_INSTR_RETURN(instr_l, instr_r);

  if (0 == strcmp(tok->str, "||") || 0 == strcmp(tok->str, "&&"))
  {
      if (NULL == (instr_r = parse_and_or(lex)))
        FREE_INSTR_RETURN(instr_l, instr_r);

      if (0 == strcmp(tok->str, "||"))
        return (build_instr(AST_INSTR_OR, build_instr_or(instr_l, instr_r)));

      if (0 == strcmp(tok->str, "&&"))
        return (build_instr(AST_INSTR_AND, build_instr_and(instr_l, instr_r)));
  }
  else
    FREE_INSTR_RETURN(instr_l, instr_r);
  return (instr_l);
}
