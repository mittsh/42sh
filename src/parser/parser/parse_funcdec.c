/**
** @author maarek_j
** @date Thu Nov 11 20:00:48 2010
*/
#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

/**
** @brief                       This function returns a word and
**                              check if the rule funcdec is applicable
** @param lex                   Lexer.
** @return                      The name's function if OK, NULL if the rule
**                              isn't applicable.
*/
static inline char              *get_word(s_lexer               *lex)
{
  s_token                       *tok = NULL;
  char                          *word = NULL;

  if (NULL == (tok = lexer_pop_token(lex)))
    return (NULL);

  if (0 == strcmp(tok->str, "function"))
    if (NULL == (tok = lexer_pop_token(lex)))
      return (NULL);

  word = tok->str;

  if ((NULL == (tok = lexer_pop_token(lex))) &&
      (0 != strcmp(tok->str, "(")))
    return (NULL);

  if ((NULL == (tok = lexer_pop_token(lex))) &&
      (0 != strcmp(tok->str, ")")))
    return (NULL);

  return (word);
}

s_instr                         *parse_funcdec(s_lexer          *lex)
{
  s_token                       *tok = NULL;
  char                          *word = NULL;
  s_instr                       *instr = NULL;

  if (NULL == (word = get_word(lex)))
    return (NULL);

  if (NULL == (tok = skip_newline(lex)))
    return (NULL);

  if (NULL == (instr = parse_shell_command(lex)))
    return (NULL);

  return (build_instr(AST_INSTR_FUNC,
                      build_instr_func(mstring_copy(word),
                                       add_instr_in_list(NULL,
                                                         instr,
                                                         false))));
  return (NULL);
}
