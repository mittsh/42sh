/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define PIPELINE_WHILE()                                        \
  while ((NULL != (tok = lexer_get_token(lex))) &&              \
         ((0 == strcmp(tok->str, "|"))))                        \
  {                                                             \
      lexer_eat_token(lex);                                     \
      tok = skip_newline(lex);                                  \
                                                                \
      if ((instr = parse_command(lex)) == NULL)                 \
      {                                                         \
          if (list_instr)                                       \
            free_list_instr(list_instr);                        \
          return (NULL);                                        \
      }                                                         \
                                                                \
      list_instr = add_instr_in_list(list_instr, instr, false); \
  }

s_instr                 *parse_pipeline(s_lexer                 *lex)
{
  s_instr               *instr = NULL;
  s_token               *tok = NULL;
  s_list_instr          *list_instr = NULL;

  if (NULL == (tok = lexer_get_token(lex)))
    return (NULL);

  if (0 == strcmp(tok->str, "!"))
  {
      lexer_eat_token(lex);
      if (NULL == (instr = build_instr(AST_INSTR_NOT,
                                       build_instr_not(parse_command(lex)))))
        return (NULL);
  }
  else
    if (NULL == (instr = parse_command(lex)))
      return (NULL);

  list_instr = build_list_instr();
  list_instr = add_instr_in_list(list_instr, instr, false);

  PIPELINE_WHILE();

  return (build_instr(AST_INSTR_PIPE, build_instr_pipe(list_instr)));
}
