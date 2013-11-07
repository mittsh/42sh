/**
** @author maarek_j
** @date Wed Nov 10 13:23:43 2010
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

static inline bool      test_chevron(s_token            *tok)
{
  if ((tok) && ((0 == strcmp(tok->str, ">")) ||
                (0 == strcmp(tok->str, "<")) ||
                (0 == strcmp(tok->str, ">>")) ||
                (0 == strcmp(tok->str, "<<")) ||
                (0 == strcmp(tok->str, "<<-")) ||
                (0 == strcmp(tok->str, ">&")) ||
                (0 == strcmp(tok->str, "<&")) ||
                (0 == strcmp(tok->str, ">|")) ||
                (0 == strcmp(tok->str, "<>"))))
    return (true);
  else
    return (false);
}

s_instr                 *parse_element(s_lexer          *lex)
{
  s_list_words          *list_words = NULL;
  s_token               *tok = NULL;
  s_token               *tok_next = NULL;

  if (NULL == (tok = lexer_get_token(lex)))
    return (NULL);

  tok_next = lexer_next_token(lex);

  if ((true == test_chevron(tok)) ||
      ((NULL != tok_next) && (true == test_chevron(tok_next))))
    return (build_instr(AST_INSTR_REDIR,
                        build_instr_redir(NULL,
                                          parse_redirection(lex))));

  if (tok)
  {
      lexer_eat_token(lex);
      list_words = mmalloc(sizeof (s_list_words));
      list_words->word = mstring_copy(tok->str);
      list_words->next = NULL;
      return (build_instr(AST_INSTR_CMD,
                          build_instr_cmd(list_words)));
  }

  return (NULL);
}
